#ifndef smv_listmv_header_h
#define smv_listmv_header_h
#include <stdlib.h>

void listmv_start_gc();  // TODO
void *__smv_listmv_grow_array(void *data, int new_size);

#define listmv(__smv__type__) \
  struct {                    \
    __smv__type__ *data;      \
    int len;                  \
    int cap;                  \
  }

// this is just eye candy lol
#define new_listmv() \
  {}

// incomplete, TODO
#define listmv_push(__smv__list__, __smv__data__)                              \
  do {                                                                         \
    /* if sizeof data and list type aren't same, abort - TODO find a better    \
     * way to deal with this, since a char (for example) can be cast to int    \
     */                                                                        \
    if (sizeof(__smv__data__) != sizeof(*(__smv__list__.data))) break;         \
    /* if data is too small increase its length  */                            \
    if (__smv__list__.cap == __smv__list__.len) {                              \
      __smv__list__.cap = (__smv__list__.cap < 8) ? 8 : __smv__list__.cap * 2; \
      __smv__list__.data =                                                     \
          __smv_listmv_grow_array(__smv__list__.data, __smv__list__.cap);      \
      /* TODO check if there's an issue */                                     \
    }                                                                          \
    __smv__list__.data[__smv__list__.len++] = __smv__data__;                   \
  } while (0)

// TODO
#define listmv_push_array(__smv__list__, __smv__data__arr__)                 \
  do {                                                                       \
    if (sizeof(*__smv__data__arr__) != sizeof(*(__smv__list__.data))) break; \
    int len = sizeof(__smv__data__arr__) / sizeof(*__smv__data__arr__);      \
    for (int i = 0; i < len; i++)                                            \
      listmv_push(__smv__list__, __smv__data__arr__[i]);                     \
  } while (0)

// TODO probably add some sort of error instead of just returning a 0?
#define listmv_i(__smv__list__, __smv__i__) \
  (__smv__i__ < __smv__list__.len ? __smv__list__.data[__smv__i__] : 0);

// MAYBE this needs more stuff but for now this is enough
#define listmv_str_unwrap(__smv__list__) ((char *)__smv__list__.data);

#define listmv_delete(__smv__list__) free(__smv__list__.data);

#define dictmv(__smv__key__type__, __smv__value__type__) \
  struct {                                               \
    listmv(__smv__key__type) key;                        \
    listmv(__smv__value__type) value;                    \
    int len;                                             \
    int cap;                                             \
  }

// this is just eye candy again
#define new_dictmv() \
  {}

// TODO no overwrites: this is somewhat flawed
// example: if someone uses a dictmv(string, int) and someone pushed for the key
//          "hello" twice it SHOULD overwrite but that doesn't happen
// maybe a different structure is required for dictmv structs...
#define dictmv_push(__smv__dict__, __smv__key__data__, __smv__value__data__) \
  do {                                                                       \
    listmv_push(__smv__dict__.key, __smv__key__data__);                      \
    listmv_push(__smv__dict__.value, __smv__value__data__);                  \
    /* TODO: make this cleaner */                                            \
    __smv__dict__.len = __smv__dict__.key.len;                               \
    __smv__dict__.cap = __smv__dict__.key.cap;                               \
  } while (0);

#define dictmv_delete(__smv__list__) \
  do {                               \
    free(__smv__list__.key);         \
    free(__smv__list__.value);       \
  } while (0)

#endif