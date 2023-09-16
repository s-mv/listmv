#ifndef smv_listmv_header_h
#define smv_listmv_header_h

#include <stdlib.h>

void listmv_start_gc();  // TODO
int __smv_listmv_gc_started();
void *__smv_listmv_grow_array_gc(void *data, int *cap, int size,
                                 int *i);  // TODO

/* dictmv declaration */

typedef struct listmv {
  void *data;
  int len;
  int cap;
  // "private"
  int __size;
  int __i;
} listmv;

/* listmv functions */

#define new_listmv(_type) \
  (listmv) { .data = NULL, .len = 0, .cap = 0, .__size = sizeof(_type), .i = 0 }
// why a pointer? consistency of course
#define listmv_str_unwrap(_list) ((char *)((_list)->data))
#define listmv_free(_list) free((_list)->data)

void listmv_push(listmv *ls, void *data);
void listmv_push_array(listmv *ls, void *array, int len);
void listmv_pop(listmv *ls, int i);
void *listmv_i(listmv *ls, int i);

/* listmv helper functions */

// ALL TODO
#ifdef __super_comment_trigger
#define listmv_slice(_newlist, _list, _i1, _i2)                            \
  do {                                                                     \
    if (_i1 < 0 || _i1 >= _i2 || _i2 >= _list.len) break;                  \
    for (int i = _i1; i <= _i2; i++) listmv_push(_newlist, _list.data[i]); \
  } while (0) /* dictmv defintion */
#endif

/* dictmv declaration */

typedef struct dictmv {
  list keys;
  list values;
  int len;
  int cap;
} dictmv;

/* dictmv functions */

// this is just eye candy again
#define new_dictmv(_type_key, _type_value) \
  (dictmv) { .keys = new_listmv(_type_key), .values = new_listmv(_type_value) }

void dictmv_push(dictmv *dc, void *key, void *value);
void dictmv_free(dictmv *dc);

#endif