/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <errno.h>
#include <process.h>
#include <windows.h>

#if defined(__i386__)
#include "i386_sse_float_exception_handler.h"
uintptr_t __cdecl __msvcrt_beginthread(_beginthread_proc_type start_address, unsigned stack_size, void *arglist);
#define _beginthread __msvcrt_beginthread
#endif

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
__MINGW_ATTRIB_NORETURN
static void __cdecl thread_func(void *data)
{
  unsigned ret;
  void **thread_args = data;
  _beginthreadex_proc_type start_address = thread_args[0];
  void *arglist = thread_args[1];
  unsigned *thread_id_ptr = thread_args[2];
  HANDLE child_initialized = thread_args[3];
  HANDLE child_can_run = thread_args[4];

  /* Store our spawned thread id if the caller asked for it. */
  if (thread_id_ptr)
    *thread_id_ptr = GetCurrentThreadId();

  /* Inform the parent thread that we (child) have stopped using the
   * thread_args[] array (which is stored on the parent thread stack).
   * After this step the parent thread can deallocate the thread_args[]
   * array and destroy events which owns.
   */
  _ReadWriteBarrier();
  SetEvent(child_initialized);

  /* Wait until the _beginthreadex() parent finish its initialization.
   * This prevents executing of the application's start_address which
   * could close the thread handle and break our _beginthreadex().
   * This also prevents executing of the application's start_address
   * if our thread should be in the CREATE_SUSPENDED state.
   */
  WaitForSingleObject(child_can_run, INFINITE);
  CloseHandle(child_can_run);

  /* Call the application supplied thread function. */
#if defined(__i386__)
  EXCEPTION_REGISTRATION_RECORD exception_record = {
    .Next = (EXCEPTION_REGISTRATION_RECORD *)__readfsdword(0),
    .Handler = (PEXCEPTION_ROUTINE)(INT_PTR)sse_float_exception_handler,
  };
  __writefsdword(0, (DWORD)&exception_record);
#endif
  ret = start_address(arglist);
#if defined(__i386__)
  __writefsdword(0, (DWORD)exception_record.Next);
#endif

  /* Ensure that our thread function never returns back to the caller as
   * our caller (which is _beginthread) automatically closes the thread handle.
   * Thread spawned by the _beginthreadex() must not close the thread handle.
   */
  ExitThread(ret);
}

/* mingw-w64 _beginthreadex() implementation is wrapper around the CRT _beginthread() function. */
uintptr_t __cdecl _beginthreadex(void *security, unsigned stack_size, _beginthreadex_proc_type start_address, void *arglist, unsigned initflag, unsigned *thread_id_ptr)
{
  void *thread_args[5];
  uintptr_t thread_handle;
  SECURITY_ATTRIBUTES *sec_attrs;
  HANDLE child_initialized;
  HANDLE child_can_run;
  BOOL create_suspended = FALSE;
  BOOL inherit_handle = FALSE;
  SECURITY_DESCRIPTOR *dacl_descriptor = NULL;

  if (initflag) {
    if (initflag & ~(CREATE_SUSPENDED | STACK_SIZE_PARAM_IS_A_RESERVATION)) {
      /* Invalid initflag was passed. */
      errno = EINVAL;
      return 0;
    }
    if (initflag & CREATE_SUSPENDED)
      create_suspended = TRUE;
    /* STACK_SIZE_PARAM_IS_A_RESERVATION is ignored, new thread would have just larger preallocated stack. */
  }

  if (security) {
    sec_attrs = security;
    if (sec_attrs->nLength != sizeof(*sec_attrs)) {
      /* Invalid SECURITY_ATTRIBUTES structure was passed. */
      errno = EINVAL;
      return 0;
    }
    inherit_handle = sec_attrs->bInheritHandle;
    dacl_descriptor = sec_attrs->lpSecurityDescriptor;
  }

  child_initialized = CreateEventA(NULL, TRUE, FALSE, NULL);
  if (!child_initialized) {
    errno = ENOMEM;
    return 0;
  }

  child_can_run = CreateEventA(NULL, TRUE, FALSE, NULL);
  if (!child_can_run) {
    CloseHandle(child_initialized);
    errno = ENOMEM;
    return 0;
  }

  thread_args[0] = (void *)start_address;
  thread_args[1] = arglist;
  thread_args[2] = thread_id_ptr;
  thread_args[3] = child_initialized;
  thread_args[4] = child_can_run;
  thread_handle = _beginthread(thread_func, stack_size, thread_args);

  if (thread_handle != (uintptr_t)-1) {
    /* Set HANDLE_FLAG_INHERIT and DACL_SECURITY_INFORMATION as soon as possible. */
    if (inherit_handle)
      SetHandleInformation((HANDLE)thread_handle, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
    if (dacl_descriptor)
      SetKernelObjectSecurity((HANDLE)thread_handle, DACL_SECURITY_INFORMATION, dacl_descriptor);

    /* Wait until the child thread_func started, filled the thread_id_ptr,
     * stopped using our stack variables, including the automatic array of
     * arguments OR the newly spawned child thread crashed/finished.
     */
    if (WaitForMultipleObjects(2, (HANDLE[]){(HANDLE)thread_handle, child_initialized}, FALSE, INFINITE) == WAIT_OBJECT_0) {
      /* If the newly spawned thread crashed/finished (returns WAIT_OBJECT_0)
       * before signaling the successful startup (returns WAIT_OBJECT_1)
       * then treat it as an _beginthread() error.
       */
      CloseHandle((HANDLE)thread_handle);
      thread_handle = (uintptr_t)-1;
      errno = EINVAL;
    }
    _ReadWriteBarrier();
  }

  CloseHandle(child_initialized);

  /* _beginthread() returned -1 on error but _beginthreadex() has to return 0 on error.
   * _beginthread() already set errno if error happened and above code called
   * only WinAPI functions which do not modify CRT errno at all.
   */
  if (thread_handle == (uintptr_t)-1) {
    CloseHandle(child_can_run);
    return 0;
  }

  /* If the CREATE_SUSPENDED flag was passed then now suspend the child thread.
   * SuspendThread() is asynchronous function and it returns before the thread
   * is suspended. To wait until the thread is suspended, it is needed to call
   * some synchronous operation which forces the suspend request to be processed.
   * GetThreadContext() is one of such function. See:
   * https://devblogs.microsoft.com/oldnewthing/20150205-00/?p=44743
   */
  if (create_suspended) {
    SuspendThread((HANDLE)thread_handle);
    GetThreadContext((HANDLE)thread_handle, &(CONTEXT){.ContextFlags = CONTEXT_CONTROL});
  }

  /* Now tell the child thread that it can execute the application's start_address.
   * If the child thread is suspended then it will start execution after is resumed.
   * Child thread will also closes the child_can_run handle.
   */
  SetEvent(child_can_run);

  return thread_handle;
}
uintptr_t (__cdecl *__MINGW_IMP_SYMBOL(_beginthreadex))(void *, unsigned, _beginthreadex_proc_type, void *, unsigned, unsigned *) = _beginthreadex;
