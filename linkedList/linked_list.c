#include	<stdlib.h>
#include	<stdio.h>
#include "linked_list.h"

LinkedList create_list(void){
	LinkedList linked_list = *(LinkedList *)malloc(sizeof(LinkedList));
	linked_list.head = NULL;
	linked_list.tail = NULL;
	linked_list.length = 0;
	return linked_list;
}

int add_to_list(LinkedList *linked_list,void *val){
	Element *elemnt = (Element *)malloc(sizeof(Element));
	elemnt->val = val;
	elemnt->next = NULL;
	if(linked_list->head ==NULL)
		linked_list->head = linked_list->tail = elemnt;
	else if(linked_list->head !=NULL){
		linked_list->tail->next = elemnt; 
		linked_list->tail = elemnt;
	}
	return ++linked_list->length;
}

void *get_first_element(LinkedList list){
	if(list.head!=NULL)
		return list.head->val;
	return NULL;
}

void *get_last_element(LinkedList list){
	if(list.tail!=NULL)
		return list.tail->val;
	return NULL;
}



void for_each(LinkedList linked_list, ElementProcessor traverse ){
	Element *ptr = linked_list.head;
	while(ptr!=NULL){
		(*traverse)(ptr->val);
		ptr = ptr->next;
	}
}




