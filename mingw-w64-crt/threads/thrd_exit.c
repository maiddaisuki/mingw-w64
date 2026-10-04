/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <windows.h> /* for ExitThread() */

void __cdecl __MINGW_ATTRIB_NORETURN thrd_exit(int res)
{
  ExitThread(res);
}
