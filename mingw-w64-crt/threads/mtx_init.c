/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include <windows.h> /* for InitializeConditionVariable() and InitializeSRWLock() */

int mtx_init(mtx_t *mtx, int type)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  _Static_assert(sizeof(mtx->_Cv) == sizeof(CONDITION_VARIABLE), "mtx->_Cv and CONDITION_VARIABLE are not size-compatible");
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  CONDITION_VARIABLE *cv = (CONDITION_VARIABLE *)&mtx->_Cv;
  /* vcruntime140_threads.dll mtx_init does not validate type */
  mtx->_Type = type;
  InitializeSRWLock(lock);
  InitializeConditionVariable(cv);
  mtx->_Owner = 0;
  mtx->_Cnt = 0;
  return thrd_success;
}
