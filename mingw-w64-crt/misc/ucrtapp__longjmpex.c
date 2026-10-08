/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#if defined(__i386__)

#include <setjmp.h>
#include <windows.h>

__MINGW_ATTRIB_NORETURN __attribute__((nothrow)) void __cdecl __mingw_longjmp_noseh(jmp_buf buf, int value);

__MINGW_ATTRIB_NORETURN
__attribute__((nothrow))
void __cdecl _longjmpex(jmp_buf buf, int value)
{
  _JUMP_BUFFER *bufptr = (void *)buf;

  _Static_assert(sizeof(bufptr->Registration) == sizeof(void *), "_JUMP_BUFFER.Registration has not pointer size");
  _Static_assert(sizeof(bufptr->UnwindFunc) == sizeof(void *), "_JUMP_BUFFER.UnwindFunc has not pointer size");

  if (bufptr->Registration != __readfsdword(0)) {
    /* Call: global_unwind2((void *)bufptr->Registration);
     * Function global_unwind2() is just calling the function RtlUnwind().
     * Function RtlUnwind() cannot be easily called from C source code easily
     * because it does not return via the return address placed on the stack
     * but it returns to the address in the second function argument on the stack.
     * And also it clobbers 3 additional callee saved ebx, esi and edi registers.
     * So call the RtlUnwind((void *)bufptr->Registration, ret_addr, NULL, NULL);
     * via the inline assembly.
     */
    asm volatile(
      "pushl $0\r\n"
      "pushl $0\r\n"
      "pushl $1f\r\n" /* label after calll */
      "pushl %0\r\n"
      "calll _RtlUnwind@16\r\n"
      "1:"
      :
      : "rmi" (bufptr->Registration)
      : "eax", "ecx", "edx", /* stdcall clobbered registers */
        "ebx", "esi", "edi", /* RtlUnwind clobbered registers */
        "memory"
    );
  }

  if (bufptr->Registration != 0) {
    if (!IsBadReadPtr(&bufptr->Cookie, sizeof(bufptr->Cookie)) && bufptr->Cookie == 0x56433230) {
      if (bufptr->UnwindFunc != 0)
        ((void(__stdcall*)(const _JUMP_BUFFER *))bufptr->UnwindFunc)(bufptr);
    } else {
      /* Call _local_unwind2((void *)bufptr->Registration, bufptr->TryLevel);
       * TODO: mingw-w64 does not provide _local_unwind2() implementation yet.
       */
    }
  }

  __mingw_longjmp_noseh(buf, value);
}
void (__cdecl *__MINGW_IMP_SYMBOL(_longjmpex))(jmp_buf buf, int value) = _longjmpex;

/* In msvcrt and UCRT the longjmp() function is calling SEH unwind and is aliased to _longjmpex() function. */
#undef longjmp
void __attribute__((alias("_longjmpex"))) __cdecl longjmp(jmp_buf buf, int value);
extern void __attribute__((alias(__MINGW64_STRINGIFY(__MINGW_IMP_SYMBOL(_longjmpex)))))(__cdecl *__MINGW_IMP_SYMBOL(longjmp))(jmp_buf buf, int value);

#endif
