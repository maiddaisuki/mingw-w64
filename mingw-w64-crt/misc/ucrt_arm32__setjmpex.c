/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#if defined(__arm__)

#include <setjmp.h>

/* arm32 _setjmp() function ignores it second frame argument and always stores
 * the NULL pointer into the Frame member of _JUMP_BUFFER structure.
 * Implement our _setjmpex() function as a wrapper around the _setjmp() function
 * and manually stores the frame pointer into the Frame member.
 * Note that we need to fixup Sp and Pc members as they were not filled with
 * respect to the caller of our _setjmpex() function.
 */
int __cdecl __attribute__((naked)) __attribute__((nothrow, returns_twice)) _setjmpex(jmp_buf buf, void *frame)
{
    asm(
        "push.w {r4, r5, lr}\n\t"
        "mov    r4, r0\n\t"
        "mov    r5, r1\n\t"
        "bl     _setjmp\n\t"
        "mov    r2, r4\n\t"
        "mov    r1, r5\n\t"
        "pop.w  {r4, r5, lr}\n\t"
        "str    r1, [r2, #0x00]\n\t" /* jmp_buf->Frame */
        "str    sp, [r2, #0x24]\n\t" /* jmp_buf->Sp */
        "str    lr, [r2, #0x28]\n\t" /* jmp_buf->Pc */
        "bx     lr\n\t"
    );
}
int (__cdecl *__MINGW_IMP_SYMBOL(_setjmpex))(jmp_buf buf, void *frame) = _setjmpex;

/* In UCRT is the _setjmpex() function aliased to __intrinsic_setjmpex() function. */
int __attribute__((alias("_setjmpex"))) __cdecl __intrinsic_setjmpex(jmp_buf buf, void *frame);
extern int __attribute__((alias(__MINGW64_STRINGIFY(__MINGW_IMP_SYMBOL(_setjmpex)))))(__cdecl *__MINGW_IMP_SYMBOL(__intrinsic_setjmpex))(jmp_buf buf, void *frame);

#endif
