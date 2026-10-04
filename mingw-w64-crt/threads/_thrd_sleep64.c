/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <windows.h> /* for Sleep() */

int __cdecl _thrd_sleep64(const struct _timespec64 *duration, struct _timespec64 *__UNUSED_PARAM(remaining))
{
  long long ms;
  if (__builtin_mul_overflow(duration->tv_sec, 1000, &ms))
    return -2;
  if (__builtin_add_overflow(ms, (duration->tv_nsec + 999999) / 1000000, &ms))
    return -2;
  if (ms > 0xffffffff)
    return -2;
  if (ms < 0)
    ms = 0;
  Sleep(ms);
  /* vcruntime140_threads.dll _thrd_sleep64 does not touch remaining */
  return 0;
}
