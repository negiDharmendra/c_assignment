// # ifdef	_array_util_
// # define	_array_util_

typedef int(*MatchFunc)(void *, void *);
typedef void (*ConvertFunc)(void*,void*, void*);
typedef void (*OperationFunc)(void*, void*);
typedef void* (*ReducerFunc)(void* , void* , void*);
typedef struct array {
	int typeSize;
	int length;
	void *base;
} ArrayUtil;

ArrayUtil create(int , int);

int are_equal(ArrayUtil , ArrayUtil );
ArrayUtil resize(ArrayUtil , int );

int find_index(ArrayUtil, void *);
void dispose(ArrayUtil);
void* find_first(ArrayUtil, MatchFunc * , void *);
int isEven(void *, void *);
int isDivisible(void *, void *);
void* find_last(ArrayUtil, MatchFunc * , void *);
int count(ArrayUtil, MatchFunc*, void*);
int filter(ArrayUtil , MatchFunc* , void* , void** , int );
void map(ArrayUtil , ArrayUtil , ConvertFunc* , void* );


void forEach(ArrayUtil , OperationFunc*, void*);


void* reduce(ArrayUtil , ReducerFunc* , void* , void* );
 

// # endif