/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <time.h>

wchar_t *__cdecl _wasctime(const struct tm *tm)
{
    static wchar_t wbuf[26]; /* this buffer is shared with all threads, so this _wasctime() emulation is not thread safe */
    const char *abuf;
    int i;

    abuf = asctime(tm);
    for (i = 0; abuf[i] && i < 25; i++)
        wbuf[i] = (wchar_t)abuf[i];
    wbuf[i] = L'\0';

    return wbuf;
}
wchar_t *__cdecl (*__MINGW_IMP_SYMBOL(_wasctime))(const struct tm *) = _wasctime;
