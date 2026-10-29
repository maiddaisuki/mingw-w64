/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

int __cdecl __mingw_abs_timespec64_to_rel_uintms(const struct _timespec64 *ts, unsigned *timeout);
int __cdecl __mingw_cnd_timedwait_unguarded(cnd_t *cond, mtx_t *mtx, unsigned timeout);
int __cdecl __mingw_mtx_timedlock_unguarded(mtx_t *mtx, const struct _timespec64 *ts);
int __cdecl __mingw_mtx_unlock_unguarded(mtx_t *mtx);

/* On pre-Vista systems, all mtx unguarded functions are called without lock,
 * so on pre-Vista systems read-modify-write of mtx members have to be atomic.
 * On Vista and new systems does not have to be. */
#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))
#define MTX_TRY_CHANGE_OWNER_UNGUARDED(mtx, new_owner) (!InterlockedCompareExchange((volatile LONG*)&(mtx)->_Owner, (new_owner), 0))
#else
#define MTX_TRY_CHANGE_OWNER_UNGUARDED(mtx, new_owner) ((mtx)->_Owner == 0 ? (!!((mtx)->_Owner = (new_owner))) : 0)
#endif

/* On pre-Vista systems, lock is noop and cv is synchronous WinAPI event.
 * On Vista and new systems lock is SRWLOCK which protects cv CONDITION_VARIABLE
 * in all mtx unguarded functions. SRWLOCK and CONDITION_VARIABLE functions
 * on 32-bit and 64-bit x86 systems are resolved at runtime (when available). */
#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))
struct _RTL_SRWLOCK;
struct _RTL_CONDITION_VARIABLE;
extern int(__stdcall*__mingw_initialize_mtx_lock_and_cv_ptr)(struct _RTL_SRWLOCK*,struct _RTL_CONDITION_VARIABLE*);
extern void(__stdcall*__mingw_destroy_mtx_lock_and_cv_ptr)(struct _RTL_SRWLOCK*,struct _RTL_CONDITION_VARIABLE*);
extern void(__stdcall*__mingw_acquire_mtx_lock_for_unguarded_ops_ptr)(struct _RTL_SRWLOCK*);
extern void(__stdcall*__mingw_release_mtx_lock_for_unguarded_ops_ptr)(struct _RTL_SRWLOCK*);
extern void(__stdcall*__mingw_singal_mtx_cv_unguarded_ptr)(struct _RTL_CONDITION_VARIABLE*);
extern int(__stdcall*__mingw_wait_for_mtx_cv_unguarded_ptr)(struct _RTL_CONDITION_VARIABLE*,struct _RTL_SRWLOCK*,unsigned long,unsigned long);
#define INITIALIZE_MTX_LOCK_AND_CV(lock, cv) __mingw_initialize_mtx_lock_and_cv_ptr(lock, cv)
#define DESTROY_MTX_LOCK_AND_CV(lock, cv) __mingw_destroy_mtx_lock_and_cv_ptr(lock, cv)
#define ACQUIRE_MTX_LOCK_FOR_UNGUARDED_OPS(lock) __mingw_acquire_mtx_lock_for_unguarded_ops_ptr(lock)
#define RELEASE_MTX_LOCK_FOR_UNGUARDED_OPS(lock) __mingw_release_mtx_lock_for_unguarded_ops_ptr(lock)
#define SIGNAL_MTX_CV_UNGUARDED(cv) __mingw_singal_mtx_cv_unguarded_ptr(cv)
#define WAIT_FOR_MTX_CV_UNGUARDED(cv, lock, timeout, flags) __mingw_wait_for_mtx_cv_unguarded_ptr(cv, lock, timeout, flags)
#else
#define INITIALIZE_MTX_LOCK_AND_CV(lock, cv) (InitializeSRWLock(lock), InitializeConditionVariable(cv), 1)
#define DESTROY_MTX_LOCK_AND_CV(lock, cv) ((void)(lock), (void)(cv))
#define ACQUIRE_MTX_LOCK_FOR_UNGUARDED_OPS(lock) AcquireSRWLockExclusive(lock)
#define RELEASE_MTX_LOCK_FOR_UNGUARDED_OPS(lock) ReleaseSRWLockExclusive(lock)
#define SIGNAL_MTX_CV_UNGUARDED(cv) WakeConditionVariable(cv)
#define WAIT_FOR_MTX_CV_UNGUARDED(cv, lock, timeout, flags) SleepConditionVariableSRW(cv, lock, timeout, flags)
#endif
