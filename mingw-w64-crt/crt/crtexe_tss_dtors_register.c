/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 */

#include <threads.h>
#include <thread_local.h>
#include <sect_attribs.h>
#include <windows.h>

/* Register native PE TLS callback which will call the __mingw_tss_run_dtors_ptr() function. */
const int __mingw_tss_run_dtors_caller_provider = 1;
#if defined(__i386__)
int __mingw_tss_dtors_supported = 0;
#endif
extern void (__cdecl *const __mingw_tss_run_dtors_ptr)(void);
static void WINAPI tss_tls_callback(HANDLE __UNUSED_PARAM(handle), DWORD reason, LPVOID __UNUSED_PARAM(reserved))
{
  /* PE TLS callbacks for DLL builds are called before DllMain.
   * The __mingw_tss_run_dtors_ptr function invalidates tss data.
   * So use this PE TLS callback exclusively only for EXE builds. */
  if (reason == DLL_THREAD_DETACH)
    __mingw_tss_run_dtors_ptr();
  /* PE TLS callbacks are not being called on Win9x systems at all.
   * So on 32-bit x86 systems the dtors support is available only
   * if our PE TLS callback was called at least for DLL_PROCESS_ATTACH. */
#if defined(__i386__)
  if (reason == DLL_PROCESS_ATTACH)
    __mingw_tss_dtors_supported = 1;
#endif
}
static _CRTALLOC(".CRT$XLD") const PIMAGE_TLS_CALLBACK tls_callback_ptr = tss_tls_callback;

/* Force tlssup.c (_tls_used symbol for .tls linker section) to be linked.  */
extern const IMAGE_TLS_DIRECTORY _tls_used;
static __attribute__((destructor)) void _include_tls_used(void) { asm volatile ("" :: "r" (&_tls_used)); }
