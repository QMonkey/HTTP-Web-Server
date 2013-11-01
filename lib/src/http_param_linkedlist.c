#include <stdlib.h>

#include "http_string.h"
#include "http_param_linkedlist.h"

HTTP_param_node* HTTP_param_create(HTTP_String *key,HTTP_String *value)
{
	HTTP_param_node *node = (HTTP_param_node*)malloc(sizeof(HTTP_param_node));
	node->key = HTTP_String_copy(key);
	node->value = HTTP_String_copy(value);
	return node;
}

HTTP_param_node* HTTP_param_insert(HTTP_param_node **head,
		HTTP_String *key,HTTP_String *value)
{
	if(head == NULL)
	{
		return NULL;
	}
	int res;
	HTTP_param_node *node = NULL;
	if((res = HTTP_String_strcmp2((*head)->key,key)) == 0)
	{
		HTTP_String_adjust_to((*head)->value,value);
	}
	else if(res < 0)
	{
		node = HTTP_param_create(key,value);
		node->next = *head;
		*head = node;
	}
	else
	{
		node = HTTP_param_insert(&(*head)->next,key,value);
	}
	return node;
}

int HTTP_param_pop(HTTP_param_node **head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_param_node *node = (*head)->next;
	HTTP_param_destroy_node(*head);
	*head = node;
	return 0;
}

int HTTP_param_destroy_node(HTTP_param_node *node)
{
	if(node == NULL)
	{
		return -1;
	}
	HTTP_String_destroy(node->key);
	HTTP_String_destroy(node->value);
	free(node);
	return 0;
}

int HTTP_param_destroy(HTTP_param_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_param_destroy(head->next);
	HTTP_param_destroy_node(head);
	return 0;
}
