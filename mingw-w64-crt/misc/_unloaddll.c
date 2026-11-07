/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <process.h>
#include <windows.h>

int __cdecl _unloaddll(intptr_t handle)
{
  if (!FreeLibrary((HANDLE)handle))
    return GetLastError();
  else
    return 0;
}
typeof(_unloaddll) *__MINGW_IMP_SYMBOL(_unloaddll) = _unloaddll;
