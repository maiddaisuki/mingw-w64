/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdlib.h>
#include <wchar.h>
#include <errno.h>
#include <windows.h>

wchar_t *__cdecl _wfullpath(wchar_t *absPath, const wchar_t *relPath, size_t maxLength)
{
  BOOL free_on_error = FALSE;
  DWORD ret;

  if (!absPath) {
    absPath = calloc(_MAX_PATH, sizeof(wchar_t));
    if (!absPath) {
      errno = ENOMEM;
      return NULL;
    }
    free_on_error = TRUE;
  }

  if (!relPath || !relPath[0])
    relPath = L".";

  ret = GetFullPathNameW(relPath, maxLength, absPath, NULL);
  if (ret == 0 || ret >= maxLength) {
    if (free_on_error)
      free(absPath);
    errno = ret == 0 ? EINVAL : ERANGE;
    return NULL;
  }

  return absPath;
}
wchar_t *(__cdecl *__MINGW_IMP_SYMBOL(_wfullpath))(wchar_t *, const wchar_t *, size_t) = _wfullpath;
