/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER.PD within this package.
 *
 * Written by Pali Rohár
 */

#include <threads.h>
#include <windows.h> /* for AddAtomA(), GetAtomNameA() and DeleteAtom() */

int __cdecl __mingw_tss_register_interface(void);
void __cdecl __mingw_tss_unregister_interface(void);

#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))
extern void **(__cdecl *const __mingw_tss_get_vals_dll_tls_ptr)(void);
#endif
extern void **(__cdecl *const __mingw_tss_get_vals_pe_tls_ptr)(void);

#if defined(__i386__)
extern int __mingw_tss_dtors_supported;
#endif

static void **tss_get_vals_ptr(void)
{
#if defined(__i386__) || (defined(__x86_64__) && !defined(__arm64ec__))
  /* crtdll.c and crtexe.c ensures that exactly one of these pointers is non-NULL */
  if (__mingw_tss_get_vals_dll_tls_ptr)
    return __mingw_tss_get_vals_dll_tls_ptr();
#endif
  return __mingw_tss_get_vals_pe_tls_ptr();
}

struct mingw_tss_interface
{
  void (__cdecl*tss_delete)(tss_t);
  void *(__cdecl*tss_get)(tss_t);
  int (__cdecl*tss_set)(tss_t,void*);
};

static const struct mingw_tss_interface tss_interface = {
  .tss_delete = &tss_delete,
  .tss_get = &tss_get,
  .tss_set = &tss_set,
};

static ATOM tss_atom = 0;

int __cdecl __mingw_tss_register_interface(void)
{
  char atom_name[12 + sizeof(void*)*2 + 1];
  const unsigned len = sizeof(void*)*2;
  unsigned char digit;
  unsigned i;

  if (tss_atom)
    return 0;

  /* Compose atom name in string format "mingw_tss_0xADDR" */
  __builtin_memcpy(atom_name, "mingw_tss_0x", 12);
  for (i = 0; i < len; i++) {
    digit = ((uintptr_t)&tss_interface >> (4*(len-i-1))) & 0xf;
    atom_name[12 + i] = digit > 9 ? (digit-0xA+'A') : (digit+'0');
  }
  atom_name[12 + len] = '\0';

  tss_atom = AddAtomA(atom_name);
  if (!tss_atom)
    return 0;

  return 1;
}

void __cdecl __mingw_tss_unregister_interface(void)
{
  if (!tss_atom)
    return;
  DeleteAtom(tss_atom);
  tss_atom = 0;
}

static struct mingw_tss_interface *tss_get_interface(ATOM atom)
{
  char atom_name[12 + sizeof(void*)*2 + 1];
  uintptr_t tss_address;
  unsigned char digit;
  unsigned atom_len;
  unsigned i;

  /* Retrieve pointer to the TSS interface of the foreign DLL/EXE module
   * identified by atom from the process local atom storage. */

  /* Atom name should have name "mingw_tss_0xADDR" */
  atom_len = GetAtomNameA(atom, atom_name, sizeof(atom_name));
  if (atom_len != sizeof(atom_name)-1 || __builtin_memcmp(atom_name, "mingw_tss_0x", 12) != 0)
    return NULL;

  /* Convert atom name in string format to the pointer address */
  tss_address = 0;
  for (i = 12; i < sizeof(atom_name)-1; i++) {
    if (atom_name[i] >= '0' && atom_name[i] <= '9')
      digit = atom_name[i] - '0';
    else if (atom_name[i] >= 'a' && atom_name[i] <= 'f')
      digit = atom_name[i] - 'a' + 0xa;
    else if (atom_name[i] >= 'A' && atom_name[i] <= 'F')
      digit = atom_name[i] - 'A' + 0xA;
    else
      return NULL;
    tss_address |= (uintptr_t)digit << (4*sizeof(void*)*2 - 4*(i-12+1));
  }

  return (struct mingw_tss_interface *)tss_address;
}

static tss_dtor_t tss_dtors[1024] = { NULL, };
static uintptr_t tss_dtors_gen[1024] = { 0, };

static void __cdecl tss_dtor_null(void *__UNUSED_PARAM(arg)) {} /* sentinel to indicate NULL dtor */

int __cdecl tss_create(tss_t *key, tss_dtor_t dtor)
{
  unsigned i;

  if (!tss_atom)
    return thrd_error;

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

    /* Layout of tss_t _Idx is:
     *               mingw-w64  vcruntime140_threads
     * high 16 bits    ATOM              0
     * mid   6 bits      0               0
     * low  10 bits     idx             idx
     * ATOM is always non-zero, idx can be zero.
     */
    key->_Idx = i | ((unsigned)tss_atom << 16);
    return thrd_success;
  }

  /* vcruntime140_threads.dll tss_create returns thrd_error for memory limits */
  return thrd_error;
}

void __cdecl tss_delete(tss_t key)
{
  ATOM atom = key._Idx >> 16;
  unsigned short unused = (key._Idx & 0xffff) & ~1023;
  unsigned short idx = key._Idx & 1023;

  /* If upper 22 bits of _Idx are zero then the key was
   * allocated by the vcruntime140_threads.dll tss_create.
   * So forward call to the vcruntime140_threads.dll. */
  if (__builtin_expect(unused == 0 && atom == 0, 0)) {
    static void (__cdecl*vcruntime_tss_delete)(tss_t) = NULL;
    if (!vcruntime_tss_delete) {
      HMODULE dll = GetModuleHandleA("vcruntime140_threads.dll");
      FARPROC proc = dll ? GetProcAddress(dll, "tss_delete") : NULL;
      if (!proc)
        return;
      __atomic_store_n(&vcruntime_tss_delete, (void(__cdecl*)(tss_t))(void(*)(void))proc, __ATOMIC_SEQ_CST);
    }
    vcruntime_tss_delete(key);
    return;
  }

  /* If the atom is valid (non-zero) but is not our then it belongs to the
   * foreign DLL/EXE module. So forward call to the interface for that atom. */
  if (__builtin_expect(atom != tss_atom && atom != 0, 0)) {
    struct mingw_tss_interface *tss_interface_ptr = tss_get_interface(atom);
    if (!tss_interface_ptr)
      return;
    tss_interface_ptr->tss_delete(key);
    return;
  }

  /* mingw-w64 tss_create sets _Idx unused bits to zero and atom to non-zero. */
  if (__builtin_expect(unused != 0 || atom == 0, 0))
    return;

  __atomic_store_n(&tss_dtors[idx], NULL, __ATOMIC_SEQ_CST);
}

void *__cdecl tss_get(tss_t key)
{
  ATOM atom = key._Idx >> 16;
  unsigned short unused = (key._Idx & 0xffff) & ~1023;
  unsigned short idx = key._Idx & 1023;

  /* If upper 22 bits of _Idx are zero then the key was
   * allocated by the vcruntime140_threads.dll tss_create.
   * So forward call to the vcruntime140_threads.dll. */
  if (__builtin_expect(unused == 0 && atom == 0, 0)) {
    static void *(__cdecl*vcruntime_tss_get)(tss_t) = NULL;
    if (!vcruntime_tss_get) {
      HMODULE dll = GetModuleHandleA("vcruntime140_threads.dll");
      FARPROC proc = dll ? GetProcAddress(dll, "tss_get") : NULL;
      if (!proc)
        return NULL;
      __atomic_store_n(&vcruntime_tss_get, (void*(__cdecl*)(tss_t))(void(*)(void))proc, __ATOMIC_SEQ_CST);
    }
    return vcruntime_tss_get(key);
  }

  /* If the atom is valid (non-zero) but is not our then it belongs to the
   * foreign DLL/EXE module. So forward call to the interface for that atom. */
  if (__builtin_expect(atom != tss_atom && atom != 0, 0)) {
    struct mingw_tss_interface *tss_interface_ptr = tss_get_interface(atom);
    if (!tss_interface_ptr)
      return NULL;
    return tss_interface_ptr->tss_get(key);
  }

  /* mingw-w64 tss_create sets _Idx unused bits to zero and atom to non-zero. */
  if (__builtin_expect(unused != 0 || atom == 0, 0))
    return NULL;

  void **vals = tss_get_vals_ptr();
  uintptr_t *vals_gen = (uintptr_t*)&vals[1024];
  uintptr_t gen = __atomic_load_n(&tss_dtors_gen[idx], __ATOMIC_RELAXED);
  if (__builtin_expect(vals_gen[idx] != gen, 0)) {
    /* Stored value is invalid and for the current generation was not set yet.
     * The default TSS value for each key and tread is NULL. */
    vals[idx] = NULL;
    vals_gen[idx] = gen;
  }
  return vals[idx];
}

int __cdecl tss_set(tss_t key, void *val)
{
  ATOM atom = key._Idx >> 16;
  unsigned short unused = (key._Idx & 0xffff) & ~1023;
  unsigned short idx = key._Idx & 1023;

  /* If upper 22 bits of _Idx are zero then the key was
   * allocated by the vcruntime140_threads.dll tss_create.
   * So forward call to the vcruntime140_threads.dll. */
  if (__builtin_expect(unused == 0 && atom == 0, 0)) {
    static int (__cdecl*vcruntime_tss_set)(tss_t,void*) = NULL;
    if (!vcruntime_tss_set) {
      HMODULE dll = GetModuleHandleA("vcruntime140_threads.dll");
      FARPROC proc = dll ? GetProcAddress(dll, "tss_set") : NULL;
      if (!proc)
        return thrd_error;
      __atomic_store_n(&vcruntime_tss_set, (int(__cdecl*)(tss_t,void*))(void(*)(void))proc, __ATOMIC_SEQ_CST);
    }
    return vcruntime_tss_set(key, val);
  }

  /* If the atom is valid (non-zero) but is not our then it belongs to the
   * foreign DLL/EXE module. So forward call to the interface for that atom. */
  if (__builtin_expect(atom != tss_atom && atom != 0, 0)) {
    struct mingw_tss_interface *tss_interface_ptr = tss_get_interface(atom);
    if (!tss_interface_ptr)
      return thrd_error;
    return tss_interface_ptr->tss_set(key, val);
  }

  /* mingw-w64 tss_create sets _Idx unused bits to zero and atom to non-zero. */
  if (__builtin_expect(unused != 0 || atom == 0, 0))
    return thrd_error;

  void **vals = tss_get_vals_ptr();
  uintptr_t *vals_gen = (uintptr_t*)&vals[1024];
  uintptr_t gen = __atomic_load_n(&tss_dtors_gen[idx], __ATOMIC_RELAXED);
  vals[idx] = val;
  vals_gen[idx] = gen;
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

    /* Before destructor is invoked, the value in tss storage has to be set to NULL. */
    void *val = vals[i];
    if (val == NULL)
      continue;
    vals[i] = NULL;

    /* Check if the value is valid. */
    if (vals_gen[i] != gen)
      continue;

    if (dtor != NULL && dtor != tss_dtor_null)
      dtor(val);
  }
}
void (__cdecl *const __mingw_tss_run_dtors_ptr)(void) = tss_run_dtors;

/* Force inclusion of code which calls __mingw_tss_run_dtors_ptr */
extern const int __mingw_tss_run_dtors_caller_provider;
static __attribute__((used)) const void *const _include_mingw_tss_run_dtors_caller = &__mingw_tss_run_dtors_caller_provider;
