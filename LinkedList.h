#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "stdint.h"

typedef enum {
  LL_DATA_ADDED,
  LL_DATA_UPDATED,
  LL_DATA_DELETED,
  LL_MALLOC_FAILED,
  LL_KEY_NOT_FOUND,
} ll_return_status_t;

ll_return_status_t ll_add_or_update(const char * key, void * data);

void * ll_pop(const char * key);

ll_return_status_t ll_delete(const char * key);

void * ll_get(const char * key);

uint16_t ll_get_size(void);

#endif
