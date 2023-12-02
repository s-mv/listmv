#ifndef smv_listmv_header_h
#define smv_listmv_header_h

#include <stdlib.h>
#include <string.h>

/*** "header" ***/

void listmv_start_gc();  // TODO
int _smv__listmv_gc_started();
void *_smv__listmv_grow_array_gc(void *data, int *cap, int size,
                                 int *i);  // TODO

/* dictmv declaration */

typedef struct listmv {
  void *data;
  int len;
  int cap;
  // "private"
  int _size;
  int _i;
} listmv;

/* listmv functions */

#define new_listmv(_type) \
  (listmv) { .data = NULL, .len = 0, .cap = 0, ._size = sizeof(_type), ._i = 0 }
// why a pointer? consistency of course
#define listmv_str_unwrap(_list) ((char *)((_list)->data))
#define listmv_free(_list) free((_list)->data)

void listmv_push(listmv *ls, void *data);
void listmv_push_array(listmv *ls, void *array, int len);
void listmv_pop(listmv *ls, int i);
void *listmv_i(listmv *ls, int i);

/* listmv helper functions */

// ALL TODO
#ifdef _todo
// this is terrible
#define listmv_slice(_newlist, _list, _i1, _i2)                            \
  do {                                                                     \
    if (_i1 < 0 || _i1 >= _i2 || _i2 >= _list.len) break;                  \
    for (int i = _i1; i <= _i2; i++) listmv_push(_newlist, _list.data[i]); \
  } while (0) /* dictmv defintion */
#endif

/* dictmv declaration */

typedef struct dictmv {
  listmv keys;
  listmv values;
  int len;
  int cap;
} dictmv;

/* dictmv functions */
// majorly TODO

// this is just eye candy again
#define new_dictmv(_type_key, _type_value) \
  (dictmv) { .keys = new_listmv(_type_key), .values = new_listmv(_type_value) }

// probably better than just leaving them around
#ifdef _todo
void dictmv_push(dictmv *dc, void *key, void *value);
void dictmv_free(dictmv *dc);
#endif

/*** source ***/

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
  if (_smv__listmv_gc_started())
    ls->data = _smv__listmv_grow_array_gc(ls->data, &ls->cap, sizeof(*ls->data),
                                          &ls->_i);
  else
    ls->data = realloc(ls->data, ls->cap * ls->_size);
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

  void *temp = malloc(ls->_size * sizeof(char));
  *(char *)temp = data;
  memcpy(listmv_ptr_at(ls, ls->len++), temp, ls->_size);

  free(temp);
}

void listmv_push_array(listmv *ls, void *array, int len) {
  if (ls->cap <= ls->len + len) {
    ls->cap = (ls->cap < 8) ? 8 : ls->cap * 2;
    __smv_listmv_grow_list(ls);
  }

  for (int i = 0; i < len; i++) listmv_push(ls, array + i * ls->_size);
}

void listmv_pop(listmv *ls, int i) {
  memmove(listmv_ptr_at(ls, i), listmv_ptr_at(ls, i + 1), i * ls->_size);

  ls->len--; /* decrease capacity if the length is not required */
  if (ls->len * 2 < ls->cap) {
    ls->cap = (ls->cap <= 16 ? 8 : ls->cap / 2);
    __smv_listmv_grow_list(ls);
  }
}

void *listmv_i(listmv *ls, int i) {
  return (void *)(*(char *)(ls->data + i * ls->_size));
}

void *listmv_ptr_at(listmv *ls, int i) { return ls->data + i * ls->_size; }

/* dictmv functions */
// majorly TODO
#ifdef _todo
void dictmv_push(dictmv *dc, void *key, void *value) {
  // dictmv_indexof(): TODO
  if (dictmv_indexof()) listmv_push(&dc->keys, key);
  listmv_push(&dc->values, value);
  /* TODO: make this cleaner */
  dc->len = dc->keys.len;
  dc->cap = dc->keys.cap;
}

void dictmv_free(dictmv *dc) {
  listmv_free(&dc->keys);
  listmv_free(&dc->values);
}
#endif

/* the real stuff */

/*
 * TODO
 * DETAILED EXPLANATION (for future me haha)
 */

// NOTE: size is the size of *data
void *_smv__listmv_grow_array_gc(void *data, int *cap, int size, int *i) {
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

int _smv__listmv_gc_started() { return gc_initialised; }

static void exit_gc() {
  for (int i = 0; i < pointers.len; i++) free(pointers.data[i]);
  free(pointers.data);
}

#endif