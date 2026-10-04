/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <stdlib.h> /* for malloc() and free() */
#include <process.h> /* for _beginthreadex() */
#include <errno.h> /* for errno and ENOMEM */

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static unsigned __stdcall thread_func(void *data)
{
  void **thread_args = data;
  thrd_start_t func = thread_args[0];
  void *arg = thread_args[1];
  free(thread_args);
  return func(arg);
}

int __cdecl thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
  void *thread_handle;
  unsigned thread_id;
  void **thread_args = malloc(2 * sizeof(void *));
  if (!thread_args)
    return thrd_nomem;
  thread_args[0] = (void *)func;
  thread_args[1] = arg;
  /* Use _beginthreadex() instead of CreateThread() to ensure that C signal dispatcher is properly registered */
  thread_handle = (void *)_beginthreadex(NULL, 0, thread_func, thread_args, 0, &thread_id);
  if (!thread_handle) {
    free(thread_args);
    return errno == ENOMEM ? thrd_nomem : thrd_error;
  }
  thr->_Handle = thread_handle;
  thr->_Tid = thread_id;
  return thrd_success;
}
