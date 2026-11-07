/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <process.h>
#include <windows.h>

int (__cdecl *__cdecl _getdllprocaddr(intptr_t handle, char *name, intptr_t ordinal))(void)
{
  LPCSTR arg;
  if (!name && ordinal <= 65535)
    arg = (LPCSTR)ordinal;
  else if (name && ordinal == -1)
    arg = name;
  else
    return NULL;
  return (int(__cdecl*)(void))(void(*)(void))GetProcAddress((HANDLE)handle, arg);
}
typeof(_getdllprocaddr) *__MINGW_IMP_SYMBOL(_getdllprocaddr) = _getdllprocaddr;
