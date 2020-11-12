/*******************
 * File  : SList.h
 * Author: Karthik
*******************/

#include <stdint.h>
#include "Node.h"

#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

struct _single_linked_list_ {
  Node*             head;
  Node*             tail;
  uint32_t          length;
};

typedef struct _single_linked_list_ SList; 

SList               slist_init(void);
void                slist_add_node_head(SList*, int32_t);
void                slist_append(SList*, int32_t);
void                slist_add_node_at(SList*, int32_t, uint32_t);
uint8_t             unique_slist_add_node_at(SList*, int32_t, uint32_t);
void                slist_del_node_head(SList*);
void                slist_del_node_tail(SList*);
void                slist_del_node_at(SList*, uint32_t);
Node *              slist_get_node(SList*, uint32_t);
uint8_t             slist_lookup(const SList*, int32_t);
uint32_t            slist_length(const SList*);
void                slist_for_each(SList*, void callback(int32_t));
int32_t             slist_min(SList*);
int32_t             slist_max(SList*);
void                slist_reverse(SList*);
uint8_t             slist_equality(const SList *, const SList *);
SList               slist_union(const SList *, const SList *);
SList               slist_intersection(const SList *, const SList *);
void                slist_clear(SList *list);

#endif