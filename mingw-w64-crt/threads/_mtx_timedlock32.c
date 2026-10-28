/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>

int __cdecl _mtx_timedlock32(mtx_t *mtx, const struct _timespec32 *ts)
{
  return _mtx_timedlock64(mtx, &(struct _timespec64){.tv_sec = ts->tv_sec, .tv_nsec = ts->tv_nsec});
}
