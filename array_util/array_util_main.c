#include <stdio.h>
#include <stdlib.h>
#include "array_util.h"





int main(void) {
	ArrayUtil array_1 = create(sizeof(int), 2);
	ArrayUtil array_2 = create(sizeof(int), 3);
	printf("array_1.base----- %d\n", array_1.typeSize);
	printf("array_1.length----- %d\n", array_1.length);
	printf("array_2.base----- %d\n", array_2.typeSize);
	printf("array_2.length----- %d\n", array_2.length);
	printf("%d\n", areEqual(array_1,array_2));
	return 0;
}