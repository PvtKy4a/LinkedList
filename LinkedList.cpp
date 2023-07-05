#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  char * key;
  void * data;
  struct Node * next;
} Node_t;

typedef struct {
  Node_t * firs_node;
  uint16_t size;
} LinkedList_t;

LinkedList_t linked_list = {0};

Node_t * create_node(const char * key, void * data) {
  uint8_t key_size = strlen(key);
  Node_t * new_node = (Node_t *)malloc(sizeof(*new_node));
  if (new_node == NULL) {
    return NULL;
  }
  new_node->key = (char *)malloc(sizeof(*key) * (key_size + 1));
  if (new_node->key == NULL) {
    free(new_node);
    return NULL;
  }
  new_node->key = strcpy(new_node->key, key);
  new_node->key[key_size] = '\0';
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

void delete_node(Node_t * node) {
  free(node->key);
  free(node);
}

ll_return_status_t ll_add_or_update(const char * key, void * data) {
  Node_t * new_node = create_node(key, data);
  Node_t * node = NULL;
  if (new_node == NULL) {
    return LL_MALLOC_FAILED;
  }
  if (linked_list.firs_node == NULL) {
    linked_list.firs_node = new_node;
    linked_list.size++;
    return LL_DATA_ADDED;
  }
  if (strcmp(linked_list.firs_node->key, key) == 0) {
    linked_list.firs_node->data = data;
    delete_node(new_node);
    return LL_DATA_UPDATED;
  }
  node = linked_list.firs_node;
  while (node->next != NULL) {
    node = node->next;
    if (strcmp(node->key, key) == 0) {
      node->data = data;
      delete_node(new_node);
      return LL_DATA_UPDATED;
    }
  }
  node->next = new_node;
  linked_list.size++;
  return LL_DATA_ADDED;
}

void * ll_pop(const char * key) {
  Node_t * node = NULL;
  Node_t * previous_node = NULL;
  Node_t * next_node = NULL;
  void * data = NULL;
  if (strcmp(linked_list.firs_node->key, key) == 0) {
    data = linked_list.firs_node->data;
    next_node = linked_list.firs_node->next;
    delete_node(linked_list.firs_node);
    linked_list.firs_node = next_node;
    linked_list.size = 0;
    return data;
  }
  node = linked_list.firs_node;
  previous_node = node;
  while (node != NULL) {
    node = node->next;
    if (strcmp(node->key, key) == 0) {
      data = node->data;
      next_node = node->next;
      delete_node(node);
      previous_node->next = next_node;
      linked_list.size--;
      return data;
    }
    previous_node = node;
  }
  return NULL;
}

ll_return_status_t ll_delete(const char * key) {
  void * data = ll_pop(key);
  if (data == NULL) {
    return LL_KEY_NOT_FOUND;
  }
  return LL_DATA_DELETED;
}

void * ll_get(const char * key) {
  Node_t * node = linked_list.firs_node;
  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      return node->data;
    }
    node = node->next;
  }
  return NULL;
}

uint16_t ll_get_size(void) {
  return linked_list.size;
}
