#ifndef smv_listmv_header_h
#define smv_listmv_header_h
#include <stdlib.h>

#define listmv(__smv__type__) \
  struct {                    \
    __smv__type__ *data;      \
    int len;                  \
    int cap;                  \
  }

// incomplete, TODO
#define listmv_push(__smv__list__, __smv__data__)                              \
  do {                                                                         \
    printf("%d %d\n", (sizeof(__smv__data__), sizeof(*(__smv__list__.data)))); \
    if (sizeof(__smv__data__) == sizeof(*(__smv__list__.data))) {              \
      if (__smv__list__.cap <= __smv__list__.len) {                            \
        if (__smv__list__.cap >= 0) {                                          \
          __smv__list__.data =                                                 \
              realloc(__smv__list__.data,                                      \
                      __smv__list__.cap * sizeof(__smv__data__) * 2);          \
          __smv__list__.cap *= 2;                                              \
        } else {                                                               \
          __smv__list__.data = malloc(8 * sizeof(__smv__data__));              \
          __smv__list__.cap = 8;                                               \
          __smv__list__.len = 0;                                               \
        }                                                                      \
      }                                                                        \
      __smv__list__.data[__smv__list__.len++] = __smv__data__;                 \
    }                                                                          \
  } while (0);

#define listmv_push_array(__smv__list__, __smv__data__arr__) ;  // TODO

#define listmv_delete(__smv__list__) free(__smv__list__.data);

#define dictmv(__smv__key__type__, __smv__value__type__) \
  struct {                                               \
    listmv(__smv__key__type) key;                        \
    listmv(__smv__value__type) value;                    \
    int len;                                             \
    int cap;                                             \
  }

#define dictmv_push(__smv__dict__, __smv__key__data__, __smv__value__data__) \
  {}

void start_gc();  // TODO

#endif