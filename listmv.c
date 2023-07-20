#include "listmv.h"

// GC completely TODO

static int gc_initialised = 0;

// there's a good reason I'm not using lismv(void *)

typedef struct DataArray {
  void **data;
  int cap;
  int len;
} DataArray;

typedef struct IDs {
  int *data;
  int cap;
  int len;
} IDs;

DataArray array = {};
IDs free_ids = {};

void exit_gc();

void listmv_start_gc() {
  atexit(exit_gc);
  gc_initialised = 42;
}

void *__smv_listmv_grow_array(void *data, int new_size) {
  data = realloc(data, new_size);
  return data;
}

/*
 * TODO
 * also need to explain what is exactly going on here I guess
 */
void *__smv_listmv_grow_array_gc(void *data, int *cap, int *len) {
    return data;
}

int __smv_listmv_gc_started() { return gc_initialised; }

void exit_gc() {
  free(free_ids.data);
  free(array.data);
}
