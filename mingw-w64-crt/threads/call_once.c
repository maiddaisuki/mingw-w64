/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <windows.h> /* for InitOnceExecuteOnce */

#if defined(__i386__) || defined(__x86_64__)

static WINBOOL WINAPI InitOnceExecuteOnceEmul(INIT_ONCE *init_once, PINIT_ONCE_FN init_fn, PVOID parameter, LPVOID *context)
{
  /* For pre-Vista systems use ABI compatible InitOnceExecuteOnce() logic:
   * state 0 - func did not finished successfully yet
   * state 1 - func is being executing
   * state 2 - func already finished successfully
   */
  while (init_once->Ptr != (void *)2) {
    if (InterlockedCompareExchangePointer(&init_once->Ptr, (void *)1, 0) == (void *)0) {
      if (!init_fn(init_once, parameter, context)) {
        (void)InterlockedExchangePointer(&init_once->Ptr, (void *)0);
        return FALSE;
      } else {
        (void)InterlockedExchangePointer(&init_once->Ptr, (void *)2);
        return TRUE;
      }
    } else {
      while (init_once->Ptr == (void *)1)
        Sleep(1);
    }
  }
  return TRUE;
}
_Static_assert(__builtin_types_compatible_p(typeof(InitOnceExecuteOnceEmul), typeof(InitOnceExecuteOnce)), "InitOnceExecuteOnceEmul() and InitOnceExecuteOnce() are not compatible");

static WINBOOL WINAPI InitOnceExecuteOnceInit(INIT_ONCE *init_once, PINIT_ONCE_FN init_fn, PVOID parameter, LPVOID *context);
static typeof(InitOnceExecuteOnce) *InitOnceExecuteOncePtr = InitOnceExecuteOnceInit;

static WINBOOL WINAPI InitOnceExecuteOnceInit(INIT_ONCE *init_once, PINIT_ONCE_FN init_fn, PVOID parameter, LPVOID *context)
{
  /* InitOnceExecuteOnce() is available since Windows Vista */
  HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
  FARPROC proc = kernel32 ? GetProcAddress(kernel32, "InitOnceExecuteOnce") : NULL;
  if (!proc) proc = (FARPROC)(void(*)(void))InitOnceExecuteOnceEmul;
  (void)InterlockedExchangePointer((PVOID *)&InitOnceExecuteOncePtr, proc);
  return InitOnceExecuteOncePtr(init_once, init_fn, parameter, context);
}
_Static_assert(__builtin_types_compatible_p(typeof(InitOnceExecuteOnceInit), typeof(InitOnceExecuteOnce)), "InitOnceExecuteOnceInit() and InitOnceExecuteOnce() are not compatible");

#define InitOnceExecuteOnce InitOnceExecuteOncePtr

#endif

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static WINBOOL WINAPI call_once_func(INIT_ONCE *__UNUSED_PARAM(init_once), PVOID parameter, PVOID *__UNUSED_PARAM(context))
{
  void(__cdecl*func)(void) = (void(__cdecl*)(void))parameter;
  func();
  return TRUE;
}

void __cdecl call_once(once_flag *flag, void(__cdecl*func)(void))
{
  _Static_assert(sizeof(once_flag) == sizeof(INIT_ONCE), "once_flag and INIT_ONCE are not size-compatible");
  InitOnceExecuteOnce((INIT_ONCE *)flag, call_once_func, (void *)func, NULL);
}
