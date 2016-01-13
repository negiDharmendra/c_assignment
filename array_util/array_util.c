#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include	"array_util.h"


ArrayUtil create(int typeSize, int length) {
	ArrayUtil array = *(ArrayUtil *)calloc(1,sizeof(ArrayUtil));
	array.base = calloc(length, typeSize);
	array.typeSize = typeSize;
	array.length = length;
	return array;
}

int are_equal(ArrayUtil array_1, ArrayUtil array_2) {
	int length = (array_1.length == array_2.length);
	int size = (array_1.typeSize == array_2.typeSize);
	if (length != 1 || size != 1) return 0;
	for (int i = 0; i < array_1.length * array_1.typeSize; ++i)
		if (*((unsigned char *)array_1.base + i) - * ((unsigned char *)array_2.base + i) != 0) return 0;
	return 1;
}


ArrayUtil resize(ArrayUtil array, int length ) {
	array.base = realloc(array.base, length);
	array.length = length;
	return array;
}

int find_index(ArrayUtil array, void *val) {
	for (int i = 0; i < array.length; ++i)
		if (memcmp(array.base + (i * array.typeSize), val, array.typeSize) == 0)return i;
	return -1;
}

void dispose(ArrayUtil array) {
	free(array.base);
}



void *find_first(ArrayUtil array, MatchFunc *match, void *hint) {
	for (int i = 0; i < array.length; ++i) {
		int result = (*match)(hint, array.base + (i * array.typeSize));
		if (result == 1) {
			return (array.base + (i * array.typeSize));
		}
	}
	return NULL;
};


void *find_last(ArrayUtil array, MatchFunc *match, void *hint) {
	for (int i = array.length - 1; i >= 0; --i) {
		int result = (*match)(hint, array.base + (i * array.typeSize));
		if (result == 1) {
			return (array.base + (i * array.typeSize));
		}
	}
	return NULL;
};


int count(ArrayUtil util, MatchFunc* match, void* hint) {
	int count = 0;
	for (int i = util.length - 1; i >= 0; --i) {
		int result = (*match)(hint, util.base + (i * util.typeSize));
		if (result == 1) {
			count++;
		}
	}
	return count;
};


int filter(ArrayUtil util, MatchFunc *match, void* hint, void** destination, int maxItems) {
	void *base =util.base;
	int count = 0;
	for (int i = 0; i < util.length*util.typeSize; i+=util.typeSize) {
		if ((*match)(hint, &base[i])==1) {
			if (count < maxItems){
				destination[count]= &(base[i]);
				count++;
			};
		}
	};
	return count;
}

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc * convert, void* hint){
	void *source_base = source.base;
	void *dest_base = destination.base;
	for (int i = 0; i < source.length*source.typeSize; i+=source.typeSize)
		(*convert)(hint,&source_base[i],&dest_base[i]);
};

void forEach(ArrayUtil util, OperationFunc *operation, void * hint){
	void *util_base = util.base;
	for (int i = 0; i < util.length*util.typeSize; i+=util.typeSize)
		(*operation)(hint,&util_base[i]);
};

void* reduce(ArrayUtil util, ReducerFunc* reducer, void* hint, void* intialValue){
	void *itm;
	for (int i = 0; i < util.length*util.typeSize; i+=util.typeSize){
		itm = util.base+i;
		intialValue = (*reducer)(hint,intialValue ,itm);
	};
	return intialValue;
};



