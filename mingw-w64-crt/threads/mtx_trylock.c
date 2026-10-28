/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include <windows.h> /* for AcquireSRWLockExclusive(), ReleaseSRWLockExclusive() and GetCurrentThreadId() */

int __cdecl mtx_trylock(mtx_t *mtx)
{
  _Static_assert(sizeof(mtx->_Ptr) == sizeof(SRWLOCK), "mtx->_Ptr and SRWLOCK are not size-compatible");
  int ret;
  SRWLOCK *lock = (SRWLOCK *)&mtx->_Ptr;
  DWORD cur_thread_id = GetCurrentThreadId();
  AcquireSRWLockExclusive(lock);

  if (mtx->_Owner == cur_thread_id) {
    if (!(mtx->_Type & mtx_recursive)) {
      ret = thrd_busy;
    } else {
      mtx->_Cnt++;
      ret = thrd_success;
    }
  } else {
    if (mtx->_Owner != 0) {
      ret = thrd_busy;
    } else {
      mtx->_Owner = cur_thread_id;
      mtx->_Cnt = 1;
      ret = thrd_success;
    }
  }

  ReleaseSRWLockExclusive(lock);
  return ret;
}
