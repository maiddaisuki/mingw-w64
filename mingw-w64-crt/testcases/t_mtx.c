#include <threads.h>
#include <assert.h>

/* mingw-w64 headers */
#include "libtest.h"

#define COUNTER_ITERS 1024

static int __cdecl thrd_counter_trylock_worker(void *arg) {
  void *(*thrd_data)[2] = arg;
  mtx_t *mtx_ptr = (*thrd_data)[0];
  int *counter_ptr = (*thrd_data)[1];

  for (int i = 0; i < COUNTER_ITERS; i++) {
    int ret;
    while ((ret = mtx_trylock(mtx_ptr)) == thrd_busy) thrd_yield();
    assert(ret == thrd_success);
    volatile int tmp_counter = *counter_ptr;
    tmp_counter++;
    *counter_ptr = tmp_counter;
    assert(mtx_unlock(mtx_ptr) == thrd_success);
  }

  return 0;
}

static int __cdecl thrd_counter_lock_worker(void *arg) {
  void *(*thrd_data)[2] = arg;
  mtx_t *mtx_ptr = (*thrd_data)[0];
  int *counter_ptr = (*thrd_data)[1];

  for (int i = 0; i < COUNTER_ITERS; i++) {
    assert(mtx_lock(mtx_ptr) == thrd_success);
    volatile int tmp_counter = *counter_ptr;
    tmp_counter++;
    *counter_ptr = tmp_counter;
    assert(mtx_unlock(mtx_ptr) == thrd_success);
  }

  return 0;
}

int main() {
  mingw_test_init();

  mtx_t mtx;
  struct timespec ts;
  struct _timespec32 ts32;
  struct _timespec64 ts64;

  /* mtx_plain */
  assert(mtx_init(&mtx, mtx_plain) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_busy);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  mtx_destroy(&mtx);

  /* mtx_plain | mtx_recursive */
  assert(mtx_init(&mtx, mtx_plain | mtx_recursive) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  mtx_destroy(&mtx);

  /* mtx_timed */
  assert(mtx_init(&mtx, mtx_timed) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_busy);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
#ifdef _USE_32BIT_TIME_T
  if (timespec_get(&ts, TIME_UTC) == TIME_UTC)
#else
  assert(timespec_get(&ts, TIME_UTC) == TIME_UTC);
#endif
  {
    assert(mtx_timedlock(&mtx, &(struct timespec){.tv_sec = ts.tv_sec + 10}) == thrd_success);
    assert(mtx_trylock(&mtx) == thrd_busy);
    assert(mtx_unlock(&mtx) == thrd_success);
  }
  if (_timespec32_get(&ts32, TIME_UTC) == TIME_UTC) {
    assert(_mtx_timedlock32(&mtx, &(struct _timespec32){.tv_sec = ts32.tv_sec + 10}) == thrd_success);
    assert(mtx_trylock(&mtx) == thrd_busy);
    assert(mtx_unlock(&mtx) == thrd_success);
  }
  assert(_timespec64_get(&ts64, TIME_UTC) == TIME_UTC);
  assert(_mtx_timedlock64(&mtx, &(struct _timespec64){.tv_sec = ts64.tv_sec + 10}) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_busy);
  assert(mtx_unlock(&mtx) == thrd_success);
  mtx_destroy(&mtx);

  /* mtx_timed | mtx_recursive */
  assert(mtx_init(&mtx, mtx_timed | mtx_recursive) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(_timespec64_get(&ts64, TIME_UTC) == TIME_UTC);
  assert(_mtx_timedlock64(&mtx, &(struct _timespec64){.tv_sec = ts64.tv_sec + 10}) == thrd_success);
  assert(_mtx_timedlock64(&mtx, &(struct _timespec64){.tv_sec = ts64.tv_sec + 10}) == thrd_success);
  assert(mtx_trylock(&mtx) == thrd_success);
  assert(mtx_lock(&mtx) == thrd_success);
  assert(_mtx_timedlock64(&mtx, &(struct _timespec64){.tv_sec = ts64.tv_sec + 10}) == thrd_success);
#ifdef _USE_32BIT_TIME_T
  if (timespec_get(&ts, TIME_UTC) == TIME_UTC)
#else
  assert(timespec_get(&ts, TIME_UTC) == TIME_UTC);
#endif
  {
    assert(mtx_timedlock(&mtx, &(struct timespec){.tv_sec = ts.tv_sec + 10}) == thrd_success);
    assert(mtx_timedlock(&mtx, &(struct timespec){.tv_sec = ts.tv_sec + 10}) == thrd_success);
    assert(mtx_trylock(&mtx) == thrd_success);
    assert(mtx_lock(&mtx) == thrd_success);
    assert(mtx_timedlock(&mtx, &(struct timespec){.tv_sec = ts.tv_sec + 10}) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
  }
  if (_timespec32_get(&ts32, TIME_UTC) == TIME_UTC)
  {
    assert(_mtx_timedlock32(&mtx, &(struct _timespec32){.tv_sec = ts32.tv_sec + 10}) == thrd_success);
    assert(_mtx_timedlock32(&mtx, &(struct _timespec32){.tv_sec = ts32.tv_sec + 10}) == thrd_success);
    assert(mtx_trylock(&mtx) == thrd_success);
    assert(mtx_lock(&mtx) == thrd_success);
    assert(_mtx_timedlock32(&mtx, &(struct _timespec32){.tv_sec = ts32.tv_sec + 10}) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
    assert(mtx_unlock(&mtx) == thrd_success);
  }
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  assert(mtx_unlock(&mtx) == thrd_success);
  mtx_destroy(&mtx);


  int counter;
  thrd_t thrds[128];
  void *thrd_data[2] = { &mtx, &counter };

  /* thread concurency test via mtx_lock */
  counter = 0;
  assert(mtx_init(&mtx, mtx_plain) == thrd_success);
  for (unsigned i = 0; i < 128; i++)
    assert(thrd_create(&thrds[i], thrd_counter_lock_worker, &thrd_data) == thrd_success);
  for (unsigned i = 0; i < 128; i++)
    assert(thrd_join(thrds[i], NULL) == thrd_success);
  mtx_destroy(&mtx);
  assert(counter == 128 * COUNTER_ITERS);

  /* thread concurency test via mix of mtx_lock and mtx_trylock */
  counter = 0;
  assert(mtx_init(&mtx, mtx_plain) == thrd_success);
  for (unsigned i = 0; i < 32; i++)
    assert(thrd_create(&thrds[i], i % 2 ? thrd_counter_trylock_worker : thrd_counter_lock_worker, &thrd_data) == thrd_success);
  for (unsigned i = 0; i < 32; i++)
    assert(thrd_join(thrds[i], NULL) == thrd_success);
  mtx_destroy(&mtx);
  assert(counter == 32 * COUNTER_ITERS);

  return 0;
}
