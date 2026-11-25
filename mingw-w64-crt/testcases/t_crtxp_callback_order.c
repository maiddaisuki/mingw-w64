#include <stdio.h>
#include <stdlib.h>
#include <process.h>

#ifndef _MSC_VER
/* mingw-w64 headers */
#include "libtest.h"
#endif

#ifdef DLL_BUILD
#define puts(str) puts("DLL: " str)
#endif

#ifndef _MSC_VER
#define _CRTALLOC(x) __attribute__((section(x), used))
#else
#define _CRTALLOC(x) __pragma(section(x, long, read)) __declspec(allocate(x))
#endif

typedef void (__cdecl *_PVFV)(void);
typedef int (__cdecl *_PIFV)(void);

static int main_success = 0;
static int atexit_main_called = 0;
#ifndef _MSC_VER
static int atexit_ctor65535_called = 0;
static int atexit_ctor101_called = 0;
static int atexit_ctor_called = 0;
#endif
static int atexit_crtxcy_called = 0;
static int atexit_crtxcb_called = 0;
static int atexit_crtxiy_called = 0;
static int atexit_crtxib_called = 0;
#ifndef _MSC_VER
static int dtor65535_called = 0;
static int dtor101_called = 0;
static int dtor_called = 0;
#endif
static int crtxpb_called = 0;

/* .CRT$XPW is the last callback in msvc which has CRT stdio access */
#ifndef DLL_BUILD
__declspec(noreturn)
#endif
static void __cdecl crtxpw_callback(void)
{
  puts(".CRT$XPW callback");
  if (main_success == 1 &&
      atexit_main_called == 1 &&
#ifndef _MSC_VER
      atexit_ctor65535_called == 1 &&
      atexit_ctor101_called == 1 &&
      atexit_ctor_called == 1 &&
#endif
      atexit_crtxcy_called == 1 &&
      atexit_crtxcb_called == 1 &&
      atexit_crtxiy_called == 1 &&
      atexit_crtxib_called == 1 &&
#ifndef _MSC_VER
      dtor65535_called == 1 &&
      dtor101_called == 1 &&
      dtor_called == 1 &&
#endif
      crtxpb_called == 1) {
    puts("SUCCESS all callbacks were called");
#ifdef DLL_BUILD
    if (all_callbacks_called_ptr)
      *all_callbacks_called_ptr = 1;
#else
    _exit(0);
#endif
  } else {
    if (!main_success)
      puts("Error: main failed");
    if (!atexit_main_called)
      puts("Error: atexit callback from main was not called");
#ifndef _MSC_VER
    if (!atexit_ctor65535_called)
      puts("Error: atexit callback from __attribute__((constructor(65535))) was not called");
    if (!atexit_ctor101_called)
      puts("Error: atexit callback from __attribute__((constructor(101))) was not called");
    if (!atexit_ctor_called)
      puts("Error: atexit callback from __attribute__((constructor)) was not called");
#endif
    if (!atexit_crtxcy_called)
      puts("Error: atexit callback from .CRT$XCY was not called");
    if (!atexit_crtxcb_called)
      puts("Error: atexit callback from .CRT$XCB was not called");
    if (!atexit_crtxiy_called)
      puts("Error: atexit callback from .CRT$XIY was not called");
    if (!atexit_crtxib_called)
      puts("Error: atexit callback from .CRT$XIB was not called");
#ifndef _MSC_VER
    if (!dtor65535_called)
      puts("Error: __attribute__((destructor(65535))) callback was not called");
    if (!dtor101_called)
      puts("Error: __attribute__((destructor(101))) callback was not called");
    if (!dtor_called)
      puts("Error: __attribute__((destructor)) callback was not called");
#endif
    if (!crtxpb_called)
      puts("Error: .CRT$XPB callback was not called");
    _exit(1);
  }
}
_CRTALLOC(".CRT$XPW") static const _PVFV crtxpw_callback_ptr = crtxpw_callback;

#ifndef _MSC_VER
__attribute__((destructor))
static void dtor_callback(void)
{
  puts("__attribute__((destructor)) callback");
  dtor_called = 1;
}

__attribute__((destructor(65535)))
static void dtor65535_callback(void)
{
  puts("__attribute__((destructor(65535))) callback");
  dtor65535_called = 1;
}
#endif

static void __cdecl crtxpb_callback(void)
{
  puts(".CRT$XPB callback");
  crtxpb_called = 1;
}
_CRTALLOC(".CRT$XPB") static const _PVFV crtxpb_callback_ptr = crtxpb_callback;

#ifndef _MSC_VER
__attribute__((destructor(101)))
static void dtor101_callback(void)
{
  puts("__attribute__((destructor(101))) callback");
  dtor101_called = 1;
}
#endif

static void __cdecl atexit_callback_from_main(void)
{
  puts("atexit callback from main");
  atexit_main_called = 1;
}

static void __cdecl atexit_callback_from_crtxib(void)
{
  puts("atexit callback from .CRT$XIB");
  atexit_crtxib_called = 1;
}

static void __cdecl atexit_callback_from_crtxiy(void)
{
  puts("atexit callback from .CRT$XIY");
  atexit_crtxiy_called = 1;
}

static void __cdecl atexit_callback_from_crtxcb(void)
{
  puts("atexit callback from .CRT$XCB");
  atexit_crtxcb_called = 1;
}

static void __cdecl atexit_callback_from_crtxcy(void)
{
  puts("atexit callback from .CRT$XCY");
  atexit_crtxcy_called = 1;
}

#ifndef _MSC_VER
static void __cdecl atexit_callback_from_ctor(void)
{
  puts("atexit callback from __attribute__((constructor))");
  atexit_ctor_called = 1;
}

static void __cdecl atexit_callback_from_ctor101(void)
{
  puts("atexit callback from __attribute__((constructor(101)))");
  atexit_ctor101_called = 1;
}

static void __cdecl atexit_callback_from_ctor65535(void)
{
  puts("atexit callback from __attribute__((constructor(65535)))");
  atexit_ctor65535_called = 1;
}
#endif

static int __cdecl crtxib_callback(void)
{
  if (atexit(atexit_callback_from_crtxib) != 0) {
    puts("Error: .CRT$XIB: atexit() failed");
    _exit(1);
  }
  return 0;
}
_CRTALLOC(".CRT$XIB") static const _PIFV crtxib_callback_ptr = crtxib_callback;

static int __cdecl crtxiy_callback(void)
{
  if (atexit(atexit_callback_from_crtxiy) != 0) {
    puts("Error: .CRT$XIY: atexit() failed");
    _exit(1);
  }
  return 0;
}
_CRTALLOC(".CRT$XIY") static const _PIFV crtxiy_callback_ptr = crtxiy_callback;

static void __cdecl crtxcb_callback(void)
{
  if (atexit(atexit_callback_from_crtxcb) != 0) {
    puts("Error: .CRT$XCB: atexit() failed");
    _exit(1);
  }
}
_CRTALLOC(".CRT$XCB") static const _PVFV crtxcb_callback_ptr = crtxcb_callback;

static void __cdecl crtxcy_callback(void)
{
  if (atexit(atexit_callback_from_crtxcy) != 0) {
    puts("Error: .CRT$XCY: atexit() failed");
    _exit(1);
  }
}
_CRTALLOC(".CRT$XCY") static const _PVFV crtxcy_callback_ptr = crtxcy_callback;

#ifndef _MSC_VER
__attribute__((constructor))
static void ctor_callback(void)
{
  if (atexit(atexit_callback_from_ctor) != 0) {
    puts("Error: __attribute__((constructor)): atexit() failed");
    _exit(1);
  }
}

__attribute__((constructor(65535)))
static void ctor65535_callback(void)
{
  if (atexit(atexit_callback_from_ctor65535) != 0) {
    puts("Error: __attribute__((constructor(65535))): atexit() failed");
    _exit(1);
  }
}

__attribute__((constructor(101)))
static void ctor101_callback(void)
{
  if (atexit(atexit_callback_from_ctor101) != 0) {
    puts("Error: __attribute__((constructor(101))): atexit() failed");
    _exit(1);
  }
}
#endif

#ifdef DLL_BUILD

int __stdcall DllMain(void *handle, unsigned long reason, void *reserved)
{
  (void)handle;
  (void)reserved;
  if (reason == 1 /*DLL_PROCESS_ATTACH*/) {
    if (atexit(atexit_callback_from_main) != 0) {
      puts("Error: main: atexit() failed");
      _exit(1);
    }
  } else if (reason == 0 /*DLL_PROCESS_DETACH*/) {
    puts("main: Checking if the .CRT$XPW callback would be called after all atexit callbacks...");
    main_success = 1;
  }
  return 1;
}

#else

int main(void)
{
#ifndef _MSC_VER
  mingw_test_init();
#else
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
#endif

  if (atexit(atexit_callback_from_main) != 0) {
    puts("Error: main: atexit() failed");
    _exit(1);
  }

#ifndef NO_DLL_TEST
  {
    int dll_all_callbacks_called = 0;
    void (__cdecl*setvar)(int*) = NULL;
    intptr_t libcrtxp = _loaddll("libcrtxp.dll");
    if (!libcrtxp) {
      puts("Error: main: Cannot load libcrtxp.dll");
      _exit(1);
    }
    setvar = (void(__cdecl*)(int*))(void(*)(void))_getdllprocaddr(libcrtxp, "setvar", -1);
    if (!setvar) {
      puts("Error: main: Cannot resolve setvar from libcrtxp.dll");
      _exit(1);
    }
    setvar(&dll_all_callbacks_called);
    _unloaddll(libcrtxp);
    if (!dll_all_callbacks_called) {
      puts("Error: main: Some DLL callback was not called");
      _exit(1);
    }
  }
#endif

  puts("main: Checking if the .CRT$XPW callback would be called after all atexit callbacks...");
  main_success = 1;
  return 1; /* .CRT$XPW callback changes return code to 0 */
}

#endif
