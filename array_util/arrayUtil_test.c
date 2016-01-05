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
	assert(are_equal( array_1, array_2)!=0);
}

void test_are_equal_for_integer(){
	int length = 10;
	int size = 4;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
	{
		*((int *)(array_1.base)+i-65) = i;
		*((int *)(array_2.base)+i-65) = i;
	}

	assert(are_equal( array_1, array_2)==1);
	assert(are_equal( array_1, array_2)!=2);
}


void test_are_equal_for_character(void){
	int length = 10;
	int size = 1;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
	{
		*((char *)(array_1.base)+i-65) = i;
		*((char *)(array_2.base)+i-65) = i;
	}
	assert(are_equal( array_1, array_2)==1);
	assert(are_equal( array_1, array_2)!=2);
}

void test_are_equal_for_double(){
	int length = 10;
	int size = 8;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
	{
		*((double *)(array_1.base)+i-65) = i;
		*((double *)(array_2.base)+i-65) = i;
	}

	assert(are_equal( array_1, array_2)==1);
	assert(are_equal( array_1, array_2)!=2);
}

void test_are_equal_for_string(){
	int length = 10;
	int size = 1;
	ArrayUtil array_1 =  create(size, length);
	ArrayUtil array_2 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
	{
		*((char *)(array_1.base)+i-65) = "hello";
		*((char *)(array_2.base)+i-65) = "hello";
	}

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
	assert(are_equal( array_1, array_2)==0);
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

void test_find_index_return_minus_one_if_elsment_not_exist(){
	int size = sizeof(int);
	int length = 4;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
		*(( int *)(array_1.base)+i-65) = i;
	int d  = 50;
	assert(find_index(array_1,&d)==-1);
}

void test_find_index_also_works_for_char(){
	int size = sizeof(char);
	int length = 26;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
		*(( char *)(array_1.base)+i-65) = i;
	char d  = 'Z';
	char e = 'B';
	assert(find_index(array_1,&d)==25);
	assert(find_index(array_1,&e)!=2);
}

void test_find_index_also_works_for_double(){
	int size = sizeof(double);
	int length = 10;
	ArrayUtil array_1 =  create(size, length);
	for (int i = 65; i < 65+length; ++i)
		*(( double *)(array_1.base)+i-65) = i;
	double d  = 70;
	double e = 'B';
	assert(find_index(array_1,&d)==5);
	assert(find_index(array_1,&e)==1);
}


int isEven(void *hint,void *val){
	return (*(int*)val)%2==0;
};



void test_find_first_gives_firs_even_num(){
	int size = sizeof(int);
	int length = 4;
	MatchFunc map= isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 26;
	base[3] = 48;
	void *result = find_first(array_1,&map,NULL);
	if(result!=NULL)assert(*(int*)result==26);
	else assert((int*)result==0);
}

void test_find_first_gives_NULL_in_the_absence_of_even_num(){
	int size = sizeof(int);
	int length = 4;
	MatchFunc map= isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 27;
	base[3] = 45;
	void *result = find_first(array_1,&map,NULL);
	if(result!=NULL)assert(*(int*)result==26);
	else assert((int*)result==0);
}


int isDivisibleInt(void *hint,void *val){
	return (*(int*)val)%(*(int*)hint)==0;
};
int isDivisibleChar(void *hint,void *val){
	return (*(char*)val)%(*(char*)hint)==0;
};

void test_find_first_gives_num_whish_is_divisible_by_hint_num_for_Char(){
	int size = sizeof(char);
	int length = 4;
	MatchFunc map= isDivisibleChar;
	ArrayUtil array_1 =  create(size, length);
	char *base = ( char *)(array_1.base);
	base[0] = 'A';
	base[1] = 'B';
	base[2] = 'C';
	base[3] = 'D';
	char hint = 'A';
	void *result;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(char*)result=='A');
	else assert((int*)result==0);

	hint = 'B';
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(char*)result=='B');
	else assert((int*)result==0);

	hint = 'C';
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(char*)result=='C');
	else assert((int*)result==0);

	hint = 'D';
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(char*)result=='D');
	else assert((int*)result==0);

	hint = 'R';
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(char*)result=='R');
	else assert((int*)result==0);
}

void test_find_first_gives_num_whish_is_divisible_by_hint_num_for_int(){
	int size = sizeof(int);
	int length = 4;
	MatchFunc map= isDivisibleChar;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 45;
	base[3] = 22;
	int hint = 23;
	void *result;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==23);
	else assert((int*)result==0);

	hint = 9;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==27);
	else assert((int*)result==0);

	hint = 2;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==22);
	else assert((int*)result==0);

	hint =15;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==45);
	else assert((int*)result==3);

	hint =15;
	result = find_first(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==45);
	else assert((int*)result==3);	
}

void test_find_last_gives_num_whish_is_divisible_by_hint_num_for_int(){
	int size = sizeof(int);
	int length = 5;
	MatchFunc map= isDivisibleInt;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 33;
	base[1] = 27;
	base[2] = 45;
	base[3] = 22;
	base[4] = 15;
	int hint = 11;
	void *result;
	result = find_last(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==22);
	else assert((int*)result==0);

	hint = 9;
	result = find_last(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==45);
	else assert((int*)result==0);

	hint =15;
	result = find_last(array_1,&map,&hint);
	if(result!=NULL)assert(*(int*)result==15);
	else assert((int*)result==3);
	
}


void test_find_last_gives_firs_even_num(){
	int size = sizeof(int);
	int length = 4;
	MatchFunc map= isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 26;
	base[3] = 28;
	void *result = find_last(array_1,&map,NULL);
	if(result!=NULL)assert(*(int*)result==28);
	else assert((int*)result==0);
}

void test_find_last_gives_NULL_in_the_absence_of_even_num(){
	int size = sizeof(int);
	int length = 4;
	MatchFunc map= isEven;
	ArrayUtil array_1 =  create(size, length);
	int *base = ( int *)(array_1.base);
	base[0] = 23;
	base[1] = 27;
	base[2] = 27;
	base[3] = 45;
	void *result = find_last(array_1,&map,NULL);
	if(result!=NULL)assert(*(int*)result==26);
	else assert((int*)result==0);
}