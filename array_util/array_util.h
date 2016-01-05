// # ifdef	_array_util_
// # define	_array_util_

typedef struct array {
	void *base;
	int typeSize;
	int length;
} ArrayUtil;

ArrayUtil create(int , int);

int are_equal(ArrayUtil , ArrayUtil );
ArrayUtil resize(ArrayUtil , int );

int find_index(ArrayUtil,void *);

void print(ArrayUtil);

// # endif