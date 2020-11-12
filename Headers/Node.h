/*******************
 * File  : Node.h
 * Author: Karthik
*******************/

#include <stdint.h>

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct _node_ Node;

struct _node_ {
  int32_t           data;
  Node*             next;
  Node*             prev;
};

Node *              _create_node_(int32_t);
void                _delete_node_(Node *);

#endif