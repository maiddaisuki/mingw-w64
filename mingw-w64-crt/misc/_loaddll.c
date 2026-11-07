/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <process.h>
#include <windows.h>

intptr_t __cdecl _loaddll(char *filename)
{
  return (intptr_t)LoadLibraryA(filename);
}
typeof(_loaddll) *__MINGW_IMP_SYMBOL(_loaddll) = _loaddll;
