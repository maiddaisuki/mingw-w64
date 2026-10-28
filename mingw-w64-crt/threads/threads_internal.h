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
