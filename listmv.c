#include "listmv.h"

#include <string.h>

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
static void *listmv_ptr_at(listmv *ls, int i);

static inline void __smv_listmv_grow_list(listmv *ls) {
  if (__smv_listmv_gc_started())
    ls->data = __smv_listmv_grow_array_gc(ls->data, &ls->cap, sizeof(*ls->data),
                                          &ls->__i);
  else
    ls->data = realloc(ls->data, ls->cap * ls->__size);
}

void listmv_start_gc() {
  pointers.cap = 8;
  pointers.len = 1;  // data[0] is null
  pointers.data = malloc(sizeof(void *) * 8);

  gc_initialised = 42;

  atexit(exit_gc);
}

/* listmv functions */

void listmv_push(listmv *ls, void *data) {
  if (ls->cap == ls->len) {
    ls->cap = (ls->cap < 8) ? 8 : ls->cap * 2;
    __smv_listmv_grow_list(ls);
  }

  void *temp = malloc(ls->__size * sizeof(char));
  *(char *)temp = data;

  memcpy(listmv_ptr_at(ls, ls->len++), temp, ls->__size);

  printf("%i %i %p %p\n", listmv_i(ls, ls->len - 1), *(int *)temp, listmv_ptr_at(ls, ls->len - 1), temp);
  free(temp);
}

void listmv_push_array(listmv *ls, void *array, int len) {
  if (ls->cap <= ls->len + len) {
    ls->cap = (ls->cap < 8) ? 8 : ls->cap * 2;
    __smv_listmv_grow_list(ls);
  }

  for (int i = 0; i < len; i++) listmv_push(ls, array + i * ls->__size);
}

void listmv_pop(listmv *ls, int i) {
  memmove(listmv_ptr_at(ls, i), listmv_ptr_at(ls, i + 1), i * ls->__size);

  ls->len--; /* decrease capacity if the length is not required */
  if (ls->len * 2 < ls->cap) {
    ls->cap = (ls->cap <= 16 ? 8 : ls->cap / 2);
    __smv_listmv_grow_list(ls);
  }
}

void *listmv_i(listmv *ls, int i) { return *(char *)(ls->data + i * ls->__size); }
void *listmv_ptr_at(listmv *ls, int i) { return ls->data + i * ls->__size; }

/*
 * TODO
 * DETAILED EXPLANATION (for future me haha)
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