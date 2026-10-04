/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <windows.h> /* for CloseHandle() */

int __cdecl thrd_detach(thrd_t thr)
{
  return CloseHandle(thr._Handle) ? thrd_success : thrd_error;
}
