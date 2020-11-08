#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "SList.h"

void test_slist_methods(void) {
  /*****
   * Test initialization method
   *****/
  SList s = slist_init();
  SList *list = &s;
  assert((list->head == NULL) && (list->tail == NULL) && (list->length == 0));
  /*****
   * Test slist_length method
   *****/
  assert(slist_length(list) == 0);
  /*****
   * Test slist_add_node_head method
   * implicitly _create_node_ method
   *****/
  slist_add_node_head(list, 11);
  assert((slist_length(list) == 1));
  /*****
   * Test slist_append method
   * implicitly _create_node_ method
   *****/
  slist_append(list, 12);
  assert((slist_length(list) == 2));
  /*****
   * Test slist_get_node method
   *****/
  assert(slist_get_node(list, 0)->data == 11);
  /*****
   * Test slist_del_node_head method
   *****/
  slist_del_node_head(list);
  assert(list->length == 1);
  /*****
   * Test slist_del_node_tail method
   *****/
  slist_del_node_tail(list);
  assert(list->length == 0);
  /*****
   * Test slist_add_node_at method
   *****/
  slist_add_node_at(list, 1, 0);
  slist_add_node_at(list, 2, 1);
  slist_add_node_at(list, 3, 1);
  slist_add_node_at(list, 4, 3);
  assert(list->length == 4);
  assert(slist_get_node(list, 1)->data == 3);
  assert(slist_get_node(list, 3)->data == 4);
  /*****
   * Test slist_lookup method
   *****/
  assert(slist_lookup(list, 4) == 1);
  assert(slist_lookup(list, 5) == 0);
  /*****
   * Test min & max methods
   *****/
  assert(slist_min(list) == 1);
  assert(slist_max(list) == 4);
  /*****
   * Test slist_reverse method
   *****/
  slist_reverse(list);
  assert(slist_get_node(list, 3)->data == 1);
  assert(slist_get_node(list, 2)->data == 3);
  assert(slist_get_node(list, 1)->data == 2);
  assert(slist_get_node(list, 0)->data == 4);
  /*****
   * Test slist_equality method
   *****/
  assert(slist_equality(list, list) == 1);
  SList s1 = slist_init();
  SList *list1 = &s1;
  slist_add_node_at(list1, 1, 0);
  slist_add_node_at(list1, 3, 1);
  slist_add_node_at(list1, 4, 2);
  assert(slist_equality(list, list1) == 0);
  slist_add_node_at(list1, 2, 2);
  assert(slist_equality(list, list1) == 0);
  /*****
   * Test slist_union method
   *****/
  slist_add_node_at(list1, 5, 0);
  SList expected = slist_init();
  slist_append(&expected, 4);
  slist_append(&expected, 2);
  slist_append(&expected, 3);
  slist_append(&expected, 1);
  slist_append(&expected, 5);
  SList result = slist_union(list, list1);
  assert(slist_equality(&result, &expected) == 1);
  slist_clear(&expected);
  /*****
   * Test slist_intersection method
   *****/
  slist_append(&expected, 1);
  slist_append(&expected, 3);
  slist_append(&expected, 2);
  slist_append(&expected, 4);
  result = slist_intersection(list, list1);
  assert(slist_equality(&result, &expected) == 1);
  /*****
   * Test unique_slist_add_node_at method
   *****/
  assert(unique_slist_add_node_at(list1, 5, 4) == 0);
  assert(unique_slist_add_node_at(list1, 6, 0) == 1);
  /*****
   * Test slist_del_node_at method
   *****/
  slist_del_node_at(list, 0);
  assert(list->head->data == 2);
  slist_del_node_at(list, 1);
  slist_del_node_at(list, 1);
  slist_del_node_at(list, 0);
  assert(list->length == 0);
}

int main(void) {
  printf("********** Testing slist methods **********\n");
  test_slist_methods();
  // printf("********** Testing dlist methods **********\n");
  // test_dlist_methods();
  printf("**********    End of testing     **********\n");
  return 0;
}