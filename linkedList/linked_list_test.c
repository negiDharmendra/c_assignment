#include	<stdlib.h>
#include	<assert.h>
#include	<stdio.h>
#include "linked_list.h"


void test_create_list() {
	LinkedList linked_list = create_list();
	assert(linked_list.head == NULL);
	assert(linked_list.tail == NULL);
	assert(linked_list.length == 0);
}

void test_add_to_list_add_element_at_the_ened_of_list() {
	LinkedList linked_list = create_list();
	int num = 23;
	int num_1 = 24;
	void *ptr, *ptr_1;
	ptr = &num;
	ptr_1 = &num_1;
	int length  = add_to_list(&linked_list, ptr);
	assert(length == 1);
	assert(linked_list.head == linked_list.tail);
	assert(*(int*)linked_list.head->val==23);
	assert(*(int*)linked_list.tail->val==23);

	length  = add_to_list(&linked_list, ptr_1);
	assert(length == 2);
	assert(linked_list.head != linked_list.tail);
	assert(*(int*)linked_list.head->val==23);
	assert(*(int*)linked_list.tail->val==24);
}

void test_get_first_element() {
	LinkedList linked_list = create_list();
	int num = 1223;
	int num_1 = 24;
	void *ptr, *ptr_1;
	ptr = &num;
	ptr_1 = &num_1;
	int length  = add_to_list(&linked_list, ptr);


	Element *element = (Element*)get_first_element(linked_list);
	int *val;
	val = (int*)(element->val);
	assert(*val==1223);
}

void test_get_last_element() {
	LinkedList linked_list = create_list();
	int num = 1223;
	int num_1 = 3457869;
	void *ptr, *ptr_1;
	ptr = &num;
	ptr_1 = &num_1;
	int length  = add_to_list(&linked_list, ptr);
	length  = add_to_list(&linked_list, ptr_1);


	Element *element = (Element*)get_last_element(linked_list);
	int *val;
	val = (int*)(element->val);
	assert(*val==3457869);
}