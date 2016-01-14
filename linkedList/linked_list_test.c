#include	<stdlib.h>
#include	<assert.h>
#include	<stdio.h>
#include "linked_list.h"

#define TYPEINT *(int*)
#define TYPECHAR *(char*)

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
	assert(TYPEINT(linked_list.head->val) == 23);
	assert(TYPEINT(linked_list.tail->val) == 23);

	length  = add_to_list(&linked_list, ptr_1);
	assert(length == 2);
	assert(linked_list.head != linked_list.tail);
	assert(TYPEINT(linked_list.head->val) == 23);
	assert(TYPEINT(linked_list.tail->val) == 24);
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
	assert(*val == 1223);
}

void test_get_first_element_return_NULL_for_empty_list() {
	LinkedList linked_list = create_list();
	void *element = get_first_element(linked_list);

	assert(element == NULL);
}

void test_get_last_element_return_NULL_for_empty_list() {
	LinkedList linked_list = create_list();
	void *element = get_last_element(linked_list);

	assert(element == NULL);
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
	assert(*val == 3457869);
}

void multiply_by_two(void* val) {
	TYPEINT(val) *= 2;
}

void test_for_each_will_process_each_element_according_to_ElementProcessor() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		add_to_list(&linked_list, &(nums[i]));
	ElementProcessor element_processor = multiply_by_two;

	for_each(linked_list, element_processor);
	assert(TYPEINT(linked_list.head->next->val) == 48);
	assert(TYPEINT(linked_list.tail->val) == 2058);

}

void test_get_element_at_given_index() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));

	Element *element =  (Element * )get_element_at(linked_list, 2 );
	assert(TYPEINT(element->val) == 26);
	assert(element->index == 2);
}


void test_get_element_return_NULL_in_the_absence_of_index() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26};
	for (int i = 0; i < 3; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	assert(get_element_at(linked_list, 5 ) == NULL);
}

void test_index_of_return_index_of_given_element() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));

	int index_1 =  indexOf(linked_list, linked_list.head->next->next );
	assert(index_1 == 2);
	int index_2 =  indexOf(linked_list, get_element_at(linked_list, 9 ));
	assert(index_2 == 9);
}


void test_delete_element_at_given_index() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 5);
	assert(TYPEINT(element->val) == 35);
	assert(element->index == 5);
	assert(linked_list.tail->index == 8);
	assert(linked_list.length == 9);
}

void test_delete_element_at_zeroTh_index() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 0);

	assert(TYPEINT(element->val) == 23);
	assert(element->index == 0);
	assert(TYPEINT(linked_list.head->val) == 24);
	assert(linked_list.head->index == 0);
	assert(linked_list.tail->index == 8);
	assert(linked_list.length == 9);
}

void test_delete_element_at_last_index() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	Element *element =  (Element * )delete_element_at(&linked_list, 9);

	assert(TYPEINT(element->val) == 1029);
	assert(element->index == 9);
	assert(TYPEINT(linked_list.tail->val) == 5687);
	assert(TYPEINT(linked_list.head->val) == 23);
	assert(linked_list.head->index == 0);
	assert(linked_list.tail->index == 8);
	assert(linked_list.length == 9);
}

void test_delete_element_return_NULL_in_the_absence_of_index_in_list() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));

	assert(delete_element_at(&linked_list, 10) == NULL);
	assert(TYPEINT(linked_list.tail->val) == 1029);
	assert(TYPEINT(linked_list.head->val) == 23);
	assert(linked_list.head->index == 0);
	assert(linked_list.tail->index == 9);
	assert(linked_list.length == 10);
}

void test_asArray() {
	LinkedList linked_list = create_list();
	int num_1 = 23;
	int num_2 = 26;
	int num_3 = 24;
	int num_4 = 25;
	void *num1 = &num_1;
	void *num2 = &num_2;
	void *num3 = &num_3;
	void *num4 = &num_4;

	add_to_list(&linked_list, num1);
	add_to_list(&linked_list, num2);
	add_to_list(&linked_list, num3);
	add_to_list(&linked_list, num4);
	void *d[5];

	int length = asArray(linked_list, d, 4);
	assert(length == 4);
	assert(TYPEINT(d[0]) == 23);
	assert(TYPEINT(d[1]) == 26);
	assert(TYPEINT(d[2]) == 24);
}



int isEven(void *hint, void *val) {
	return TYPEINT (val) % 2 == 0;
};

int isLessThan(void *hint, void *val) {
	return TYPEINT (val) < TYPEINT(hint);
};

void test_filter() {
	LinkedList linked_list = create_list();
	int num_1 = 23;
	int num_2 = 26;
	int num_3 = 24;
	int num_4 = 28;
	void *num1 = &num_1;
	void *num2 = &num_2;
	void *num3 = &num_3;
	void *num4 = &num_4;

	add_to_list(&linked_list, num1);
	add_to_list(&linked_list, num2);
	add_to_list(&linked_list, num3);
	add_to_list(&linked_list, num4);
	MatchFunc matcher = isEven;

	LinkedList newList = filter(linked_list, matcher, NULL);
	assert(newList.length == 3);
	assert(TYPEINT(newList.head->val) == 26);
	assert(TYPEINT(newList.head->next->val) == 24);

}

void test_filter_will_return_all_num_less_than_ten() {
	LinkedList linked_list = create_list();
	int num_1 = 23;
	int num_2 = 3;
	int num_3 = 24;
	int num_4 = 7;
	void *num1 = &num_1;
	void *num2 = &num_2;
	void *num3 = &num_3;
	void *num4 = &num_4;

	add_to_list(&linked_list, num1);
	add_to_list(&linked_list, num2);
	add_to_list(&linked_list, num3);
	add_to_list(&linked_list, num4);
	MatchFunc matcher = isLessThan;
	int hint = 10;

	LinkedList newList = filter(linked_list, matcher, &hint);
	assert(newList.length == 2);
	assert(TYPEINT(newList.head->val) == 3);
	assert(TYPEINT(newList.head->next->val) == 7);

}

void test_reverse() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));

	LinkedList newList = reverse(linked_list);
	assert(newList.length == 10);
	assert(newList.head->index == 0);
	assert(newList.tail->index == 9);
	assert(TYPEINT(newList.head->val) == 1029);
	assert(TYPEINT(newList.head->next->val) == 5687);
	assert(TYPEINT(newList.tail->val) == 23);

}

void multiply_by_num(void *hint, void *source_val,void *dest_val) {
	TYPEINT(dest_val) = TYPEINT(source_val)*TYPEINT(hint);
};  


void test_map() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	int hint = 2;
	ConvertFunc converter =  multiply_by_num;
	LinkedList newList = map(linked_list,converter,&hint);

	assert(newList.length == 10);
	assert(newList.head->index == 0);
	assert(newList.tail->index == 9);
	assert(TYPEINT(newList.head->val) == 46);
	assert(TYPEINT(newList.head->next->val) == 48);
	assert(TYPEINT(newList.head->next->next->val) == 52);
	assert(TYPEINT(newList.tail->val) == 2058);
}


void test_map_does_not_change_original_linked_list() {
	LinkedList linked_list = create_list();
	int nums[10] = {23, 24, 26, 27, 12, 35, 78, 667, 5687, 1029};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));
	int hint = 2;
	ConvertFunc converter =  multiply_by_num;
	LinkedList newList = map(linked_list,converter,&hint);

	assert(linked_list.length == 10);
	assert(linked_list.head->index == 0);
	assert(linked_list.tail->index == 9);
	assert(TYPEINT(linked_list.head->val) == 23);
	assert(TYPEINT(linked_list.head->next->val) == 24);
	assert(TYPEINT(linked_list.head->next->next->val) == 26);
	assert(TYPEINT(linked_list.tail->val) == 1029);

	assert(newList.length == 10);
	assert(newList.head->index == 0);
	assert(newList.tail->index == 9);
	assert(TYPEINT(newList.head->val) == 46);
	assert(TYPEINT(newList.head->next->val) == 48);
	assert(TYPEINT(newList.head->next->next->val) == 52);
	assert(TYPEINT(newList.tail->val) == 2058);
}

void increment_char_by_one_position(void *hint, void *source_val,void *dest_val) {
	TYPEINT(dest_val) = TYPEINT(source_val)+TYPEINT(hint);
};  


void test_map_is_able_to_oprate_on_Char() {
	LinkedList linked_list = create_list();
	char nums[10] = {'A','B','C','D','E','F','G','H','I','J'};
	for (int i = 0; i < 10; ++i)
		assert(i + 1 == add_to_list(&linked_list, &(nums[i])));

	int hint = 1;
	ConvertFunc converter =  increment_char_by_one_position;
	
	LinkedList newList = map(linked_list,converter,&hint);
	
	assert(linked_list.length == 10);
	assert(linked_list.head->index == 0);
	assert(linked_list.tail->index == 9);
	assert(TYPECHAR(linked_list.head->val) == 'A');
	assert(TYPECHAR(linked_list.head->next->val) == 'B');
	assert(TYPECHAR(linked_list.head->next->next->val) == 'C');
	assert(TYPECHAR(linked_list.tail->val) == 'J');
	
	assert(newList.length == 10);	
	assert(newList.head->index == 0);
	assert(newList.tail->index == 9);
	assert(TYPECHAR(newList.head->val) == 'B');
	assert(TYPECHAR(newList.head->next->val) == 'C');
	assert(TYPECHAR(newList.head->next->next->val) == 'D');
	assert(TYPECHAR(newList.tail->val) == 'K');
}



