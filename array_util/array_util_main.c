#include <stdio.h>
#include <stdlib.h>
#include "array_util.h"





int main(void) {
	int length = 10;
	ArrayUtil array_1 = create(sizeof(int), length);
	ArrayUtil array_2 = create(sizeof(int), length);
	int *a = array_1.base;
	for (int i = 0; i < length; ++i)
		a[i] = i;
	print(array_1);
	printf("%d\n", are_equal(array_1,array_2));
	return 0;
}