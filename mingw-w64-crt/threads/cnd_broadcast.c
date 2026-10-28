/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include <windows.h> /* for WakeAllConditionVariable() */

int __cdecl cnd_broadcast(cnd_t *cond)
{
  _Static_assert(sizeof(cond->_Ptr) == sizeof(CONDITION_VARIABLE), "cond->_Ptr and CONDITION_VARIABLE are not size-compatible");
  WakeAllConditionVariable((CONDITION_VARIABLE *)&cond->_Ptr);
  return thrd_success;
}
