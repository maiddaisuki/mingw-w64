/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <fcntl.h>
#include <io.h>

int __cdecl _wcreat(const wchar_t *filename, int mode)
{
    return _wopen(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
}
int __cdecl (*__MINGW_IMP_SYMBOL(_wcreat))(const wchar_t *, int) = _wcreat;
