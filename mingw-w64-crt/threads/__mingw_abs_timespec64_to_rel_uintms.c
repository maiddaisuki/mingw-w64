/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include "threads_internal.h"
#include <windows.h> /* for GetSystemTimeAsFileTime() and INFINITE */

#if defined(__i386__)

static VOID WINAPI GetSystemTimeAsFileTimeEmul(FILETIME *filetime)
{
  SYSTEMTIME systemtime;
  GetSystemTime(&systemtime);
  if (!SystemTimeToFileTime(&systemtime, filetime))
    filetime->dwHighDateTime = filetime->dwLowDateTime = -1;
}
_Static_assert(__builtin_types_compatible_p(typeof(GetSystemTimeAsFileTimeEmul), typeof(GetSystemTimeAsFileTime)),
  "GetSystemTimeAsFileTimeEmul() and GetSystemTimeAsFileTime() are not compatible");

static VOID WINAPI GetSystemTimeAsFileTimeInit(FILETIME *filetime);
static typeof(GetSystemTimeAsFileTime) *GetSystemTimeAsFileTimePtr = GetSystemTimeAsFileTimeInit;

static VOID WINAPI GetSystemTimeAsFileTimeInit(FILETIME *filetime)
{
  /* GetSystemTimeAsFileTime() is not available in older WinNT versions */
  HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
  FARPROC proc = kernel32 ? GetProcAddress(kernel32, "GetSystemTimeAsFileTime") : NULL;
  if (!proc) proc = (FARPROC)(void(*)(void))GetSystemTimeAsFileTimeEmul;
  (void)InterlockedExchangePointer((PVOID *)&GetSystemTimeAsFileTimePtr, proc);
  return GetSystemTimeAsFileTimePtr(filetime);
}
_Static_assert(__builtin_types_compatible_p(typeof(GetSystemTimeAsFileTimeInit), typeof(GetSystemTimeAsFileTime)),
  "GetSystemTimeAsFileTimeInit() and GetSystemTimeAsFileTime() are not compatible");

#define GetSystemTimeAsFileTime GetSystemTimeAsFileTimePtr

#endif

int __cdecl __mingw_abs_timespec64_to_rel_uintms(const struct _timespec64 *ts, unsigned *timeout)
{
  FILETIME now_ft_struct;
  unsigned long long now_ft;
  long long ts_ft;
  unsigned long long ms;

  if (__builtin_mul_overflow(ts->tv_sec, 10000000, &ts_ft))
    return thrd_error;
  if (__builtin_add_overflow(ts_ft, ts->tv_nsec/100, &ts_ft))
    return thrd_error;
  if (__builtin_add_overflow(ts_ft, 116444736000000000, &ts_ft))
    return thrd_error;

  GetSystemTimeAsFileTime(&now_ft_struct);
  now_ft = ((unsigned long long)now_ft_struct.dwHighDateTime << 32) | now_ft_struct.dwLowDateTime;
  if (ts_ft < 0 || (unsigned long long)ts_ft <= now_ft)
    return thrd_timedout;

  ms = ((unsigned long long)ts_ft - now_ft) / 10000;
  if (ms > 0xffffffff || ms == INFINITE)
    return thrd_error;
  if (ms <= 0)
    return thrd_timedout;
  *timeout = ms;
  return thrd_success;
}
