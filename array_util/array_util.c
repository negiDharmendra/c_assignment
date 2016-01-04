#include <stdlib.h>
#include	"array_util.h"


ArrayUtil create(int typeSize, int length) {
	ArrayUtil array = *(ArrayUtil *)malloc(sizeof(ArrayUtil));
	array.base = NULL;
	array.typeSize = typeSize;
	array.length = length;
	return array;
}

int areEqual(ArrayUtil array_1, ArrayUtil array_2) {
	if(array_1.length==array_2.length&&array_1.typeSize==array_2.typeSize)
		return 1;
	else return 0;
}