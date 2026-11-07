#include <threads.h>

__declspec(dllexport)
int __cdecl lib2_tss_create(tss_t *key, tss_dtor_t dtor)
{
  return tss_create(key, dtor);
}

__declspec(dllexport)
void __cdecl lib2_tss_delete(tss_t key)
{
  tss_delete(key);
}

__declspec(dllexport)
void *__cdecl lib2_tss_get(tss_t key)
{
  return tss_get(key);
}

__declspec(dllexport)
int __cdecl lib2_tss_set(tss_t key, void *val)
{
  return tss_set(key, val);
}
