#include <stdlib.h>
#include <assert.h>
#include "Node.h"

Node * _create_node_(int32_t data) {
  Node *node = (Node *) malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node->data = data;
  node->next = NULL;
  return node;
}

void _delete_node_(Node *node) {
  assert(node != NULL);
  free(node);
}