#include "listmv.h"

// GC completely TODO

static int gc_initialised = 0;

// I'm not using listmv(void *) for a reason
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
  if (gc_initialised) {
    data = realloc(data, new_size);
    return data;
  }

  data = realloc(data, new_size);
  return data;
}

void exit_gc() { free(array.data); }
