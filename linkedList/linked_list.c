#include	<stdlib.h>
#include	<stdio.h>
#include "linked_list.h"

LinkedList create_list(void) {
	LinkedList linked_list = *(LinkedList *)malloc(sizeof(LinkedList));
	linked_list.head = NULL;
	linked_list.tail = NULL;
	linked_list.length = 0;
	return linked_list;
}

int add_to_list(LinkedList *linked_list, void *val) {
	Element *elemnt = (Element *)malloc(sizeof(Element));
	elemnt->val = val;
	elemnt->next = NULL;
	if (linked_list->head == NULL) {
		elemnt->index = linked_list->length;
		linked_list->head = linked_list->tail = elemnt;
	}
	else if (linked_list->head != NULL) {
		elemnt->index = linked_list->length;
		linked_list->tail->next = elemnt;
		linked_list->tail = elemnt;
	}
	return ++linked_list->length;
}

void *get_first_element(LinkedList list) {
	if (list.head != NULL)
		return list.head->val;
	return NULL;
}

void *get_last_element(LinkedList list) {
	if (list.tail != NULL)
		return list.tail->val;
	return NULL;
}



void for_each(LinkedList linked_list, ElementProcessor traverse ) {
	Element *ptr = linked_list.head;
	while (ptr != NULL) {
		(*traverse)(ptr->val);
		ptr = ptr->next;
	}
}


void * get_element_at(LinkedList list, int index) {
	Element *ptr = list.head;
	while (ptr != NULL) {
		if (ptr->index == index)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}


int indexOf(LinkedList list, void *element) {
	Element *ptr = list.head;
	while (ptr != NULL) {
		if (ptr->val == ((Element*)element)->val)
			return ptr->index;
		ptr = ptr->next;
	}
	return -1;
}

void * delete_first_element(LinkedList *list) {
	Element *deleteed_element = list->head;
	list->head = list->head->next;
	Element *ptr = (Element *)list->head;
	while(ptr!=NULL){
		ptr->index--;
		ptr= ptr->next;
	}
	list->length--;
	return deleteed_element;
}

void * delete_last_element(LinkedList *list) {
	Element *deleteed_element = list->tail;
	Element *ptr = (Element *)list->head;
	while(ptr!=NULL){
		if(ptr->next==list->tail){
			list->tail = ptr;
			list->tail->next = NULL;
		}
		ptr= ptr->next;
	}
	list->length--;
	return deleteed_element;
}


void modify_index(Element *element){
	while(element){
		element->index--;
		element = element->next;
	}
}



void * delete_element_at(LinkedList *list, int index) {
	Element *ptr = (Element *)list->head;
	Element *prev;
	Element *deleteed_element;
	if(index==0)return delete_first_element(list);
	if(index==list->length-1)return delete_last_element(list);
	while (ptr != NULL) {
		if (ptr->index == index) {
			deleteed_element = ptr;
			prev->next = ptr->next;
			modify_index(ptr->next);
			list->length--;
			return deleteed_element;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return NULL;
}

