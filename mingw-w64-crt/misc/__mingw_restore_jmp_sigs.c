/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <setjmp.h>
#include <signal.h>

void __cdecl __mingw_restore_jmp_sigs(sigjmp_buf _SigBuf)
{
  _SIGJUMP_BUFFER *sigbuf = (void *)_SigBuf;
  if (sigbuf->sigs_saved) {
    signal(SIGINT, sigbuf->sigint);
    signal(SIGILL, sigbuf->sigill);
    signal(SIGFPE, sigbuf->sigfpe);
    signal(SIGSEGV, sigbuf->sigsegv);
    signal(SIGTERM, sigbuf->sigterm);
    signal(SIGBREAK, sigbuf->sigbreak);
    signal(SIGABRT, sigbuf->sigabrt);
  }
}
