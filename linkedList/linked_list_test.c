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


	void *element = get_first_element(linked_list);
	int *val;
	val = (int*)(element);
	assert(*val==1223);
}

void test_get_first_element_return_NULL_for_empty_list() {
	LinkedList linked_list = create_list();
	void *element = get_first_element(linked_list);
	
	assert(element==NULL);
}

void test_get_last_element_return_NULL_for_empty_list() {
	LinkedList linked_list = create_list();
	void *element = get_last_element(linked_list);
	
	assert(element==NULL);
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


	void *element = get_last_element(linked_list);
	int *val;
	val = (int*)(element);
	assert(*val==3457869);
}

void multiply_by_two(void* val){
	(*(int*)val)*=2;
}

void test_for_each_will_process_each_element_according_to_ElementProcessor(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		add_to_list(&linked_list,&(nums[i]));
	ElementProcessor element_processor = multiply_by_two;

	for_each(linked_list,element_processor);
	assert(*(int*)linked_list.head->next->val == 48);
	assert(*(int*)linked_list.tail->val == 2058);

}

void test_get_element_at_given_index(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));

	Element *element =  (Element * )get_element_at(linked_list, 2 );
	assert(*(int*)element->val==26);
	assert(element->index==2);
}


void test_get_element_return_NULL_in_the_absence_of_index(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26};
	for (int i = 0; i < 3; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));
	assert(get_element_at(linked_list, 5 )==NULL);
}

void test_index_of_return_index_of_given_element(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));

	int index_1 =  indexOf(linked_list, linked_list.head->next->next );
	assert(index_1==2);
	int index_2 =  indexOf(linked_list, get_element_at(linked_list, 9 ));
	assert(index_2==9);
}


void test_delete_element_at_given_index(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 5);
	assert(*(int*)element->val==35);
	assert(element->index==5);
	assert(linked_list.tail->index==8);
	assert(linked_list.length==9);
}

void test_delete_element_at_zeroTh_index(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 0);

	assert(*(int*)element->val==23);
	assert(element->index==0);
	assert(*(int*)linked_list.head->val==24);
	assert(linked_list.head->index==0);
	assert(linked_list.tail->index==8);
	assert(linked_list.length==9);
}

void test_delete_element_at_last_index(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 9);

	assert(*(int*)element->val==1029);
	assert(element->index==9);
	assert(*(int*)linked_list.tail->val==5687);
	assert(*(int*)linked_list.head->val==23);
	assert(linked_list.head->index==0);
	assert(linked_list.tail->index==8);
	assert(linked_list.length==9);
}

void test_delete_element_return_NULL_in_the_absence_of_index_in_list(){
	LinkedList linked_list = create_list();
	int nums[10] = {23,24,26,27,12,35,78,667,5687,1029};
	for (int i = 0; i < 10; ++i)
		assert(i+1==add_to_list(&linked_list,&(nums[i])));

	assert(delete_element_at(&linked_list, 10)==NULL);
	assert(*(int*)linked_list.tail->val==1029);
	assert(*(int*)linked_list.head->val==23);
	assert(linked_list.head->index==0);
	assert(linked_list.tail->index==9);
	assert(linked_list.length==10);
}



