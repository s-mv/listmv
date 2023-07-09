#include "listmv.h"

// completely TODO

int gc_initialised = 0;

// uhuhuh imagine if I used a listmv for this
typedef struct ListArray {
  void *data;
} Listarray;

void listmv_start_gc() { gc_initialised = 42; }

void *__smv_listmv_grow_array(void *data, int new_size) {
  if (gc_initialised) {
    return;
  }
  if (new_size == 0) {
    free(data);
    return NULL;
  }

  data = realloc(data, new_size);
  return data;
}