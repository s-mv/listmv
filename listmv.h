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
  (listmv) { .data = NULL, .len = 0, .cap = 0, .__size = sizeof(_type) }
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

#define dictmv(_key_type, _value_type) \
  struct {                             \
    listmv(_key_type) key;             \
    listmv(_value_type) value;         \
    int len;                           \
    int cap;                           \
  }

/* dictmv functions */

// this is just eye candy again
#define new_dictmv() \
  {}

// TODO no overwrites: this is somewhat flawed
// example: if someone uses a dictmv(string, int) and someone pushed for the key
//          "hello" twice it SHOULD overwrite but that doesn't happen
// maybe a different structure is required for dictmv structs...
#define dictmv_push(_dict, _key, _value)                \
  do {                                                  \
    if (list_indexndex()) listmv_push(_dict.key, _key); \
    listmv_push(_dict.value, _value);                   \
    /* TODO: make this cleaner */                       \
    _dict.len = _dict.key.len;                          \
    _dict.cap = _dict.key.cap;                          \
  } while (0)

#define dictmv_free(_list) \
  do {                     \
    free(_list.key);       \
    free(_list.value);     \
  } while (0)

#endif