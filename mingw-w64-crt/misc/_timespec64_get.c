/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>
#include <windows.h>
#include "internal.h"

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))

#if defined(__i386__)
static VOID WINAPI GetSystemTimeAsFileTimeEmul(FILETIME *filetime)
{
  SYSTEMTIME systemtime;
  GetSystemTime(&systemtime);
  if (!SystemTimeToFileTime(&systemtime, filetime))
    filetime->dwHighDateTime = filetime->dwLowDateTime = -1;
}
_Static_assert(__builtin_types_compatible_p(typeof(GetSystemTimeAsFileTimeEmul), typeof(GetSystemTimePreciseAsFileTime)),
  "GetSystemTimeAsFileTimeEmul() and GetSystemTimePreciseAsFileTime() are not compatible");
#endif

static VOID WINAPI GetSystemTimePreciseAsFileTimeInit(FILETIME *filetime);
static typeof(GetSystemTimePreciseAsFileTime) *GetSystemTimePreciseAsFileTimePtr = GetSystemTimePreciseAsFileTimeInit;

static VOID WINAPI GetSystemTimePreciseAsFileTimeInit(FILETIME *filetime)
{
  /* GetSystemTimePreciseAsFileTime() is available since Windows 8 */
  HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
  FARPROC proc = kernel32 ? GetProcAddress(kernel32, "GetSystemTimePreciseAsFileTime") : NULL;
#if defined(__i386__)
  /* GetSystemTimeAsFileTime() is not available in older WinNT versions */
  if (!proc && kernel32) proc = GetProcAddress(kernel32, "GetSystemTimeAsFileTime");
  if (!proc) proc = (FARPROC)(void(*)(void))GetSystemTimeAsFileTimeEmul;
#else
  if (!proc) proc = (FARPROC)(void(*)(void))GetSystemTimeAsFileTime;
#endif
  (void)InterlockedExchangePointer((PVOID *)&GetSystemTimePreciseAsFileTimePtr, proc);
  return GetSystemTimePreciseAsFileTimePtr(filetime);
}
_Static_assert(__builtin_types_compatible_p(typeof(GetSystemTimePreciseAsFileTimeInit), typeof(GetSystemTimePreciseAsFileTime)),
  "GetSystemTimePreciseAsFileTimeInit() and GetSystemTimePreciseAsFileTime() are not compatible");

#define GetSystemTimePreciseAsFileTime GetSystemTimePreciseAsFileTimePtr

#endif

int __cdecl _timespec64_get(struct _timespec64 *ts, int base)
{
  FILETIME filetime;
  unsigned long long val;

  if (!ts) {
    errno = EINVAL;
    _invalid_parameter_noinfo();
    return 0;
  }

  if (base != TIME_UTC)
    return 0;

  GetSystemTimePreciseAsFileTime(&filetime);

  val = ((unsigned long long)filetime.dwHighDateTime << 32) | filetime.dwLowDateTime;

  /* Reject underflow and time above 3001-01-19 00:00:00 PST like ucrt */
  if (val < 116444736000000000 || val >= 441812736000000000)
    return 0;

  val -= 116444736000000000;
  ts->tv_sec = val / 10000000;
  ts->tv_nsec = (val % 10000000) * 100;

  return TIME_UTC;
}
typeof(_timespec64_get) *__MINGW_IMP_SYMBOL(_timespec64_get) = _timespec64_get;

/* On 64-bit systems is timespec_get ABI using 64-bit struct timespec */
#ifdef _WIN64
PRAGMA_DIAGNOSTIC_IGNORED_ATTRIBUTE_ALIAS_BEGIN
int __attribute__ ((alias("_timespec64_get"))) __cdecl timespec_get(struct timespec *);
PRAGMA_DIAGNOSTIC_IGNORED_ATTRIBUTE_ALIAS_END
#endif
