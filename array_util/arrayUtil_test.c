#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "array_util.h"

void test_create_array(){
	ArrayUtil array_1 =  create(sizeof(int), 2);

	assert(sizeof(array_1.base)==8);
	assert(array_1.length == 2);
	assert(array_1.typeSize == 4);
}

void test_are_equal(){
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(int), 2);

	assert(are_equal( array_1, array_2)==1);
	assert(are_equal( array_1, array_2)!=2);
}

void test_array_with_defferent_type_size_are_not_equal(){
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(char), 2);

	assert(are_equal( array_1, array_2)==0);
	assert(are_equal( array_1, array_2)!=1);
}

void test_array_with_defferent_length_are_not_equal(){
	ArrayUtil array_1 =  create(sizeof(int), 2);
	ArrayUtil array_2 =  create(sizeof(int), 3);

	assert(are_equal( array_1, array_2)==0);
	assert(are_equal( array_1, array_2)!=1);
}

void test_array_with_defferent_element_are_not_equal(){
	int size = sizeof(int);
	int length = 20;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
	{
		*((int *)(array_1.base)+i-65) = i;
		*((int *)(array_2.base)+i-65) = i+1;
	}
	assert(are_equal( array_1, array_2)==1);
}

void test_resize(){
	int size = sizeof(int);
	int length = 4;
	int new_length = 9;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  resize(array_1, new_length);
	
	assert(array_2.typeSize==4);
	assert(array_2.length==new_length);
}

void test_find_index(){
	int size = sizeof(int);
	int length = 26;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
		*(( int *)(array_1.base)+i-65) = i;
	int d  = 90;
	assert(find_index(array_1,&d)==25);
}


