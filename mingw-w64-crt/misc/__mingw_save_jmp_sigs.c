/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <setjmp.h>
#include <signal.h>

static __p_sig_fn_t get_sighandler(int sig)
{
  /* pre-msvcr80 libraries do not support SIG_GET and sets the signal handler to SIG_GET.
   * Detect this behavior and restore the signal handler back. */
  __p_sig_fn_t handler = signal(sig, SIG_GET);
  if (signal(sig, SIG_GET) == SIG_GET)
    signal(sig, handler);
  return handler;
}

void __cdecl __mingw_save_jmp_sigs(sigjmp_buf _SigBuf, int _SaveSigs)
{
  _SIGJUMP_BUFFER *sigbuf = (void *)_SigBuf;
  if (_SaveSigs) {
    sigbuf->sigs_saved = 1;
    sigbuf->sigint = get_sighandler(SIGINT);
    sigbuf->sigill = get_sighandler(SIGILL);
    sigbuf->sigfpe = get_sighandler(SIGFPE);
    sigbuf->sigsegv = get_sighandler(SIGSEGV);
    sigbuf->sigterm = get_sighandler(SIGTERM);
    sigbuf->sigbreak = get_sighandler(SIGBREAK);
    sigbuf->sigabrt = get_sighandler(SIGABRT);
  } else {
    sigbuf->sigs_saved = 0;
    sigbuf->sigint = NULL;
    sigbuf->sigill = NULL;
    sigbuf->sigfpe = NULL;
    sigbuf->sigsegv = NULL;
    sigbuf->sigterm = NULL;
    sigbuf->sigbreak = NULL;
    sigbuf->sigabrt = NULL;
  }
}
