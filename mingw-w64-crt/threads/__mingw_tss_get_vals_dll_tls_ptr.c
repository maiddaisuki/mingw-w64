/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))

#include <windows.h> /* for LocalAlloc(), LocalFree(), TlsAlloc(), TlsFree(), TlsGetValue() and TlsSetValue() */

static DWORD tss_tls_key = TLS_OUT_OF_INDEXES;

/* Return pointer to WinAPI allocated TLS array where are stored values for all tss_t keys and their generations. */
static void **__cdecl tss_get_vals_dll_tls(void)
{
  return (void **)TlsGetValue(tss_tls_key);
}
void **(__cdecl *const __mingw_tss_get_vals_dll_tls_ptr)(void) = tss_get_vals_dll_tls;

static WINBOOL WINAPI tss_callback(HANDLE handle __attribute__((unused)), DWORD reason, LPVOID reserved __attribute__((unused)))
{
  if (reason == DLL_PROCESS_ATTACH) {
    tss_tls_key = TlsAlloc();
    if (tss_tls_key == TLS_OUT_OF_INDEXES)
      return FALSE;
  }

  if (reason == DLL_PROCESS_ATTACH || reason == DLL_THREAD_ATTACH) {
    /* TLS array contains space for storing values and generations for all 1024 tss_t keys. */
    void *tss_vals = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, 1024 * 2 * sizeof(void*));
    if (!tss_vals)
      return FALSE;
    if (!TlsSetValue(tss_tls_key, tss_vals)) {
      LocalFree(tss_vals);
      return FALSE;
    }
  }

  if (reason == DLL_PROCESS_DETACH || reason == DLL_THREAD_DETACH) {
    void *tss_vals = TlsGetValue(tss_tls_key);
    if (tss_vals) {
      TlsSetValue(tss_tls_key, NULL);
      LocalFree(tss_vals);
    }
  }

  if (reason == DLL_PROCESS_DETACH) {
    if (tss_tls_key != TLS_OUT_OF_INDEXES) {
      TlsFree(tss_tls_key);
      tss_tls_key = TLS_OUT_OF_INDEXES;
    }
  }

  return TRUE;
}
WINBOOL (WINAPI *const __mingw_tss_callback_ptr)(HANDLE,DWORD,LPVOID) = tss_callback;

#endif
