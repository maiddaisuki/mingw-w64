/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdio.h>
#include <errno.h>
#include <share.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

FILE *__cdecl _wfsopen(const wchar_t *restrict filename, const wchar_t *restrict mode, int shflag)
{
  const wchar_t *ch;
  FILE *file;
  int flags;
  int fd;

  ch = mode;
  flags = 0;

  while (*ch == L' ')
    ch++;

  if (*ch == L'r')
    flags |= O_RDONLY;
  else if (*ch == L'w')
    flags |= O_WRONLY | O_CREAT | O_TRUNC;
  else if (*ch == L'a')
    flags |= O_WRONLY | O_CREAT | O_APPEND;
  else {
    errno = EINVAL;
    return NULL;
  }

  while (*++ch) {
    if (*ch == L' ')
      continue;
    if (*ch == L'+') {
      if (flags & O_RDWR) {
        errno = EINVAL;
        return NULL;
      }
      flags &= ~(O_RDONLY | O_WRONLY);
      flags |= O_RDWR;
    } else if (*ch == L'b') {
      if (flags & (O_BINARY | O_TEXT)) {
        errno = EINVAL;
        return NULL;
      }
      flags |= O_BINARY;
    } else if (*ch == L't') {
      if (flags & (O_BINARY | O_TEXT)) {
        errno = EINVAL;
        return NULL;
      }
      flags |= O_TEXT;
    } else if (*ch == L'S') {
      if (flags & (O_SEQUENTIAL | O_RANDOM)) {
        errno = EINVAL;
        return NULL;
      }
      flags |= O_SEQUENTIAL;
    } else if (*ch == L'R') {
      if (flags & (O_SEQUENTIAL | O_RANDOM)) {
        errno = EINVAL;
        return NULL;
      }
      flags |= O_RANDOM;
    } else if (*ch == L'T') {
      if (flags & _O_SHORT_LIVED) {
        errno = EINVAL;
        return NULL;
      }
      flags |= _O_SHORT_LIVED;
    } else if (*ch == L'D') {
      if (flags & O_TEMPORARY) {
        errno = EINVAL;
        return NULL;
      }
      flags |= O_TEMPORARY;
    } else if (*ch == L'N') {
      /* msvcrt allows repeated N characters in mode */
      flags |= O_NOINHERIT;
    } else {
      errno = EINVAL;
      return NULL;
    }
  }

  if (flags & O_CREAT)
    fd = _wsopen(filename, flags, shflag, S_IREAD | S_IWRITE);
  else
    fd = _wsopen(filename, flags, shflag);
  if (fd < 0)
    return NULL;

  file = _wfdopen(fd, mode);
  if (!file)
    close(fd);
  return file;
}
FILE *__cdecl (*__MINGW_IMP_SYMBOL(_wfsopen))(const wchar_t *restrict, const wchar_t *restrict, int) = _wfsopen;
