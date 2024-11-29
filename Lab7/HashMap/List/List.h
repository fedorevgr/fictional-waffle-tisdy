#ifndef LAB_10_1_LIST_H
#define LAB_10_1_LIST_H

typedef struct node Node;

struct node
{
	int data;
	Node *next;
};

typedef enum list_status_
{
	NORMAL,
	EMPTY,
	ERROR
} list_status_t;

list_status_t listPush(Node **head, int data);
list_status_t listRemove(Node **head, int data);



#endif //LAB_10_1_LIST_H
