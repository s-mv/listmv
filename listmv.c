#include "listmv.h"

#include "stdio.h"

// there's a good reason I'm not using lismv(void *)
// TODO, find a way to DO listmv(void *)
// but pre-TODO is to find if listmv(void *) works faster or slower
// certainly makes the program look cleaner but is that worth it?
typedef struct PointerArray {
  void **data;
  int cap;
  int len;
} PointerArray;

static PointerArray pointers = {};
static int gc_initialised = 0;

static void exit_gc();

void listmv_start_gc() {
  pointers.cap = 8;
  pointers.len = 1;  // data[0] is null
  pointers.data = malloc(sizeof(void *) * 8);

  gc_initialised = 42;

  atexit(exit_gc);
}

/*
 * TODO
 * DETAILED EXPLANATION
 */

// NOTE: size is the size of *data
void *__smv_listmv_grow_array_gc(void *data, int *cap, int size, int *i) {
  data = realloc(data, *cap * size);

  // if *i == 0 this is brand new data
  if (*i == 0) {
    // first grow the pointer array
    if (pointers.len >= pointers.cap) {
      pointers.cap = (pointers.cap < 8) ? 8 : pointers.cap * 2;
      pointers.data =
          realloc(pointers.data, pointers.cap * sizeof(*pointers.data));
    }

    pointers.data[pointers.len] = data;
    *i = pointers.len++;
  } else {  // otherwise it's reallocated data
    pointers.data[*i] = data;
  }

  return data;
}

int __smv_listmv_gc_started() { return gc_initialised; }

static void exit_gc() {
  for (int i = 0; i < pointers.len; i++) free(pointers.data[i]);
  free(pointers.data);
}