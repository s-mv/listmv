#include "listmv.h"

// completely TODO

int gc_initialised = 0;

void listmv_start_gc() {}

void *__smv_listmv_grow_array(void *data, int new_size) {
  if (new_size == 0) {
    free(data);
    return NULL;
  }

  data = realloc(data, new_size);
  return data;
}