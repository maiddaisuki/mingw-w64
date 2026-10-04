/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>

int __cdecl _thrd_sleep32(const struct _timespec32 *duration, struct _timespec32 *__UNUSED_PARAM(remaining))
{
  return _thrd_sleep64(&(struct _timespec64){.tv_sec = duration->tv_sec, .tv_nsec = duration->tv_nsec}, NULL);
  /* vcruntime140_threads.dll _thrd_sleep32 does not touch remaining */
}
