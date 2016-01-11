
typedef struct element {
	void *val;
	struct element *next;
}Element;

typedef	struct linked_list {
	Element *head;
	Element *tail;
	int length;
} LinkedList;

typedef void (*ElementProcessor)(void *);

LinkedList create_list(void);
int add_to_list(LinkedList *,void *);
void *get_first_element(LinkedList list);
void *get_last_element(LinkedList list);
void forEach(LinkedList, ElementProcessor);