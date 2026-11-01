/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include "../include/thread_local.h" /* __MINGW_ALLOC_THREAD_LOCAL() */

/* Native PE TLS is working reliable on pre-Vista systems only for EXE builds.
 * For DLL libraries on pre-Vista systems, this function can return bogus pointer.
 * So on pre-Vista systems, use this function exclusively only for EXE builds. */

/* Return pointer to native PE TLS array where are stored values for all tss_t keys and their generations. */
static void **__cdecl tss_get_vals_pe_tls_ptr(void)
{
  return __MINGW_ALLOC_THREAD_LOCAL(void*[1024 * 2]);
}
void **(__cdecl *const __mingw_tss_get_vals_pe_tls_ptr)(void) = tss_get_vals_pe_tls_ptr;
