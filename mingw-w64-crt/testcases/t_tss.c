#include <threads.h>
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

static int (__cdecl *vcrthrds_tss_create)(tss_t *key, tss_dtor_t dtor);
static void (__cdecl *vcrthrds_tss_delete)(tss_t key);
static void *(__cdecl *vcrthrds_tss_get)(tss_t key);
static int (__cdecl *vcrthrds_tss_set)(tss_t key, void *val);

static int dtor_called = 0;
static void __cdecl dtor(void *val) {
  (void)val;
  dtor_called = 1;
}

int main() {
  mingw_test_init();

  intptr_t lib2, vcrthrds;
  tss_t key0, key1, key2, key3;

  assert(tss_create(&key0, NULL) == thrd_success);
  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  assert(tss_set(key0, (void*)1) == thrd_success);
  assert(lib1_tss_get(key0) == (void*)1);
  assert(tss_get(key0) == (void*)1);
  assert(lib1_tss_set(key0, (void*)2) == thrd_success);
  assert(lib1_tss_get(key0) == (void*)2);
  assert(tss_get(key0) == (void*)2);
  tss_delete(key0);
  assert(!dtor_called);

  assert(tss_create(&key0, dtor) == thrd_success);
  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  assert(tss_set(key0, (void*)1) == thrd_success);
  lib1_tss_delete(key0);
  assert(!dtor_called);

  assert(tss_create(&key0, NULL) == thrd_success);
  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  assert(tss_set(key0, (void*)1) == thrd_success);
  tss_delete(key0);
  assert(!dtor_called);

  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(tss_set(key1, (void*)1) == thrd_success);
  assert(lib1_tss_get(key1) == (void*)1);
  assert(tss_get(key1) == (void*)1);
  assert(lib1_tss_set(key1, (void*)2) == thrd_success);
  assert(lib1_tss_get(key1) == (void*)2);
  assert(tss_get(key1) == (void*)2);
  lib1_tss_delete(key1);
  assert(!dtor_called);

  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(tss_set(key1, (void*)1) == thrd_success);
  tss_delete(key1);
  assert(!dtor_called);

  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(tss_set(key1, (void*)1) == thrd_success);
  lib1_tss_delete(key1);
  assert(!dtor_called);

  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(lib1_tss_set(key1, (void*)1) == thrd_success);
  tss_delete(key1);
  assert(!dtor_called);

  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(lib1_tss_set(key1, (void*)1) == thrd_success);
  lib1_tss_delete(key1);
  assert(!dtor_called);

  assert(tss_create(&key0, dtor) == thrd_success);
  assert(lib1_tss_create(&key1, dtor) == thrd_success);
  assert(tss_get(key0) == NULL);
  assert(lib1_tss_get(key0) == NULL);
  assert(tss_get(key1) == NULL);
  assert(lib1_tss_get(key1) == NULL);
  assert(tss_set(key0, (void*)1) == thrd_success);
  assert(tss_get(key0) == (void*)1);
  assert(lib1_tss_get(key0) == (void*)1);
  assert(lib1_tss_set(key1, (void*)2) == thrd_success);
  assert(tss_get(key1) == (void*)2);
  assert(lib1_tss_get(key1) == (void*)2);

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

  assert(lib2_tss_get(key0) == (void*)1);
  assert(lib2_tss_get(key1) == (void*)2);

  assert(lib2_tss_create(&key2, NULL) == thrd_success);

  assert(lib2_tss_set(key0, (void*)10) == thrd_success);
  assert(lib1_tss_get(key0) == (void*)10);
  assert(tss_get(key0) == (void*)10);

  assert(tss_get(key2) == NULL);
  assert(lib1_tss_get(key2) == NULL);
  assert(lib2_tss_get(key2) == NULL);

  assert(tss_set(key2, (void*)20) == thrd_success);
  assert(lib2_tss_get(key2) == (void*)20);
  assert(lib1_tss_get(key2) == (void*)20);
  assert(tss_get(key2) == (void*)20);
  assert(lib2_tss_get(key1) == (void*)2);
  assert(lib1_tss_get(key1) == (void*)2);
  assert(tss_get(key1) == (void*)2);
  assert(lib2_tss_get(key0) == (void*)10);
  assert(lib1_tss_get(key0) == (void*)10);
  assert(tss_get(key0) == (void*)10);

  assert(lib1_tss_set(key2, (void*)21) == thrd_success);
  assert(lib2_tss_get(key2) == (void*)21);
  assert(lib1_tss_get(key2) == (void*)21);
  assert(tss_get(key2) == (void*)21);
  assert(lib2_tss_get(key1) == (void*)2);
  assert(lib1_tss_get(key1) == (void*)2);
  assert(tss_get(key1) == (void*)2);
  assert(lib2_tss_get(key0) == (void*)10);
  assert(lib1_tss_get(key0) == (void*)10);
  assert(tss_get(key0) == (void*)10);

  assert(lib2_tss_set(key2, (void*)22) == thrd_success);
  assert(lib2_tss_get(key2) == (void*)22);
  assert(lib1_tss_get(key2) == (void*)22);
  assert(tss_get(key2) == (void*)22);
  assert(lib2_tss_get(key1) == (void*)2);
  assert(lib1_tss_get(key1) == (void*)2);
  assert(tss_get(key1) == (void*)2);
  assert(lib2_tss_get(key0) == (void*)10);
  assert(lib1_tss_get(key0) == (void*)10);
  assert(tss_get(key0) == (void*)10);

  vcrthrds = _loaddll("vcruntime140_threads.dll");
  if (vcrthrds) {
    vcrthrds_tss_create = (__typeof(vcrthrds_tss_create))(void(*)(void))_getdllprocaddr(vcrthrds, "tss_create", -1);
    assert(vcrthrds_tss_create);
    vcrthrds_tss_delete = (__typeof(vcrthrds_tss_delete))(void(*)(void))_getdllprocaddr(vcrthrds, "tss_delete", -1);
    assert(vcrthrds_tss_delete);
    vcrthrds_tss_get = (__typeof(vcrthrds_tss_get))(void(*)(void))_getdllprocaddr(vcrthrds, "tss_get", -1);
    assert(vcrthrds_tss_get);
    vcrthrds_tss_set = (__typeof(vcrthrds_tss_set))(void(*)(void))_getdllprocaddr(vcrthrds, "tss_set", -1);
    assert(vcrthrds_tss_set);

    assert(vcrthrds_tss_create(&key3, dtor) == thrd_success);
    assert(vcrthrds_tss_get(key3) == NULL);
    assert(tss_get(key3) == NULL);
    assert(lib1_tss_get(key3) == NULL);
    assert(lib2_tss_get(key3) == NULL);

    assert(vcrthrds_tss_set(key3, (void*)100) == thrd_success);
    assert(tss_get(key3) == (void*)100);
    assert(lib1_tss_get(key3) == (void*)100);
    assert(lib2_tss_get(key3) == (void*)100);
    assert(vcrthrds_tss_get(key3) == (void*)100);

    assert(tss_set(key3, (void*)101) == thrd_success);
    assert(tss_get(key3) == (void*)101);
    assert(lib1_tss_get(key3) == (void*)101);
    assert(lib2_tss_get(key3) == (void*)101);
    assert(vcrthrds_tss_get(key3) == (void*)101);

    assert(lib1_tss_set(key3, (void*)102) == thrd_success);
    assert(tss_get(key3) == (void*)102);
    assert(lib1_tss_get(key3) == (void*)102);
    assert(lib2_tss_get(key3) == (void*)102);
    assert(vcrthrds_tss_get(key3) == (void*)102);

    assert(lib2_tss_set(key3, (void*)103) == thrd_success);
    assert(tss_get(key3) == (void*)103);
    assert(lib1_tss_get(key3) == (void*)103);
    assert(lib2_tss_get(key3) == (void*)103);
    assert(vcrthrds_tss_get(key3) == (void*)103);

    assert(vcrthrds_tss_set(key3, (void*)104) == thrd_success);
    assert(tss_get(key3) == (void*)104);
    assert(lib1_tss_get(key3) == (void*)104);
    assert(lib2_tss_get(key3) == (void*)104);
    assert(vcrthrds_tss_get(key3) == (void*)104);

    vcrthrds_tss_delete(key3);
    assert(!dtor_called);

    /* vcrthrds_tss_create -> tss_delete */
    assert(vcrthrds_tss_create(&key3, dtor) == thrd_success);
    assert(vcrthrds_tss_get(key3) == NULL);
    assert(tss_get(key3) == NULL);
    assert(lib1_tss_get(key3) == NULL);
    assert(lib2_tss_get(key3) == NULL);
    assert(vcrthrds_tss_set(key3, (void*)105) == thrd_success);
    assert(tss_get(key3) == (void*)105);
    tss_delete(key3);
    assert(!dtor_called);

    /* vcrthrds_tss_create -> lib1_tss_delete */
    assert(vcrthrds_tss_create(&key3, dtor) == thrd_success);
    assert(vcrthrds_tss_get(key3) == NULL);
    assert(tss_get(key3) == NULL);
    assert(lib1_tss_get(key3) == NULL);
    assert(lib2_tss_get(key3) == NULL);
    assert(vcrthrds_tss_set(key3, (void*)106) == thrd_success);
    assert(tss_get(key3) == (void*)106);
    lib1_tss_delete(key3);
    assert(!dtor_called);

    /* vcrthrds_tss_create -> lib2_tss_delete */
    assert(vcrthrds_tss_create(&key3, dtor) == thrd_success);
    assert(vcrthrds_tss_get(key3) == NULL);
    assert(tss_get(key3) == NULL);
    assert(lib1_tss_get(key3) == NULL);
    assert(lib2_tss_get(key3) == NULL);
    assert(vcrthrds_tss_set(key3, (void*)107) == thrd_success);
    assert(tss_get(key3) == (void*)107);
    lib2_tss_delete(key3);
    assert(!dtor_called);

    assert(_unloaddll(vcrthrds) == 0);
  }

  assert(_unloaddll(lib2) == 0);
  assert(!dtor_called);

  assert(lib1_tss_get(key1) == (void*)2);
  assert(tss_get(key1) == (void*)2);
  assert(lib1_tss_get(key0) == (void*)10);
  assert(tss_get(key0) == (void*)10);

  lib1_tss_delete(key1);
  assert(!dtor_called);

  assert(tss_get(key0) == (void*)10);

  tss_delete(key0);
  assert(!dtor_called);

  return 0;
}
