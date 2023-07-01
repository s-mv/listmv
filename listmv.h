#ifndef smv_listmv_header_h
#define smv_listmv_header_h
#include <stdlib.h>

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
#define listmv_push(__smv__list__, __smv__data__)                             \
  do {                                                                        \
    /* if sizeof data and list type aren't same, abort TODO find a better way \
     * to deal with this, since a char (for example) can be cast to int       \
     */                                                                       \
    if (sizeof(__smv__data__) == sizeof(*(__smv__list__.data))) {             \
      if (__smv__list__.cap <= __smv__list__.len) {                           \
        if (__smv__list__.cap > 0) {                                          \
          __smv__list__.data =                                                \
              realloc(__smv__list__.data,                                     \
                      __smv__list__.cap * sizeof(__smv__data__) * 2);         \
          __smv__list__.cap *= 2;                                             \
        } else {                                                              \
          __smv__list__.data = malloc(8 * sizeof(__smv__data__));             \
          __smv__list__.cap = 8;                                              \
          __smv__list__.len = 0;                                              \
        }                                                                     \
      }                                                                       \
      __smv__list__.data[__smv__list__.len++] = __smv__data__;                \
    }                                                                         \
  } while (0);

#define listmv_push_array(__smv__list__, __smv__data__arr__) \
  do {                                                       \
  } while (0);  // TODO

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

#define dictmv_push(__smv__dict__, __smv__key__data__, __smv__value__data__) \
  do {                                                                       \
    listmv_push(__smv__dict__.key, __smv__key__data__);                      \
    listmv_push(__smv__dict__.value, __smv__value__data__);                  \
    /* TODO: make this cleaner */                                            \
    __smv__dict__.len = __smv__dict__.key.len;                               \
    __smv__dict__.cap = __smv__dict__.key.cap;                               \
  } while (0);

void start_gc();  // TODO

#endif