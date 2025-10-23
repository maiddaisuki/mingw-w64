/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdio.h>
#include <errno.h>

FILE *__cdecl _wfdopen(int fd, const wchar_t *wmode)
{
    char mode[128];
    size_t i;

    /* Convert 7-bit ASCII string stored in wchar_t* to char* */
    for (i = 0; i < sizeof(mode)-1 && wmode[i]; i++) {
        if (wmode[i] >= 0x80) {
            errno = EINVAL;
            return NULL;
        }
        mode[i] = wmode[i];
    }

    if (i >= sizeof(mode)-1) {
        errno = EINVAL;
        return NULL;
    }

    mode[i] = '\0';

    return _fdopen(fd, mode);
}
FILE *__cdecl (*__MINGW_IMP_SYMBOL(_wfdopen))(int, const wchar_t *) = _wfdopen;
