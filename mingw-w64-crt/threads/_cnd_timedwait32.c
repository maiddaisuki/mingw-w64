/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>

int __cdecl _cnd_timedwait32(cnd_t *cond, mtx_t *mtx, const struct _timespec32 *ts)
{
  return _cnd_timedwait64(cond, mtx, &(struct _timespec64){.tv_sec = ts->tv_sec, .tv_nsec = ts->tv_nsec});
}
