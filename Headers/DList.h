/*******************
 * File  : DList.h
 * Author: Karthik
*******************/

#include <stdint.h>
#include "Node.h"

#ifndef DLIST_H_INCLUDED
#define DLIST_H_INCLUDED

struct _double_linked_list_ {
  Node*             head;
  Node*             tail;
  uint32_t          length;
};

typedef struct _double_linked_list_ DList; 

DList               dlist_init(void);
void                dlist_add_node_head(DList*, int32_t);
void                dlist_add_node_tail(DList*, int32_t);
void                dlist_add_node_at(DList*, int32_t, uint32_t);
void                dlist_del_node_head(DList*);
void                dlist_del_node_tail(DList*);
void                dlist_del_node_at(DList*, uint32_t);
Node *              dlist_get_node(DList*, uint32_t);
uint8_t             dlist_lookup(const DList*, int32_t);
uint32_t            dlist_length(const DList*);

#endif