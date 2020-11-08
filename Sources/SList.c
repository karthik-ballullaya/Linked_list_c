#include <stdlib.h>
#include <assert.h>
#include "SList.h"

SList slist_init(void) {
  SList list = {NULL, NULL, 0};
  return list;
}

void slist_add_node_head(SList *list, int32_t data) {
  assert(list != NULL);

  Node *node = _create_node_(data);
  assert(node != NULL);

  node->next = list->head;
  list->head = node;
  if (list->tail == NULL) {
    list->tail = node;
  }
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

void slist_append(SList *list, int32_t data) {
  assert(list != NULL);

  Node *node = _create_node_(data);
  assert(node != NULL);

  if (list->tail != NULL) {
    list->tail->next = node;
    list->tail = node;
  } else {
    list->head = list->tail = node;
  }
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

void slist_add_node_at(SList *list, int32_t data, uint32_t index) {
  assert((list != NULL) && (index <= list->length));

  Node *node = _create_node_(data);
  assert(node != NULL);

  if (index == 0) {
    if (list->length != 0) {
      node->next = list->head;
    }
    list->head = node;
    if (list->tail == NULL) {
      list->tail = node;
    }
  } else {
    Node *prevNeighbourNode = slist_get_node(list, index - 1);
    node->next = prevNeighbourNode->next;
    prevNeighbourNode->next = node;
    if (index == list->length) {
      list->tail = node;
    }
  }
  list->length ++;

  assert( (list->length == 1 && list->head == list->tail) ||
          (list->length  > 1 && list->head != list->tail)
        );
}

static Node * _create_node_(int32_t data) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

uint32_t slist_length(const SList *list) {
  assert(list != NULL);
  return list->length;
}

void slist_del_node_head(SList *list) {
  assert(list != NULL);
  Node *firstNode = list->head;
  list->head = firstNode->next;
  if (list->head == NULL) {
    list->tail = NULL;
  }
  _delete_node_(firstNode);
  list->length--;
}

void slist_del_node_tail(SList *list) {
  assert(list != NULL);
  Node *penultimateNode = slist_get_node(list, list->length - 2);
  _delete_node_(list->tail);
  list->tail = penultimateNode;
  if (list->tail == NULL) {
    list->head = NULL;
  }
  list->length--;
}

void slist_del_node_at(SList *list, uint32_t index) {
  assert((list != NULL) && (index < list->length));

  Node *node;
  if (index == 0) {
    node = list->head;
    list->head = node->next;
    if (list->head == NULL) {
      list->tail = NULL;
    }
  } else {
    Node *prevNeighbourNode = slist_get_node(list, index - 1);
    node = prevNeighbourNode->next;
    prevNeighbourNode->next = node->next;
    if (prevNeighbourNode->next == NULL) {
      list->tail = prevNeighbourNode;
    }
  }
  _delete_node_(node);
  list->length --;
}

static void _delete_node_(Node *node) {
  assert(node != NULL);
  free(node);
}

Node * slist_get_node(SList* list, uint32_t index) {
  assert(list != NULL);
  if (index > list->length - 1) {
    return NULL;
  }
  uint32_t i;
  Node *node = list->head;
  for (i = 0; i < index; i++) {
    node = node->next;
  }
  return node;
}

uint8_t slist_lookup(const SList *list, int32_t data) {
  for (Node *node = list->head; node != NULL; node = node->next) {
    if (node->data == data) {
      return 1;
    }
  }
  return 0;
}

void slist_for_each(SList* list, void callback(int32_t)) {
  Node *node = list->head;
  for (uint32_t i = 0; i < list->length; i++) {
    callback(node->data);
    node = node->next;
  }
}

int32_t slist_min(SList *list) {
  assert(list != NULL);
  if (list->head == NULL) {
    return NULL;
  }
  int32_t minValue = list->head->data;
  Node *node = list->head;
  while (node != NULL) {
    minValue = (minValue < node->data) ? minValue : node->data;
    node = node->next;
  }
  return minValue;
}

int32_t slist_max(SList *list) {
  assert(list != NULL);
  if (list->head == NULL) {
    return NULL;
  }
  int32_t maxValue = list->head->data;
  Node *node = list->head;
  while (node != NULL) {
    maxValue = (maxValue > node->data) ? maxValue : node->data;
    node = node->next;
  }
  return maxValue;
}

void slist_reverse(SList* list) {
  assert(list != NULL);
  if (list->head == NULL) {
    return;
  }
  Node *prev = NULL, *curr = list->head, *next = NULL;
  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  list->tail = list->tail;
  list->head = prev;
}

uint8_t slist_equality(const SList *list1, const SList *list2) {
  assert((list1 != NULL) && (list2 != NULL));
  if (list1->length != list2->length) {
    return 0;
  }
  Node *curr1 = list1->head, *curr2 = list2->head;
  while (curr1 != NULL) {
    if (curr1->data != curr2->data) {
      return 0;
    }
    curr1 = curr1->next;
    curr2 = curr2->next;
  }
  return 1;
}

SList slist_union(const SList * list1, const SList * list2) {
  SList result = slist_init();
  Node *curr1 = list1->head, *curr2 = list2->head;
  while (curr1 != NULL) {
    slist_append(&result, curr1->data);
    curr1 = curr1->next;
  }
  while (curr2 != NULL) {
    if (!slist_lookup(&result, curr2->data)) {
      slist_append(&result, curr2->data);
    }
    curr2 = curr2->next;
  }
  return result;
}

SList slist_intersection(const SList *list1, const SList *list2) {
  SList result = slist_init();
  const SList *iterableList = (list1->length > list2->length) ? list1 : list2;
  const SList *otherList = (list1->length > list2->length) ? list2 : list1;
  Node *curr = iterableList->head;
  while (curr != NULL) {
    if (slist_lookup(otherList, curr->data)) {
      slist_append(&result, curr->data);
    }
    curr = curr->next;
  }
  return result;
}

uint8_t unique_slist_add_node_at(SList *list, int32_t data, uint32_t index) {
  if (!slist_lookup(list, data)) {
    slist_add_node_at(list, data, index);
    return 1;
  }
  return 0;
}

void slist_clear(SList *list) {
  Node *node = list->head;
  while (node != NULL) {
    node = node->next;
    slist_del_node_head(list);
  }
}