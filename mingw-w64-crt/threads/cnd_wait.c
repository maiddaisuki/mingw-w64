/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h" /* for __mingw_cnd_timedwait_unguarded() */
#include <windows.h> /* for AcquireSRWLockExclusive(), ReleaseSRWLockExclusive() and INFINITE */

int __cdecl cnd_wait(cnd_t *cond, mtx_t *mtx)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  int ret;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  AcquireSRWLockExclusive(lock);
  ret = __mingw_cnd_timedwait_unguarded(cond, mtx, INFINITE);
  ReleaseSRWLockExclusive(lock);
  return ret;
}
