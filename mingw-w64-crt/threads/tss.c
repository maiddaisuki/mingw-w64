/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>

extern void **(__cdecl *const __mingw_tss_get_vals_pe_tls_ptr)(void);

#if defined(__i386__)
extern int __mingw_tss_dtors_supported;
#endif

static void **tss_get_vals_ptr(void)
{
  return __mingw_tss_get_vals_pe_tls_ptr();
}

static tss_dtor_t tss_dtors[1024] = { NULL, };
static uintptr_t tss_dtors_gen[1024] = { 0, };

static void __cdecl tss_dtor_null(void *__UNUSED_PARAM(arg)) {} /* sentinel to indicate NULL dtor */

int __cdecl tss_create(tss_t *key, tss_dtor_t dtor)
{
  unsigned i;

#if defined(__i386__)
  /* On Win9x systems for EXE builds are dtors not supported. */
  if (!__mingw_tss_dtors_supported && dtor != NULL)
    return thrd_error;
#endif

  for (i = 0; i < 1024; i++) {
    /* Try to atomically store tss_dtor_null ptr to i-th dtor position if it is NULL. */
    if (__atomic_load_n(&tss_dtors[i], __ATOMIC_RELAXED))
      continue;
    if (__builtin_expect(!__atomic_compare_exchange_n(&tss_dtors[i], &(tss_dtor_t){NULL}, tss_dtor_null, 0, __ATOMIC_SEQ_CST, __ATOMIC_RELAXED), 0))
      continue;

    /* We have successfully allocated i-th dtor position.
     * Now increase the generation for i-th position.
     * If the generation overflows back to zero then let it locked
     * and do not use it because tss_get() cannot detect this overflow. */
    if (__builtin_expect(__atomic_add_fetch(&tss_dtors_gen[i], 1, __ATOMIC_SEQ_CST) == 0, 0))
      continue;

    /* Both i-th dtor and generation position was atomically allocated for us.
     * Store the real dtor, key idx and returns key. */
    if (dtor != NULL)
      __atomic_store_n(&tss_dtors[i], dtor, __ATOMIC_SEQ_CST);

    key->_Idx = i;
    return thrd_success;
  }

  /* vcruntime140_threads.dll tss_create returns thrd_error for memory limits */
  return thrd_error;
}

void __cdecl tss_delete(tss_t key)
{
  __atomic_store_n(&tss_dtors[key._Idx], NULL, __ATOMIC_SEQ_CST);
}

void *__cdecl tss_get(tss_t key)
{
  void **vals = tss_get_vals_ptr();
  uintptr_t *vals_gen = (uintptr_t*)&vals[1024];
  uintptr_t gen = __atomic_load_n(&tss_dtors_gen[key._Idx], __ATOMIC_RELAXED);
  if (__builtin_expect(vals_gen[key._Idx] != gen, 0)) {
    /* Stored value is invalid and for the current generation was not set yet.
     * The default TSS value for each key and tread is NULL. */
    vals[key._Idx] = NULL;
    vals_gen[key._Idx] = gen;
  }
  return vals[key._Idx];
}

int __cdecl tss_set(tss_t key, void *val)
{
  void **vals = tss_get_vals_ptr();
  uintptr_t *vals_gen = (uintptr_t*)&vals[1024];
  uintptr_t gen = __atomic_load_n(&tss_dtors_gen[key._Idx], __ATOMIC_RELAXED);
  vals[key._Idx] = val;
  vals_gen[key._Idx] = gen;
  return thrd_success;
}

static void __cdecl tss_run_dtors(void)
{
  void **vals = tss_get_vals_ptr();
  uintptr_t *vals_gen = (uintptr_t*)&vals[1024];
  uintptr_t copy_tss_dtors_gen[1024];
  unsigned i;

  _Static_assert(TSS_DTOR_ITERATIONS == 1, "TSS_DTOR_ITERATIONS is not 1");

  /* Read tss_dtors_gen and before dtors executions because TSS_DTOR_ITERATIONS is 1. */
  for (i = 0; i < 1024; i++)
    copy_tss_dtors_gen[i] = __atomic_load_n(&tss_dtors_gen[i], __ATOMIC_ACQUIRE);

  for (i = 0; i < 1024; i++) {
    /* Atomically read dtor pointer and validate if the read was atomic by
     * checking that generation was not changed (e.g. by parallel tss_delete
     * and tss_create calls). */
    tss_dtor_t dtor = __atomic_load_n(&tss_dtors[i], __ATOMIC_ACQUIRE);
    uintptr_t gen = __atomic_load_n(&tss_dtors_gen[i], __ATOMIC_ACQUIRE);
    if (gen != copy_tss_dtors_gen[i])
      continue;

    /* Check if the value is valid. */
    if (vals_gen[i] != gen)
      continue;

    if (dtor != NULL && dtor != tss_dtor_null && vals[i] != NULL)
      dtor(vals[i]);
  }
}
void (__cdecl *const __mingw_tss_run_dtors_ptr)(void) = tss_run_dtors;

/* Force inclusion of code which calls __mingw_tss_run_dtors_ptr */
extern const int __mingw_tss_run_dtors_caller_provider;
static __attribute__((used)) const void *const _include_mingw_tss_run_dtors_caller = &__mingw_tss_run_dtors_caller_provider;
