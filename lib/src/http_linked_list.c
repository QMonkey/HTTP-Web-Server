#include <stdlib.h>

#include "http_string.h"
#include "http_linked_list.h"

HTTP_list_node* HTTP_list_create(HTTP_string *key,HTTP_string *value)
{
	HTTP_list_node *node = (HTTP_list_node*)malloc(sizeof(HTTP_list_node));
	node->key = HTTP_string_copy(key);
	node->value = HTTP_string_copy(value);
	node->next = NULL;
	return node;
}

HTTP_list_node* HTTP_list_insert(HTTP_list_node **head,HTTP_string *key,HTTP_string *value)
{
	if(head == NULL)
	{
		return NULL;
	}
	int res;
	HTTP_list_node *node = NULL;
	if((res = HTTP_strcmp2((*head)->key,key)) == 0)
	{
		node = HTTP_string_adjust_to((*head)->value,value);
	}
	else if(res < 0)
	{
		node = HTTP_list_create(key,value);
		node->next = *head;
		*head = node;
	}
	else
	{
		node = HTTP_list_insert(&(*head)->next,key,value);
	}
	return node;
}

int HTTP_list_pop(HTTP_list_node **head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_list_node *node = (*head)->next;
	HTTP_list_destroy_node(*head);
	*head = node;
	return 0;
}

int HTTP_list_destroy_node(HTTP_list_node *node)
{
	if(node == NULL)
	{
		return -1;
	}
	HTTP_destroy_string(node->key);
	HTTP_destroy_string(node->value);
	free(node);
	return 0;
}

int HTTP_list_destroy(HTTP_list_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_list_destroy(head->next);
	HTTP_list_destroy_node(head);
	return 0;
}
