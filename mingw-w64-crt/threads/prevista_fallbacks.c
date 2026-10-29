/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))

#include <windows.h>

/* Lock functions are not used for pre-Vista emulation, so they are just noop */

static VOID WINAPI AcquireSRWLockExclusiveNoop(SRWLOCK *__UNUSED_PARAM(lock)) { }
_Static_assert(__builtin_types_compatible_p(typeof(AcquireSRWLockExclusiveNoop), typeof(AcquireSRWLockExclusive)),
  "AcquireSRWLockExclusiveNoop() and AcquireSRWLockExclusive() are not compatible");

static VOID WINAPI ReleaseSRWLockExclusiveNoop(SRWLOCK *__UNUSED_PARAM(lock)) { }
_Static_assert(__builtin_types_compatible_p(typeof(ReleaseSRWLockExclusiveNoop), typeof(ReleaseSRWLockExclusive)),
  "ReleaseSRWLockExclusiveNoop() and ReleaseSRWLockExclusive() are not compatible");

/* Whole synchronization functionality for pre-Vista emulation is implemented in these functions */

static WINBOOL WINAPI InitializeNullInSRWLockAndEventInCV(SRWLOCK *__UNUSED_PARAM(lock), CONDITION_VARIABLE *cv)
{
  lock->Ptr = NULL;
  cv->Ptr = CreateEventA(NULL, FALSE, FALSE, NULL);
  return !!cv->Ptr;
}

static VOID WINAPI DestroyNothingInSRWLockAndEventInCV(SRWLOCK *__UNUSED_PARAM(lock), CONDITION_VARIABLE *cv)
{
  HANDLE event = (HANDLE)cv->Ptr;
  if (event)
    CloseHandle(event);
  cv->Ptr = NULL;
}

static VOID WINAPI SetEventInCV(CONDITION_VARIABLE *cv)
{
  HANDLE event = (HANDLE)cv->Ptr;
  SetEvent(event);
}
_Static_assert(__builtin_types_compatible_p(typeof(SetEventInCV), typeof(WakeConditionVariable)),
  "SetEventInCV() and WakeConditionVariable() are not compatible");

static WINBOOL WINAPI WaitForSingleObjectInCV(CONDITION_VARIABLE *cv, SRWLOCK *__UNUSED_PARAM(lock), DWORD timeout, ULONG __UNUSED_PARAM(flags))
{
  HANDLE event = (HANDLE)cv->Ptr;
  DWORD result = WaitForSingleObject(event, timeout);
  if (result == WAIT_OBJECT_0) {
    return TRUE;
  } else if (result == WAIT_TIMEOUT) {
    SetLastError(ERROR_TIMEOUT);
    return FALSE;
  } else if (result == WAIT_FAILED) {
    /* LastError is already set */
    return FALSE;
  } else {
    SetLastError(ERROR_GEN_FAILURE);
    return FALSE;
  }
}
_Static_assert(__builtin_types_compatible_p(typeof(WaitForSingleObjectInCV), typeof(SleepConditionVariableSRW)),
  "WaitForSingleObjectInCV() and SleepConditionVariableSRW() are not compatible");

static typeof(InitializeSRWLock) *InitializeSRWLockPtr = NULL;
static typeof(InitializeConditionVariable) *InitializeConditionVariablePtr = NULL;

static WINBOOL WINAPI InitializeSRWLockAndConditionVariableNative(SRWLOCK *lock, CONDITION_VARIABLE *cv)
{
  InitializeSRWLockPtr(lock);
  InitializeConditionVariablePtr(cv);
  return TRUE;
}

static VOID WINAPI DestroySRWLockAndConditionVariableNative(SRWLOCK *__UNUSED_PARAM(lock), CONDITION_VARIABLE *__UNUSED_PARAM(cv)) { }

static WINBOOL WINAPI init_initialize_mtx_lock_and_cv_ptr(SRWLOCK *lock, CONDITION_VARIABLE *cv);
static VOID WINAPI init_destroy_mtx_lock_and_cv_ptr(SRWLOCK *lock, CONDITION_VARIABLE *cv);
static VOID WINAPI init_acquire_mtx_lock_for_unguarded_ops_ptr(SRWLOCK *lock);
static VOID WINAPI init_release_mtx_lock_for_unguarded_ops_ptr(SRWLOCK *lock);
static VOID WINAPI init_singal_mtx_cv_unguarded_ptr(CONDITION_VARIABLE *cv);
static WINBOOL WINAPI init_wait_for_mtx_cv_unguarded_ptr(CONDITION_VARIABLE *cv, SRWLOCK *lock, DWORD timeout, ULONG flags);

/* Exported functions */
typeof(InitializeSRWLockAndConditionVariableNative) *__mingw_initialize_mtx_lock_and_cv_ptr = init_initialize_mtx_lock_and_cv_ptr;
typeof(DestroySRWLockAndConditionVariableNative) *__mingw_destroy_mtx_lock_and_cv_ptr = init_destroy_mtx_lock_and_cv_ptr;
typeof(AcquireSRWLockExclusive) *__mingw_acquire_mtx_lock_for_unguarded_ops_ptr = init_acquire_mtx_lock_for_unguarded_ops_ptr;
typeof(ReleaseSRWLockExclusive) *__mingw_release_mtx_lock_for_unguarded_ops_ptr = init_release_mtx_lock_for_unguarded_ops_ptr;
typeof(WakeConditionVariable) *__mingw_singal_mtx_cv_unguarded_ptr = init_singal_mtx_cv_unguarded_ptr;
typeof(SleepConditionVariableSRW) *__mingw_wait_for_mtx_cv_unguarded_ptr = init_wait_for_mtx_cv_unguarded_ptr;

__attribute__((constructor))
static void init(void)
{
  typeof(AcquireSRWLockExclusive) *AcquireSRWLockExclusivePtr;
  typeof(ReleaseSRWLockExclusive) *ReleaseSRWLockExclusivePtr;
  typeof(WakeConditionVariable) *WakeConditionVariablePtr;
  typeof(SleepConditionVariableSRW) *SleepConditionVariableSRWPtr;
  BOOL fallback = TRUE;
  HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
  if (kernel32) {
    InitializeSRWLockPtr = (typeof(InitializeSRWLockPtr))(void(*)(void))GetProcAddress(kernel32, "InitializeSRWLock");
    AcquireSRWLockExclusivePtr = (typeof(AcquireSRWLockExclusivePtr))(void(*)(void))GetProcAddress(kernel32, "AcquireSRWLockExclusive");
    ReleaseSRWLockExclusivePtr = (typeof(ReleaseSRWLockExclusivePtr))(void(*)(void))GetProcAddress(kernel32, "ReleaseSRWLockExclusive");
    InitializeConditionVariablePtr = (typeof(InitializeConditionVariablePtr))(void(*)(void))GetProcAddress(kernel32, "InitializeConditionVariable");
    WakeConditionVariablePtr = (typeof(WakeConditionVariablePtr))(void(*)(void))GetProcAddress(kernel32, "WakeConditionVariable");
    SleepConditionVariableSRWPtr = (typeof(SleepConditionVariableSRWPtr))(void(*)(void))GetProcAddress(kernel32, "SleepConditionVariableSRW");
    if (InitializeSRWLockPtr && AcquireSRWLockExclusivePtr && ReleaseSRWLockExclusivePtr &&
        InitializeConditionVariablePtr && WakeConditionVariablePtr && SleepConditionVariableSRWPtr) {
      fallback = FALSE;
    }
  }
  if (fallback) {
    __mingw_initialize_mtx_lock_and_cv_ptr = InitializeNullInSRWLockAndEventInCV;
    __mingw_destroy_mtx_lock_and_cv_ptr = DestroyNothingInSRWLockAndEventInCV;
    __mingw_acquire_mtx_lock_for_unguarded_ops_ptr = AcquireSRWLockExclusiveNoop;
    __mingw_release_mtx_lock_for_unguarded_ops_ptr = ReleaseSRWLockExclusiveNoop;
    __mingw_singal_mtx_cv_unguarded_ptr = SetEventInCV;
    __mingw_wait_for_mtx_cv_unguarded_ptr = WaitForSingleObjectInCV;
  } else {
    __mingw_initialize_mtx_lock_and_cv_ptr = InitializeSRWLockAndConditionVariableNative;
    __mingw_destroy_mtx_lock_and_cv_ptr = DestroySRWLockAndConditionVariableNative;
    __mingw_acquire_mtx_lock_for_unguarded_ops_ptr = AcquireSRWLockExclusivePtr;
    __mingw_release_mtx_lock_for_unguarded_ops_ptr = ReleaseSRWLockExclusivePtr;
    __mingw_singal_mtx_cv_unguarded_ptr = WakeConditionVariablePtr;
    __mingw_wait_for_mtx_cv_unguarded_ptr = SleepConditionVariableSRWPtr;
  }
}

/* Guards in case those exported functions are called before our init()
 * function which marked with __attribute__((constructor)).
 * This can happen for example from PE TLS callback or from .CRT$XI? callback.
 * In all these pre-init phase cases, application is still single threaded.
 */

static WINBOOL WINAPI init_initialize_mtx_lock_and_cv_ptr(SRWLOCK *lock, CONDITION_VARIABLE *cv)
{
  init();
  return __mingw_initialize_mtx_lock_and_cv_ptr(lock, cv);
}

static VOID WINAPI init_destroy_mtx_lock_and_cv_ptr(SRWLOCK *lock, CONDITION_VARIABLE *cv)
{
  init();
  __mingw_destroy_mtx_lock_and_cv_ptr(lock, cv);
}

static VOID WINAPI init_acquire_mtx_lock_for_unguarded_ops_ptr(SRWLOCK *lock)
{
  init();
  __mingw_acquire_mtx_lock_for_unguarded_ops_ptr(lock);
}

static VOID WINAPI init_release_mtx_lock_for_unguarded_ops_ptr(SRWLOCK *lock)
{
  init();
  __mingw_release_mtx_lock_for_unguarded_ops_ptr(lock);
}

static VOID WINAPI init_singal_mtx_cv_unguarded_ptr(CONDITION_VARIABLE *cv)
{
  init();
  __mingw_singal_mtx_cv_unguarded_ptr(cv);
}

static WINBOOL WINAPI init_wait_for_mtx_cv_unguarded_ptr(CONDITION_VARIABLE *cv, SRWLOCK *lock, DWORD timeout, ULONG flags)
{
  init();
  return __mingw_wait_for_mtx_cv_unguarded_ptr(cv, lock, timeout, flags);
}

#endif
