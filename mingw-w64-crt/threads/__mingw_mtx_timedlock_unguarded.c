/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h"
#include <windows.h> /* for GetCurrentThreadId(), GetLastError(), SleepConditionVariableSRW() and INFINITE */

/* This function has to be called with AcquireSRWLockExclusive() */
int __cdecl __mingw_mtx_timedlock_unguarded(mtx_t *mtx, const struct _timespec64 *ts)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  _Static_assert(sizeof(mtx->_Cv) == sizeof(CONDITION_VARIABLE), "mtx->_Cv and CONDITION_VARIABLE are not size-compatible");
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  CONDITION_VARIABLE *cv = (CONDITION_VARIABLE *)&mtx->_Cv;
  DWORD cur_thread_id = GetCurrentThreadId();
  if (mtx->_Owner == cur_thread_id) {
    if (!(mtx->_Type & mtx_recursive))
      return thrd_error;
    mtx->_Cnt++;
  } else {
    while (mtx->_Owner != 0) {
      unsigned timeout = INFINITE;
      if (ts) {
        int ret = __mingw_abs_timespec64_to_rel_uintms(ts, &timeout);
        if (ret != thrd_success)
          return ret;
      }
      if (!SleepConditionVariableSRW(cv, lock, timeout, 0))
        return GetLastError() == ERROR_TIMEOUT ? thrd_timedout : thrd_error;
    }
    mtx->_Owner = cur_thread_id;
    mtx->_Cnt = 1;
  }
  return thrd_success;
}
