#include <stdlib.h>

#include "http_string.h"
#include "http_replacer_linkedlist.h"

HTTP_replacer_node* HTTP_replacer_create(char *begin,char *end,HTTP_String *value)
{
	HTTP_replacer_node *node = (HTTP_replacer_node*)malloc(sizeof(HTTP_replacer_node));
	node->begin = begin;
	node->end = end;
	node->value = HTTP_String_copy(value);
	node->next = NULL;
	return node;
}

HTTP_replacer_node* HTTP_replacer_insert(HTTP_replacer_node **head,
		char *begin,char *end,HTTP_String *value)
{
	if(head == NULL)
	{
		return NULL;
	}
	HTTP_replacer_node *node = NULL;
	if((*head)->begin == begin)
	{
		(*head)->end = end;
		HTTP_String_adjust_to((*head)->value,value);
	}
	else if((*head)->begin < 0)
	{
		node = HTTP_replacer_create(begin,end,value);
		node->next = *head;
		*head = node;
	}
	else
	{
		node = HTTP_replacer_insert(&(*head)->next,begin,end,value);
	}
	return node;
}

int HTTP_replacer_pop(HTTP_replacer_node **head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_replacer_node *node = (*head)->next;
	HTTP_replacer_destroy_node(*head);
	*head = node;
	return 0;
}

int HTTP_replacer_destroy_node(HTTP_replacer_node *node)
{
	if(node == NULL)
	{
		return -1;
	}
	HTTP_String_destroy(node->value);
	free(node);
	return 0;
}

int HTTP_replacer_destroy(HTTP_replacer_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_replacer_destroy(head->next);
	HTTP_replacer_destroy_node(head);
	return 0;
}
