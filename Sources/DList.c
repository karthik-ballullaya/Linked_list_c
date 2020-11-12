#include <stdlib.h>
#include <assert.h>
#include "DList.h"

DList dlist_init(void) {
  DList list = {NULL, NULL, 0};
  return list;
}

void dlist_add_node_head(DList *list, int32_t data) {
  assert(list != NULL);

  Node *node = _create_node_(data);
  assert(node != NULL);

  node->prev = NULL;
  node->next = list->head;
  if (list->tail == NULL) {
    list->tail = node;
  } else {
    list->head->prev = node;
  }
  list->head = node;
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

void dlist_add_node_tail(DList *list, int32_t data) {
  assert(list != NULL);

  Node *node = _create_node_(data);
  assert(node != NULL);

  if (list->tail != NULL) {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  } else {
    list->head = list->tail = node;
  }
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

void dlist_add_node_at(DList *list, int32_t data, uint32_t index) {
  assert((list != NULL) && (index <= list->length));

  Node *node = _create_node_(data);
  assert(node != NULL);

  if (index == 0) {
    node->prev = NULL;
    if (list->tail == NULL) {
      list->tail = node;
    } else {
      node->next = list->head;
      list->head->prev = node;
    }
    list->head = node;
  } else {
    Node *prevNeighbourNode = dlist_get_node(list, index - 1);
    node->prev = prevNeighbourNode;
    node->next = prevNeighbourNode->next;
    if (index == list->length) {
      list->tail = node;
    } else {
      prevNeighbourNode->next->prev = node;
    }
    prevNeighbourNode->next = node;
  }
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

uint32_t dlist_length(const DList *list) {
  assert(list != NULL);
  return list->length;
}

void dlist_del_node_head(DList *list) {
  assert(list != NULL);
  Node *firstNode = list->head;
  list->head = firstNode->next;
  if (list->head == NULL) {
    list->tail = NULL;
  } else {
    list->head->prev = NULL;
  }
  _delete_node_(firstNode);
  list->length--;
}

void dlist_del_node_tail(DList *list) {
  assert(list != NULL);
  Node *lastNode = list->tail;
  list->tail = lastNode->prev;
  _delete_node_(lastNode);
  if (list->tail == NULL) {
    list->head = NULL;
  } else {
    list->tail->next = NULL;
  }
  list->length--;
}

void dlist_del_node_at(DList *list, uint32_t index) {
  assert((list != NULL));

  if(!(index < list->length)) {
    return;
  }

  Node *node;
  if (index == 0) {
    node = list->head;
    list->head = node->next;
    if (list->head == NULL) {
      list->tail = NULL;
    } else {
      list->head->prev = NULL;
    }
  } else {
    Node *prevNeighbourNode = dlist_get_node(list, index - 1);
    node = prevNeighbourNode->next;
    prevNeighbourNode->next = node->next;
    if (prevNeighbourNode->next == NULL) {
      list->tail = prevNeighbourNode;
    } else {
      node->next->prev = prevNeighbourNode;
    }
  }
  _delete_node_(node);
  list->length --;
}

Node * dlist_get_node(DList* list, uint32_t index) {
  assert(list != NULL);
  if (index > list->length - 1) {
    return NULL;
  }

  Node *node;
  if (index < list->length / 2) {
    node = list->head;
    for (uint32_t i = 0; i < index; i++) {
      node = node->next;
    }
  } else {
    node = list->tail;
    for (uint32_t i = list->length - 1; i > index; i--) {
      node = node->prev;
    }
  }
  return node;
}

uint8_t dlist_lookup(const DList *list, int32_t data) {
  Node *fwdNode = list->head, *revNode = list->tail;
  for (uint32_t i = 0; i < (list->length / 2) + 1; i++) {
      if ((fwdNode->data == data) || (revNode->data == data)) {
        return 1;
      }
      fwdNode = fwdNode->next;
      revNode = revNode->prev;
    }
  return 0;
}
