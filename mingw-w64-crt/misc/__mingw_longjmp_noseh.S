/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <_mingw_mac.h>

#if defined(__i386__)
        .globl  __MINGW_USYMBOL(__mingw_longjmp_noseh)
        .def    __MINGW_USYMBOL(__mingw_longjmp_noseh); .scl 2; .type 32; .endef
__MINGW_USYMBOL(__mingw_longjmp_noseh):
        movl    4(%esp),%ecx         /* jmp_buf */
        movl    8(%esp),%eax         /* retval */
        cmpl    $1,%eax              /* check that retval is non-zero */
        adcl    $0,%eax              /* if not then increase by one via CF */
        movl    0(%ecx),%ebp         /* jmp_buf.Ebp */
        movl    4(%ecx),%ebx         /* jmp_buf.Ebx */
        movl    8(%ecx),%edi         /* jmp_buf.Edi */
        movl    12(%ecx),%esi        /* jmp_buf.Esi */
        movl    16(%ecx),%esp        /* jmp_buf.Esp */
        addl    $4,%esp              /* get rid of return address */
        jmp     *20(%ecx)            /* jmp_buf.Eip */
#endif
