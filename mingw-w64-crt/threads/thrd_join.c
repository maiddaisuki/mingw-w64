/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include <windows.h> /* for WaitForSingleObject(), GetExitCodeThread(), CloseHandle() and INFINITE */

int __cdecl thrd_join(thrd_t thr, int *res)
{
  DWORD exit_code;
  if (WaitForSingleObject(thr._Handle, INFINITE))
    return thrd_error;
  if (!GetExitCodeThread(thr._Handle, &exit_code))
    return thrd_error;
  if (res)
    *res = exit_code;
  return CloseHandle(thr._Handle) ? thrd_success : thrd_error;
}
