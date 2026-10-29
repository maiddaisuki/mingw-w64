/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h" /* for __mingw_mtx_unlock_unguarded(), ACQUIRE_MTX_LOCK_FOR_UNGUARDED_OPS() and RELEASE_MTX_LOCK_FOR_UNGUARDED_OPS() */
#include <windows.h> /* for AcquireSRWLockExclusive() and ReleaseSRWLockExclusive() */

int __cdecl mtx_unlock(mtx_t *mtx)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  int ret;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  ACQUIRE_MTX_LOCK_FOR_UNGUARDED_OPS(lock);
  ret = __mingw_mtx_unlock_unguarded(mtx);
  RELEASE_MTX_LOCK_FOR_UNGUARDED_OPS(lock);
  return ret;
}
