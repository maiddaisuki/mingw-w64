/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h"
#include <windows.h> /* for GetLastError() and SleepConditionVariableSRW() */

/* This function has to be called with AcquireSRWLockExclusive() */
int __cdecl __mingw_cnd_timedwait_unguarded(cnd_t *cond, mtx_t *mtx, unsigned timeout)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  _Static_assert(sizeof(cond->_Ptr) == sizeof(CONDITION_VARIABLE), "cond->_Ptr and CONDITION_VARIABLE are not size-compatible");
  int cnd_ret, mtx_ret;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  CONDITION_VARIABLE *cv = (CONDITION_VARIABLE *)&cond->_Ptr;
  mtx_ret = __mingw_mtx_unlock_unguarded(mtx);
  if (mtx_ret != thrd_success)
    return mtx_ret;
  if (!SleepConditionVariableSRW(cv, lock, timeout, 0))
    cnd_ret = GetLastError() == ERROR_TIMEOUT ? thrd_timedout : thrd_error;
  else
    cnd_ret = thrd_success;
  mtx_ret = __mingw_mtx_timedlock_unguarded(mtx, NULL);
  if (mtx_ret != thrd_success)
    return mtx_ret;
  return cnd_ret;
}
