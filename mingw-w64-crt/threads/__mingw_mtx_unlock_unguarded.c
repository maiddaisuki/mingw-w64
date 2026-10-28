/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h"
#include <windows.h> /* for GetCurrentThreadId() and WakeConditionVariable() */

/* This function has to be called with AcquireSRWLockExclusive() */
int __cdecl __mingw_mtx_unlock_unguarded(mtx_t *mtx)
{
  _Static_assert(sizeof(mtx->_Cv) == sizeof(CONDITION_VARIABLE), "mtx->_Cv and CONDITION_VARIABLE are not size-compatible");
  CONDITION_VARIABLE *cv = (CONDITION_VARIABLE *)&mtx->_Cv;
  if (mtx->_Owner != GetCurrentThreadId())
    return thrd_error;
  if (--mtx->_Cnt == 0)
    mtx->_Owner = 0;
  WakeConditionVariable(cv);
  return thrd_success;
}
