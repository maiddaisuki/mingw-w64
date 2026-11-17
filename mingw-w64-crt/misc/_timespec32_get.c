/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>
#include <stdint.h>
#include "internal.h"

int __cdecl _timespec32_get(struct _timespec32 *ts, int base)
{
  struct _timespec64 ts64;
  int ret = _timespec64_get(&ts64, base);
  if (ret == 0 || ts64.tv_sec > INT32_MAX)
    return 0;
  ts->tv_sec = ts64.tv_sec;
  ts->tv_nsec = ts64.tv_nsec;
  return ret;
}
typeof(_timespec32_get) *__MINGW_IMP_SYMBOL(_timespec32_get) = _timespec32_get;

/* On 32-bit systems is timespec_get ABI using 32-bit struct timespec */
#ifndef _WIN64
PRAGMA_DIAGNOSTIC_IGNORED_ATTRIBUTE_ALIAS_BEGIN
int __attribute__ ((alias("_timespec32_get"))) __cdecl timespec_get(struct timespec *);
PRAGMA_DIAGNOSTIC_IGNORED_ATTRIBUTE_ALIAS_END
#endif
