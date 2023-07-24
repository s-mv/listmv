#include "listmv.h"

#include "stdio.h"

// GC completely TODO

static int gc_initialised = 0;

// there's a good reason I'm not using lismv(void *)

typedef struct IDs {
  void **data;
  int cap;
  int len;
} IDs;

IDs ids = {};

void exit_gc();

void listmv_start_gc() {
  atexit(exit_gc);
  gc_initialised = 42;
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
  free(ids.data);
}
