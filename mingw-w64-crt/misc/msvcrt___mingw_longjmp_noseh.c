/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#if defined(__i386__)

#include <setjmp.h>
#include <windows.h>

#ifdef BUILD_FOR_CRTDLL
__MINGW_ATTRIB_NORETURN __attribute__((nothrow)) __attribute__((dllimport)) void __cdecl __crtdll_longjmp(jmp_buf buf, int value);
#undef longjmp
#define longjmp __crtdll_longjmp
#endif

#ifdef BUILD_FOR_MSVCRT10
struct msvcrt10_establisher_frame {
  EXCEPTION_REGISTRATION_RECORD ExceptionRecord;
  const void *ScopeTable;
  DWORD TryLevel;
};
__MINGW_ATTRIB_NORETURN __attribute__((nothrow)) __attribute__((dllimport)) void __cdecl __msvcrt10_longjmp(jmp_buf buf, int value);
#undef longjmp
#define longjmp __msvcrt10_longjmp
#endif

__MINGW_ATTRIB_NORETURN
__attribute__((nothrow))
void __cdecl __mingw_longjmp_noseh(jmp_buf buf, int value)
{
#ifndef BUILD_FOR_CRTDLL
  _JUMP_BUFFER *bufptr = (void *)buf;

  _Static_assert(sizeof(bufptr->Registration) == sizeof(void *), "_JUMP_BUFFER.Registration has not pointer size");
  _Static_assert(sizeof(bufptr->UnwindFunc) == sizeof(void *), "_JUMP_BUFFER.UnwindFunc has not pointer size");

  bufptr->Registration = __readfsdword(0); /* disables calling _global_unwind2() */
#ifdef BUILD_FOR_MSVCRT10
  bufptr->TryLevel = ((struct msvcrt10_establisher_frame *)bufptr->Registration)->TryLevel; /* disables calling _local_unwind2() on msvcrt10 */
#else
  bufptr->Cookie = 0x56433230; /* disables calling _local_unwind2() on msvcrt20+ */
  bufptr->UnwindFunc = 0; /* disables calling custom unwind function on msvcrt20+ */
#endif
#endif

  longjmp(buf, value);
}

#endif
