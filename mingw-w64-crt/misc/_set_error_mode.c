/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <stdlib.h>

int __cdecl _set_error_mode(int mode_val)
{
  /* Dummy implementation for pre-msvcrt40 builds where assert() always sends
   * error message to stderr independently of what was set via __set_app_type().
   * No change in this behavior is possible, so just validate input argument and
   * always return _OUT_TO_STDERR or -1.
   */
  switch (mode_val) {
    case _OUT_TO_DEFAULT:
    case _OUT_TO_STDERR:
    case _OUT_TO_MSGBOX:
    case _REPORT_ERRMODE:
      return _OUT_TO_STDERR;
    default:
      return -1;
  }
}
int (__cdecl *__MINGW_IMP_SYMBOL(_set_error_mode))(int) = _set_error_mode;
