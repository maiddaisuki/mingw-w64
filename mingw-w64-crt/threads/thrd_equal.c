/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>

int __cdecl thrd_equal(thrd_t thr0, thrd_t thr1)
{
  return thr0._Tid == thr1._Tid;
}
