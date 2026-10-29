/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h" /* for DESTROY_MTX_LOCK_AND_CV() */
#include <windows.h> /* for SRWLOCK and CONDITION_VARIABLE */

void __cdecl mtx_destroy(mtx_t *mtx)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  _Static_assert(sizeof(mtx->_Cv) == sizeof(CONDITION_VARIABLE), "mtx->_Cv and CONDITION_VARIABLE are not size-compatible");
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  CONDITION_VARIABLE *cv = (CONDITION_VARIABLE *)&mtx->_Cv;
  DESTROY_MTX_LOCK_AND_CV(lock, cv);
}
