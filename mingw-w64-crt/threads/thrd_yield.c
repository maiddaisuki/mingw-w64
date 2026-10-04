/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <windows.h> /* for SwitchToThread() */

#if defined(__i386__)

static WINBOOL WINAPI SwitchToThreadEmul(void)
{
  Sleep(0);
  return TRUE;
}
_Static_assert(__builtin_types_compatible_p(typeof(SwitchToThreadEmul), typeof(SwitchToThread)), "SwitchToThreadEmul() and SwitchToThread() are not compatible");

static WINBOOL WINAPI SwitchToThreadInit(void);
static typeof(SwitchToThread) *SwitchToThreadPtr = SwitchToThreadInit;

static WINBOOL WINAPI SwitchToThreadInit(void)
{
  /* SwitchToThread() is not available in older WinNT versions */
  HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
  FARPROC proc = kernel32 ? GetProcAddress(kernel32, "SwitchToThread") : NULL;
  if (!proc) proc = SwitchToThreadEmul;
  (void)InterlockedExchangePointer((PVOID *)&SwitchToThreadPtr, proc);
  return SwitchToThreadPtr();
}
_Static_assert(__builtin_types_compatible_p(typeof(SwitchToThreadInit), typeof(SwitchToThread)), "SwitchToThreadInit() and SwitchToThread() are not compatible");

#define SwitchToThread SwitchToThreadPtr

#endif

void __cdecl thrd_yield(void)
{
  SwitchToThread();
}
