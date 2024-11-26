#include "List.h"

#include <stdlib.h>

Node *next(Node *node)
{
	return node->next;
}

void *value(Node *node)
{
	return node->data;
}


list_status_t push(Node **head, void *data)
{
	list_status_t ec = NORMAL;
	if (*head == NULL)
	{
		*head = malloc(sizeof(Node));

		if (!*head)
			ec = ERROR;
		else
		{
			(*head)->data = data;
			(*head)->next = NULL;
		}
	}
	else
	{
		Node *curr_node = *head;
		while (curr_node->next)
			curr_node = curr_node->next;

		Node *new_node = malloc(sizeof(Node));
		curr_node->next = new_node;
		if (!new_node)
			ec = ERROR;
		else
		{
			new_node->data = data;
			new_node->next = NULL;
		}
	}

	return ec;
}

list_status_t pop(Node **head, void **data)
{
	if (*head == NULL)
		return EMPTY;

	Node *prev_node = NULL;
	Node *node = *head;
	while (node->next)
	{
		prev_node = node;
		node = node->next;
	}

	if (prev_node)
		prev_node->next = NULL;
	else
		*head = NULL;

	*data = node->data;
	free(node);

	return NORMAL;
}

Node *sort(Node *head, int (*comp)(const void *, const void *))
{
	if (head == NULL || head->next == NULL)
		return head;

	Node *prev = head, *curr = head->next, *next;

	while (curr)
	{
		next = curr->next;
		sorted_insert(&head, curr, comp);

		if (curr->next == curr || curr->next == NULL)
		{
			curr->next = next;
			prev = curr;
		}
		else
			prev->next = next;

		curr = next;
	}

	return head;
}

void sorted_insert(Node **head, Node *element, int (*comp)(const void *, const void *))
{
	if (element == NULL || head == NULL || comp == NULL)
		return;

	if (*head == NULL || comp((*head)->data, element->data) >= 0)
	{
		element->next = *head;
		*head = element;
		return;
	}

	Node *current = *head;
	while (current->next && comp(current->next->data, element->data) < 0)
		current = current->next;

	element->next = current->next;
	current->next = element;
}

Node *reverse(Node *head)
{
	Node *previous = NULL, *current = head, *next = NULL;
	while (current)
	{
		next = current->next;
		current->next = previous;

		previous = current;
		current = next;
	}
	return previous;
}

