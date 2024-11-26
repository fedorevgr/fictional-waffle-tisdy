#ifndef LAB_10_1_LIST_H
#define LAB_10_1_LIST_H

typedef struct node Node;

struct node
{
	void *data;
	Node *next;
};

typedef enum list_status_
{
	NORMAL,
	EMPTY,
	ERROR
} list_status_t;

Node *next(Node *node);
void *value(Node *);

list_status_t push(Node **head, void *data);
list_status_t pop(Node **head, void **data);

Node *sort(Node *head, int (*comp)(const void *, const void *));
void sorted_insert(Node **head, Node *element, int (*comp)(const void *, const void *));
Node *reverse(Node *head);

#endif //LAB_10_1_LIST_H
