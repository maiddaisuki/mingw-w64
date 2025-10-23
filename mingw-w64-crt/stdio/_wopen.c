/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdarg.h>
#include <share.h>
#include <fcntl.h>
#include <io.h>

int __cdecl _wopen(const wchar_t *filename, int flags, ...)
{
    if (flags & O_CREAT) {
        int mode;
        va_list ap;
        va_start(ap, flags);
        mode = va_arg(ap, int);
        va_end(ap);
        return _wsopen(filename, flags, SH_DENYNO, mode);
    } else {
        return _wsopen(filename, flags, SH_DENYNO);
    }
}
int __cdecl (*__MINGW_IMP_SYMBOL(_wopen))(const wchar_t *, int, ...) = _wopen;
