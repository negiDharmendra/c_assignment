// # ifdef	_array_util_
// # define	_array_util_

typedef int(*MatchFunc)(void *,void *);

typedef struct array {
	void *base;
	int typeSize;
	int length;
} ArrayUtil;

ArrayUtil create(int , int);

int are_equal(ArrayUtil , ArrayUtil );
ArrayUtil resize(ArrayUtil , int );

int find_index(ArrayUtil,void *);
void dispose(ArrayUtil);
void* find_first(ArrayUtil, MatchFunc * , void *);
int isEven(void *,void *);
int isDivisible(void *,void *);
void* find_last(ArrayUtil, MatchFunc * , void *);


// # endif