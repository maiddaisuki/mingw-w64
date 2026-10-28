/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h" /* for __mingw_mtx_timedlock_unguarded() */
#include <windows.h> /* for AcquireSRWLockExclusive() and ReleaseSRWLockExclusive() */

int __cdecl _mtx_timedlock64(mtx_t *mtx, const struct _timespec64 *ts)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  int ret;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  AcquireSRWLockExclusive(lock);
  ret = __mingw_mtx_timedlock_unguarded(mtx, ts);
  ReleaseSRWLockExclusive(lock);
  return ret;
}
