
typedef struct element {
	void *val;
	int index;
	struct element *next;
}Element;

typedef	struct linked_list {
	Element *head;
	Element *tail;
	int length;
} LinkedList;

typedef void (*ElementProcessor)(void *);
typedef int (*MatchFunc)(void *,void *);
typedef void (*ConvertFunc)(void *,void *,void *);
typedef	void *(*Reducer)(void*,void*,void*);

LinkedList create_list(void);
int add_to_list(LinkedList *,void *);
void *get_first_element(LinkedList list);
void *get_last_element(LinkedList list);
void for_each(LinkedList, ElementProcessor);
void * get_element_at(LinkedList, int );
int indexOf(LinkedList, void *);
void * delete_element_at(LinkedList *, int);
int asArray(LinkedList, void **, int maxElements);

LinkedList  filter(LinkedList, MatchFunc, void * );

LinkedList reverse(LinkedList);


LinkedList map(LinkedList, ConvertFunc, void * );

void *reduce(LinkedList, Reducer, void *hint, void *initialValue);

