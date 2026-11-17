#include <threads.h>
#include <stdlib.h>
#include <process.h>
#include <assert.h>

/* mingw-w64 headers */
#include "libtest.h"

__declspec(dllimport) int __cdecl lib1_tss_create(tss_t *key, tss_dtor_t dtor);
__declspec(dllimport) void __cdecl lib1_tss_delete(tss_t key);
__declspec(dllimport) void *__cdecl lib1_tss_get(tss_t key);
__declspec(dllimport) int __cdecl lib1_tss_set(tss_t key, void *val);

static int (__cdecl *lib2_tss_create)(tss_t *key, tss_dtor_t dtor);
static void (__cdecl *lib2_tss_delete)(tss_t key);
static void *(__cdecl *lib2_tss_get)(tss_t key);
static int (__cdecl *lib2_tss_set)(tss_t key, void *val);

static int test_key0 = 0;
static int test_key1 = 0;
static int test_key2 = 0;

static tss_t key0, key1, key2;
static mtx_t mtx0, mtx1;

static int dtor_called = 0;

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static void __cdecl dtor_no_check_func(void *val) {
  (void)val;
  (void)__atomic_add_fetch(&dtor_called, 1, __ATOMIC_SEQ_CST);
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static void __cdecl dtor_key0_val20_check_func(void *val) {
  assert(val == (void*)20);
  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  (void)__atomic_add_fetch(&dtor_called, 1, __ATOMIC_SEQ_CST);
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static void __cdecl dtor_key1_val21_check_func(void *val) {
  assert(val == (void*)21);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  (void)__atomic_add_fetch(&dtor_called, 1, __ATOMIC_SEQ_CST);
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static void __cdecl dtor_key2_val22_check_func(void *val) {
  assert(val == (void*)22);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  (void)__atomic_add_fetch(&dtor_called, 1, __ATOMIC_SEQ_CST);
}

/* dtor function is not supported on Win9x */
#define DTOR_FUNC(func) (_osplatform != 1 ? (func) : NULL)
#define DTOR_ASSERT(x) do { if (_osplatform != 1) assert(x); } while (0)

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static int __cdecl thrd_keys01_check_null_and_set_vals_20_21_func(void *arg) {
  (void)arg;

  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);

  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);

  assert(tss_set(key0, (void*)20) == thrd_success);

  assert(tss_get(key0) == (void*)20);
  assert(lib1_tss_get(key0) == (void*)20);

  assert(lib1_tss_set(key1, (void*)21) == thrd_success);

  assert(tss_get(key1) == (void*)21);
  assert(lib1_tss_get(key1) == (void*)21);

  return 0;
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static int __cdecl thrd_wait_mtx0_keys01_check_null_and_set_vals_20_21_func(void *arg) {
  (void)arg;

  assert(mtx_lock(&mtx0) == thrd_success);
  assert(mtx_unlock(&mtx0) == thrd_success);
  mtx_destroy(&mtx0);

  return thrd_keys01_check_null_and_set_vals_20_21_func(arg);
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static int __cdecl thrd_create_keys01_check_null_and_set_vals_20_21_func(void *arg) {
  (void)arg;

  assert(tss_create(&key0, DTOR_FUNC(dtor_key0_val20_check_func)) == thrd_success);
  test_key0 = 1;
  assert(lib1_tss_create(&key1, DTOR_FUNC(dtor_key1_val21_check_func)) == thrd_success);
  test_key1 = 1;

  return thrd_keys01_check_null_and_set_vals_20_21_func(arg);
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static int __cdecl thrd_wait_mtx1_key2_check_null_and_set_val_22_func(void *arg) {
  (void)arg;

  assert(mtx_lock(&mtx1) == thrd_success);
  assert(mtx_unlock(&mtx1) == thrd_success);
  mtx_destroy(&mtx1);

  assert(tss_get(key2) == NULL);
  assert(lib1_tss_get(key2) == NULL);
  assert(lib2_tss_get(key2) == NULL);

  assert(lib2_tss_set(key2, (void*)42) == thrd_success);
  assert(tss_get(key2) == (void*)42);
  assert(lib1_tss_get(key2) == (void*)42);
  assert(lib2_tss_get(key2) == (void*)42);

  assert(lib1_tss_set(key2, (void*)32) == thrd_success);
  assert(tss_get(key2) == (void*)32);
  assert(lib1_tss_get(key2) == (void*)32);
  assert(lib2_tss_get(key2) == (void*)32);

  assert(tss_set(key2, (void*)22) == thrd_success);
  assert(tss_get(key2) == (void*)22);
  assert(lib1_tss_get(key2) == (void*)22);
  assert(lib2_tss_get(key2) == (void*)22);

  return 0;
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static int __cdecl thrd_create_keys01_func(void *arg) {
  (void)arg;

  assert(tss_create(&key0, DTOR_FUNC(dtor_no_check_func)) == thrd_success);
  assert(lib1_tss_create(&key1, DTOR_FUNC(dtor_no_check_func)) == thrd_success);

  return 0;
}

#if defined(__i386__)
/* We need to make sure that we align the stack to 16 bytes for the sake of SSE */
__attribute__((force_align_arg_pointer))
#endif
static void __stdcall pe_tls_thread_attach_callback(void *handle __attribute__((unused)), unsigned long reason, void *reserved __attribute__((unused)))
{
  if (reason != 2)
    return;

  const struct {
    int test;
    tss_t key;
  } tests[] = {
    { test_key0, key0 },
    { test_key1, key1 },
    { test_key2, key2 },
  };

  for (unsigned i = 0; i < sizeof(tests)/sizeof(*tests); i++) {
    if (!tests[i].test)
      continue;

    assert(tss_get(tests[i].key) == NULL);
    assert(lib1_tss_get(tests[i].key) == NULL);
    if (lib2_tss_get)
      assert(lib2_tss_get(tests[i].key) == NULL);

    assert(tss_set(tests[i].key, (void*)60) == thrd_success);
    assert(tss_get(tests[i].key) == (void*)60);
    assert(lib1_tss_get(tests[i].key) == (void*)60);
    if (lib2_tss_get)
      assert(lib2_tss_get(tests[i].key) == (void*)60);

    assert(lib1_tss_set(tests[i].key, (void*)61) == thrd_success);
    assert(tss_get(tests[i].key) == (void*)61);
    assert(lib1_tss_get(tests[i].key) == (void*)61);
    if (lib2_tss_get)
      assert(lib2_tss_get(tests[i].key) == (void*)61);

    if (lib2_tss_set) {
      assert(lib2_tss_set(tests[i].key, (void*)62) == thrd_success);
      assert(tss_get(tests[i].key) == (void*)62);
      assert(lib1_tss_get(tests[i].key) == (void*)62);
      if (lib2_tss_get)
        assert(lib2_tss_get(tests[i].key) == (void*)62);
    }

    assert(tss_set(tests[i].key, NULL) == thrd_success);
  }
}

/* Register pe_tls_thread_attach_callback as PE TLS callback with the highest priority (=B) */
static __attribute__((section(".CRT$XLB"), used)) const void *register_pe_tls_thread_attach_callback = pe_tls_thread_attach_callback;

/* Force tlssup.c (_tls_used symbol for .tls linker section) to be linked */
extern const char _tls_used[];
static __attribute__((destructor)) void _include_tls_used(void) { asm volatile ("" :: "r" (&_tls_used)); }

int main() {
  mingw_test_init();

  int ret;
  intptr_t lib2;
  thrd_t thrd0, thrd1;


  /* simple test case that no dtor is called for NULL */

  assert(dtor_called == 0);
  assert(thrd_create(&thrd0, thrd_create_keys01_func, NULL) == thrd_success);
  assert(thrd_join(thrd0, &ret) == thrd_success);
  assert(ret == 0);
  assert(dtor_called == 0);
  lib1_tss_delete(key1);
  assert(dtor_called == 0);
  tss_delete(key0);
  assert(dtor_called == 0);


  /* test case with sharing values between tss from EXE and tss from linked lib1 DLL */

  assert(dtor_called == 0);
  assert(thrd_create(&thrd0, thrd_create_keys01_check_null_and_set_vals_20_21_func, NULL) == thrd_success);
  assert(thrd_join(thrd0, &ret) == thrd_success);
  assert(ret == 0);
  DTOR_ASSERT(dtor_called == 2);
  dtor_called = 0;

  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);

  assert(tss_set(key0, (void*)10) == thrd_success);
  assert(tss_get(key0) == (void*)10);
  assert(lib1_tss_get(key0) == (void*)10);

  assert(lib1_tss_set(key1, (void*)11) == thrd_success);
  assert(tss_get(key1) == (void*)11);
  assert(lib1_tss_get(key1) == (void*)11);

  assert(dtor_called == 0);
  assert(thrd_create(&thrd0, thrd_keys01_check_null_and_set_vals_20_21_func, NULL) == thrd_success);
  assert(thrd_join(thrd0, &ret) == thrd_success);
  assert(ret == 0);
  DTOR_ASSERT(dtor_called == 2);
  dtor_called = 0;

  assert(tss_get(key0) == (void*)10);
  assert(lib1_tss_get(key0) == (void*)10);

  assert(tss_get(key1) == (void*)11);
  assert(lib1_tss_get(key1) == (void*)11);

  test_key1 = 0;
  lib1_tss_delete(key1);
  assert(dtor_called == 0);
  assert(tss_get(key0) == (void*)10);
  test_key0 = 0;
  tss_delete(key0);
  assert(dtor_called == 0);


  /* test case with sharing values between tss from EXE and tss from linked lib1 DLL and tss from dynamicalled loaded lib2 DLL */

  assert(tss_create(&key0, DTOR_FUNC(dtor_key0_val20_check_func)) == thrd_success);
  assert(lib1_tss_create(&key1, DTOR_FUNC(dtor_key1_val21_check_func)) == thrd_success);
  test_key0 = 1;
  test_key1 = 1;

  assert(mtx_init(&mtx0, mtx_plain) == thrd_success);
  assert(mtx_lock(&mtx0) == thrd_success);
  assert(thrd_create(&thrd0, thrd_wait_mtx0_keys01_check_null_and_set_vals_20_21_func, NULL) == thrd_success);

  assert(mtx_init(&mtx1, mtx_plain) == thrd_success);
  assert(mtx_lock(&mtx1) == thrd_success);
  assert(thrd_create(&thrd1, thrd_wait_mtx1_key2_check_null_and_set_val_22_func, NULL) == thrd_success);

  assert(tss_set(key0, (void*)30) == thrd_success);
  assert(tss_get(key0) == (void*)30);
  assert(lib1_tss_get(key0) == (void*)30);

  assert(lib1_tss_set(key1, (void*)31) == thrd_success);
  assert(tss_get(key1) == (void*)31);
  assert(lib1_tss_get(key1) == (void*)31);

  lib2 = _loaddll("libtss2.dll");
  assert(lib2);

  lib2_tss_create = (__typeof(lib2_tss_create))(void(*)(void))_getdllprocaddr(lib2, "lib2_tss_create", -1);
  assert(lib2_tss_create);
  lib2_tss_delete = (__typeof(lib2_tss_delete))(void(*)(void))_getdllprocaddr(lib2, "lib2_tss_delete", -1);
  assert(lib2_tss_delete);
  lib2_tss_get = (__typeof(lib2_tss_get))(void(*)(void))_getdllprocaddr(lib2, "lib2_tss_get", -1);
  assert(lib2_tss_get);
  lib2_tss_set = (__typeof(lib2_tss_set))(void(*)(void))_getdllprocaddr(lib2, "lib2_tss_set", -1);
  assert(lib2_tss_set);

  assert(dtor_called == 0);
  assert(mtx_unlock(&mtx0) == thrd_success);
  assert(thrd_join(thrd0, &ret) == thrd_success);
  DTOR_ASSERT(dtor_called == 2);
  dtor_called = 0;

  assert(lib2_tss_get(key0) == (void*)30);
  assert(lib2_tss_get(key1) == (void*)31);

  assert(lib2_tss_create(&key2, dtor_key2_val22_check_func) == thrd_success);
  test_key2 = 1;

  assert(dtor_called == 0);
  assert(mtx_unlock(&mtx1) == thrd_success);
  assert(thrd_join(thrd1, &ret) == thrd_success);
  DTOR_ASSERT(dtor_called == 1);
  dtor_called = 0;

  assert(dtor_called == 0);
  assert(thrd_create(&thrd0, thrd_keys01_check_null_and_set_vals_20_21_func, NULL) == thrd_success);
  assert(thrd_join(thrd0, &ret) == thrd_success);
  assert(ret == 0);
  DTOR_ASSERT(dtor_called == 2);
  dtor_called = 0;

  assert(dtor_called == 0);
  test_key0 = 0;
  tss_delete(key0);
  assert(dtor_called == 0);
  test_key1 = 0;
  tss_delete(key1);
  assert(dtor_called == 0);
  test_key2 = 0;
  tss_delete(key2);
  assert(dtor_called == 0);

  lib2_tss_create = NULL;
  lib2_tss_delete = NULL;
  lib2_tss_get = NULL;
  lib2_tss_set = NULL;
  assert(_unloaddll(lib2) == 0);
  assert(dtor_called == 0);

  return 0;
}
