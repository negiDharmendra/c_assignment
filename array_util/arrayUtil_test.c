#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_util.h"

int isEven(void *hint, void *val) {
	return (*(int*)val) % 2 == 0;
};


int isDivisibleInt(void *hint, void *val) {
	return (*(int*)val)%(*(int*)hint)==0;
};
int isDivisibleChar(void *hint, void *val) {
	return (*(char*)val) % (*(char*)hint) == 0;
};

void test_create_array() {
	ArrayUtil array_1 =  create(sizeof(int), 2);

	assert(sizeof(array_1.base) == 8);
	assert(array_1.length == 2);
	assert(array_1.typeSize == 4);
	dispose(array_1);
}

void test_are_equal() {
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(int), 2);

	assert(are_equal( array_1, array_2) == 1);
	assert(are_equal( array_1, array_2) != 0);
	dispose(array_1);
	dispose(array_2);
}

void test_are_equal_for_integer() {
	int length = 10;
	int size = 4;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
	{
		*((int *)(array_1.base) + i - 65) = i;
		*((int *)(array_2.base) + i - 65) = i;
	}

	assert(are_equal( array_1, array_2) == 1);
	assert(are_equal( array_1, array_2) != 2);
	dispose(array_1);
	dispose(array_2);
}


void test_are_equal_for_character(void) {
	int length = 10;
	int size = 1;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
	{
		*((char *)(array_1.base) + i - 65) = i;
		*((char *)(array_2.base) + i - 65) = i;
	}
	assert(are_equal( array_1, array_2) == 1);
	assert(are_equal( array_1, array_2) != 2);
	dispose(array_1);
	dispose(array_2);
}

void test_are_equal_for_double() {
	int length = 10;
	int size = 8;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
	{
		*((double *)(array_1.base) + i - 65) = i;
		*((double *)(array_2.base) + i - 65) = i;
	}

	assert(are_equal( array_1, array_2) == 1);
	assert(are_equal( array_1, array_2) != 2);
	dispose(array_1);
	dispose(array_2);
}

void test_are_equal_for_string() {
	int length = 10;
	int size = 1;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
	{
		*((char *)(array_1.base) + i - 65) = 'h';
		*((char *)(array_2.base) + i - 65) = 'h';
	}

	assert(are_equal( array_1, array_2) == 1);
	assert(are_equal( array_1, array_2) != 2);
	dispose(array_1);
	dispose(array_2);
}


void test_array_with_defferent_type_size_are_not_equal() {
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(char), 2);

	assert(are_equal( array_1, array_2) == 0);
	assert(are_equal( array_1, array_2) != 1);
	dispose(array_1);
	dispose(array_2);
}

void test_array_with_defferent_length_are_not_equal() {
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(int), 3);

	assert(are_equal( array_1, array_2) == 0);
	assert(are_equal( array_1, array_2) != 1);
	dispose(array_1);
	dispose(array_2);
}

void test_array_with_defferent_element_are_not_equal() {
	int size = sizeof(int);
	int length = 20;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
	{
		*((int *)(array_1.base) + i - 65) = i;
		*((int *)(array_2.base) + i - 65) = i + 1;
	}
	assert(are_equal( array_1, array_2) == 0);
	dispose(array_1);
	dispose(array_2);
}

void test_resize() {
	int size = sizeof(int);
	int length = 4;
	int new_length = 9;
	ArrayUtil array_1 =  create(size, length);
	array_1 =  resize(array_1, new_length);

	assert(array_1.typeSize == 4);
	assert(array_1.length == new_length);
	dispose(array_1);
}

void test_find_index() {
	int size = sizeof(int);
	int length = 26;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
		*(( int *)(array_1.base) + i - 65) = i;
	int d  = 90;
	assert(find_index(array_1, &d) == 25);
	dispose(array_1);
}

void test_find_index_return_minus_one_if_elsment_not_exist() {
	int size = sizeof(int);
	int length = 4;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
		*(( int *)(array_1.base) + i - 65) = i;
	int d  = 50;
	assert(find_index(array_1, &d) == -1);
	dispose(array_1);
}

void test_find_index_also_works_for_char() {
	int size = sizeof(char);
	int length = 26;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
		*(( char *)(array_1.base) + i - 65) = i;
	char d  = 'Z';
	char e = 'B';
	assert(find_index(array_1, &d) == 25);
	assert(find_index(array_1, &e) != 2);
	dispose(array_1);
}

void test_find_index_also_works_for_double() {
	int size = sizeof(double);
	int length = 10;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65 + length; ++i)
		*(( double *)(array_1.base) + i - 65) = i;
	double d  = 70;
	double e = 'B';
	assert(find_index(array_1, &d) == 5);
	assert(find_index(array_1, &e) == 1);
	dispose(array_1);
}






void test_find_first_gives_firs_even_num() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 26;
	base[3] = 48;
	void *result = find_first(array_1, &match, NULL);
	if (result != NULL)assert(*(int*)result == 26);
	else assert(result == NULL);
	dispose(array_1);
}

void test_find_first_gives_NULL_in_the_absence_of_even_num() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 27;
	base[3] = 45;
	void *result = find_first(array_1, &match, NULL);
	if (result != NULL)assert(*(int*)result == 26);
	else assert(result == NULL);
	dispose(array_1);
}



void test_find_first_gives_num_whish_is_divisible_by_hint_num_for_Char() {
	int size = sizeof(char);
	int length = 4;
	MatchFunc match = isDivisibleChar;
	ArrayUtil array_1 =  create(size, length);
	char *base = ( char *)(array_1.base);
	base[0] = 'A';
	base[1] = 'B';
	base[2] = 'C';
	base[3] = 'D';
	char hint = 'A';
	void *result;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(char*)result == 'A');
	else assert(result == NULL);

	hint = 'B';
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(char*)result == 'B');
	else assert(result == NULL);

	hint = 'C';
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(char*)result == 'C');
	else assert(result == NULL);

	hint = 'D';
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(char*)result == 'D');
	else assert(result == NULL);

	hint = 'R';
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(char*)result == 'R');
	else assert(result == NULL);
	dispose(array_1);
}

void test_find_first_gives_num_whish_is_divisible_by_hint_num_for_int() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isDivisibleChar;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 45;
	base[3] = 22;
	int hint = 23;
	void *result;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 23);
	else assert(result == NULL);

	hint = 9;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 27);
	else assert(result == NULL);

	hint = 2;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 22);
	else assert(result == NULL);

	hint = 15;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 45);
	else assert(result == NULL);

	hint = 15;
	result = find_first(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 45);
	else assert(result == NULL);
	dispose(array_1);
}

void test_find_last_gives_num_whish_is_divisible_by_hint_num_for_int() {
	int size = sizeof(int);
	int length = 5;
	MatchFunc match = isDivisibleInt;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 33;
	base[1] = 27;
	base[2] = 45;
	base[3] = 22;
	base[4] = 15;
	int hint = 11;
	void *result;
	result = find_last(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 22);
	else assert(result == NULL);

	hint = 9;
	result = find_last(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 45);
	else assert(result == NULL);

	hint = 15;
	result = find_last(array_1, &match, &hint);
	if (result != NULL)assert(*(int*)result == 15);
	else assert(result == NULL);
	dispose(array_1);
}


void test_find_last_gives_firs_even_num() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 26;
	base[3] = 28;
	void *result = find_last(array_1, &match, NULL);
	if (result != NULL)assert(*(int*)result == 28);
	else assert(result == NULL);
	dispose(array_1);
}

void test_find_last_gives_NULL_in_the_absence_of_even_num() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 27;
	base[3] = 45;
	void *result = find_last(array_1, &match, NULL);
	if (result != NULL)assert(*(int*)result == 26);
	else assert(result == NULL);
	dispose(array_1);
}


void test_count_gives_count_of_even_element_present_in_the_array() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 26;
	base[2] = 28;
	base[3] = 45;
	int result = count(array_1, &match, NULL);
	assert(result == 2);
	dispose(array_1);
}

void test_count_gives_zero_in_the_absence_of_even_number_in_the_array() {
	int size = sizeof(int);
	int length = 4;
	MatchFunc match = isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 25;
	base[2] = 277;
	base[3] = 445;
	int result = count(array_1, &match, NULL);
	assert(result == 0);
	dispose(array_1);
}

void test_count_gives_count_the_element_which_is_divisible_by_given_num() {
	int size = sizeof(int);
	int length = 6;
	MatchFunc match = isDivisibleInt;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 45;
	base[3] = 22;
	base[4] = 46;
	base[5] = 18;
	int hint = 23;
	int result;
	result = count(array_1, &match, &hint);
	assert(result == 2);

	hint = 9;
	result = count(array_1, &match, &hint);
	assert(result == 3);

	hint = 2;
	result = count(array_1, &match, &hint);
	assert(result == 3);

	hint = 15;
	result = count(array_1, &match, &hint);
	assert(result == 1);

	hint = 7;
	result = count(array_1, &match, &hint);
	assert(result == 0);

	dispose(array_1);
}

void test_filter_for_even_num() {
	int length = 20;
	int dest_length = 10;
	int size = sizeof(int);

	ArrayUtil array = create(size, length);
	ArrayUtil destination = create(8, dest_length);
	MatchFunc match = isEven;
	int *values;

	values = (int *) array.base;
	void **dest_base =  destination.base;

	for (int i = 0; i < length; ++i)values[i] = 24 + i;

	int filterReturnValue = filter(array, &match, NULL, dest_base, destination.length);

	int **result=  (int**)dest_base;

	assert(filterReturnValue == 10);
	assert(destination.length == 10);
	assert(*result[0]==24);
	assert(*result[1]==26);
	assert(*result[2]==28);
	assert(*result[3]==30);
	assert(*result[4]==32);

	dispose(array);
	dispose(destination);
}


void test_filter_to_find_all_num_divisible_by_given_num() {
	int length = 10;
	int dest_length = 5;
	int size = sizeof(int);

	ArrayUtil array = create(size, length);
	ArrayUtil destination = create(8, dest_length);
	MatchFunc match = isDivisibleInt;

	int *values;

	values = (int *) array.base;
	void **dest_base =  destination.base;

	for (int i = 0; i < length; ++i)values[i] = 24 + i;

	int hint = 3;

	int filterReturnValue = filter(array, &match, &hint, dest_base, destination.length);

	int **result=  (int**)dest_base;
	
	assert(filterReturnValue == 4);
	assert(destination.length == 5);
	assert(*result[0]==24);
	assert(*result[1]==27);
	assert(*result[2]==30);
	assert(*result[3]==33);

	dispose(array);
	dispose(destination);
}

void increment_by_n(void *hint,void* source_el, void* destination_el){
	*(int*)destination_el = (*(int*)source_el+*(int*)hint);

}

void test_map_for_increment_by_n() {
	int length = 5;
	int size = sizeof(int);

	ArrayUtil source = create(size, length);
	ArrayUtil destination = create(size, length);
	ConvertFunc convert = increment_by_n;
	int *values;
	int hint = 2;

	values = source.base;

	for (int i = 0; i < length; ++i)values[i] = i;

	map(source, destination,&convert, &hint);


	int *result=  (int *)destination.base;
	assert(destination.length == length);
	
	assert(result[0]==2);
	assert(result[1]==3);
	assert(result[2]==4);
	assert(result[3]==5);

	dispose(source);
	dispose(destination);
}

void multiply(void *hint,void *item){
	*(int*)item = (*(int*)item)*(*(int*)hint);
}

void test_forEach_for_increment_by_n() {
	int length = 5;
	int size = sizeof(int);

	ArrayUtil source = create(size, length);
	OperationFunc convert = multiply;
	int *values;
	int hint = 2;

	values = source.base;

	for (int i = 0; i < length; ++i)values[i] = i;

	forEach(source , &convert , &hint);

	assert(source.length == length);
	
	assert(values[0]==0);
	assert(values[1]==2);
	assert(values[2]==4);
	assert(values[3]==6);

	dispose(source);
}


void* reducerfunc(void* hint, void* previousItem, void* item){
	*(int*)previousItem = *(int*)previousItem+*(int*)item;
	return previousItem;
};


void test_reduce_for_increment_by_n() {
	int length = 10;
	int size = sizeof(int);

	ArrayUtil source = create(size, length);
	ReducerFunc reducer = reducerfunc;
	int *values;
	int hint = 2;
	values = source.base;

	for (int i = 0; i < length; ++i)values[i] = i;
	int * intialValue = &values[0];
	int * result;
	result = (int*)reduce(source, &reducer, &hint, intialValue);
	
	assert(*result==45);

	dispose(source);
}

