#ifndef smv_listmv_header_h
#define smv_listmv_header_h

#include <stdlib.h>

void listmv_start_gc();  // TODO
int __smv_listmv_gc_started();
void *__smv_listmv_grow_array_gc(void *data, int *cap, int size,
                                 int *i);  // TODO

/* dictmv declaration */

#define listmv(_type) \
  struct {            \
    _type *data;      \
    int len;          \
    int cap;          \
    /* private: */    \
    int __i;          \
  }

/* back-end helper functions */

#define __smv_listmv_grow_list(_list)                                    \
  do {                                                                   \
    if (__smv_listmv_gc_started())                                       \
      _list.data = __smv_listmv_grow_array_gc(                           \
          _list.data, &_list.cap, sizeof(*_list.data), &_list.__i);      \
    else                                                                 \
      _list.data = realloc(_list.data, _list.cap * sizeof(*_list.data)); \
  } while (0)

/* listmv functions */

// this is just eye candy lol
#define new_listmv() \
  {}

// incomplete, TODO
#define listmv_push(_list, _data)                                           \
  do {                                                                      \
    /* if sizeof data and list type aren't same, abort - TODO find a better \
     * way to deal with this, since a char (for example) can be cast to int \
     */                                                                     \
    if (sizeof(_data) != sizeof(*(_list.data))) break;                      \
    /* if data is too small increase its length  */                         \
    if (_list.cap == _list.len) {                                           \
      _list.cap = (_list.cap < 8) ? 8 : _list.cap * 2;                      \
      __smv_listmv_grow_list(_list);                                        \
    }                                                                       \
    _list.data[_list.len++] = _data;                                        \
  } while (0)

// TODO
#define listmv_push_array(_list, _array, _len)                    \
  do {                                                            \
    if (sizeof(*_array) != sizeof(*(_list.data))) break;          \
    for (int i = 0; i < _len; i++) listmv_push(_list, _array[i]); \
  } while (0)

#define listmv_delete(_list, _index)                      \
  do {                                                    \
    for (int i = _index; i < _list.len - 1; i++) {        \
      _list.data[i] = _list.data[i + 1];                  \
    }                                                     \
    _list.len--;                                          \
    /* decrease capacity if the length is not required */ \
    if (_list.len * 2 < _list.cap) {                      \
      _list.cap = (_list.cap <= 16 ? 8 : _list.cap / 2);  \
      __smv_listmv_grow_list(_list);                      \
    }                                                     \
  } while (0)

// TODO probably add some sort of error instead of just returning a 0?
#define listmv_i(_list, _index) (_index < _list.len ? _list.data[_index] : 0)

#define listmv_len(_list) (_list.len)

// MAYBE this needs more stuff but for now this is enough
#define listmv_str_unwrap(_list) ((char *)_list.data)

#define listmv_free(_list) free(_list.data)

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