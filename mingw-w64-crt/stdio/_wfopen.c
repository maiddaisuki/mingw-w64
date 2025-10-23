/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdio.h>
#include <share.h>

FILE *__cdecl _wfopen(const wchar_t *restrict filename, const wchar_t *restrict mode)
{
  return _wfsopen(filename, mode, SH_DENYNO);
}
FILE *__cdecl (*__MINGW_IMP_SYMBOL(_wfopen))(const wchar_t *restrict, const wchar_t *restrict) = _wfopen;
