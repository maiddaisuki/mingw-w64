/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h" /* for __mingw_abs_timespec64_to_rel_uintms() and __mingw_cnd_timedwait_unguarded() */
#include <windows.h> /* for AcquireSRWLockExclusive() and ReleaseSRWLockExclusive() */

int __cdecl _cnd_timedwait64(cnd_t *cond, mtx_t *mtx, const struct _timespec64 *ts)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  int ret;
  unsigned timeout;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  ret = __mingw_abs_timespec64_to_rel_uintms(ts, &timeout);
  if (ret != thrd_success)
    return ret;
  AcquireSRWLockExclusive(lock);
  ret = __mingw_cnd_timedwait_unguarded(cond, mtx, timeout);
  ReleaseSRWLockExclusive(lock);
  return ret;
}
