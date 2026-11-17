/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))

#include <windows.h> /* for LocalAlloc(), LocalFree(), TlsAlloc(), TlsFree(), TlsGetValue() and TlsSetValue() */

extern int __mingw_tss_register_interface(void);
extern void __mingw_tss_unregister_interface(void);

static DWORD tss_tls_key = TLS_OUT_OF_INDEXES;

static WINBOOL tss_alloc_tls_key(void)
{
  /* This function is called either from:
   * - tss_callback(DLL_PROCESS_ATTACH) which is called from crtdll.c DLL entry
   *   point when the DLL library is being loaded and hence under the system
   *   loader lock
   * - tss_get_vals_dll_tls() before the DLL library was fully loaded, which
   *   means before the tss_callback(DLL_PROCESS_ATTACH) was called, for example
   *   from PE TLS callback DLL_PROCESS_ATTACH
   * In both cases the call is begin done during the system loader lock and
   * therefore there is no thread concurrent access. So locking of tss_tls_key
   * is not needed.
   */
  tss_tls_key = TlsAlloc();
  if (tss_tls_key == TLS_OUT_OF_INDEXES)
    return FALSE;
  if (!__mingw_tss_register_interface()) {
    TlsFree(tss_tls_key);
    tss_tls_key = TLS_OUT_OF_INDEXES;
    return FALSE;
  }
  return TRUE;
}

static WINBOOL tss_alloc_vals(void)
{
  /* TLS array contains space for storing values and generations for all 1024 tss_t keys. */
  void *tss_vals = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, 1024 * 2 * sizeof(void*));
  if (!tss_vals)
    return FALSE;
  if (!TlsSetValue(tss_tls_key, tss_vals)) {
    LocalFree(tss_vals);
    return FALSE;
  }
  return TRUE;
}

/* Return pointer to WinAPI allocated TLS array where are stored values for all tss_t keys and their generations. */
static void **__cdecl tss_get_vals_dll_tls(void)
{
  void *tss_vals;
  if (__builtin_expect(tss_tls_key == TLS_OUT_OF_INDEXES, 0)) {
    if (!tss_alloc_tls_key())
      return NULL;
  }
  tss_vals = TlsGetValue(tss_tls_key);
  if (__builtin_expect(!tss_vals, 0)) {
    /* This can happen if the current thread was created before our DLL library was loaded from another thread. */
    if (!tss_alloc_vals())
      return NULL;
    tss_vals = TlsGetValue(tss_tls_key);
  }
  return (void **)tss_vals;
}
void **(__cdecl *const __mingw_tss_get_vals_dll_tls_ptr)(void) = tss_get_vals_dll_tls;

static WINBOOL WINAPI tss_callback(HANDLE handle __attribute__((unused)), DWORD reason, LPVOID reserved __attribute__((unused)))
{
  if (reason == DLL_PROCESS_ATTACH) {
    if (__builtin_expect(tss_tls_key == TLS_OUT_OF_INDEXES, 1)) {
      if (!tss_alloc_tls_key())
        return FALSE;
    }
  }

  if (reason == DLL_PROCESS_ATTACH || reason == DLL_THREAD_ATTACH) {
    if (__builtin_expect(!TlsGetValue(tss_tls_key), 1)) {
      if (!tss_alloc_vals())
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
    __mingw_tss_unregister_interface();
    if (tss_tls_key != TLS_OUT_OF_INDEXES) {
      TlsFree(tss_tls_key);
      tss_tls_key = TLS_OUT_OF_INDEXES;
    }
  }

  return TRUE;
}
WINBOOL (WINAPI *const __mingw_tss_callback_ptr)(HANDLE,DWORD,LPVOID) = tss_callback;

#endif
