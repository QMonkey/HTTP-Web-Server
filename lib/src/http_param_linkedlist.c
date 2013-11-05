#include <stdlib.h>

#include "http_string.h"
#include "http_param_linkedlist.h"

HTTP_Param_node* HTTP_Param_create_node(HTTP_String *key,HTTP_String *value)
{
	HTTP_Param_node *node = (HTTP_Param_node*)malloc(sizeof(HTTP_Param_node));
	node->key = HTTP_String_copy(key);
	node->value = HTTP_String_copy(value);
	return node;
}

HTTP_Param_node* HTTP_Param_insert(HTTP_Param_node **head,
		HTTP_String *key,HTTP_String *value)
{
	if(head == NULL)
	{
		return NULL;
	}
	if(*head == NULL)
	{
		*head = HTTP_Param_create_node(key,value);
		return *head;
	}

	int res;
	HTTP_Param_node *node = NULL;
	if((res = HTTP_String_strcmp2((*head)->key,key)) == 0)
	{
		HTTP_String_adjust_to((*head)->value,value);
	}
	else if(res > 0)
	{
		node = HTTP_Param_create_node(key,value);
		node->next = *head;
		*head = node;
	}
	else
	{
		node = HTTP_Param_insert(&(*head)->next,key,value);
	}
	return node;
}

HTTP_String* HTTP_Param_node_value(HTTP_Param_node *head,HTTP_String *key)
{
	return HTTP_Param_node_value3(head,key->content,HTTP_String_capacity(key));
}

HTTP_String* HTTP_Param_node_value3(HTTP_Param_node *head,char *key,int32_t size)
{
	if(head == NULL)
	{
		return NULL;
	}
	int res = HTTP_String_strcmp(head->key,key,size);
	if(res > 0)
	{
		return NULL;
	}
	if(res == 0)
	{
		return head->value;
	}
	return HTTP_Param_node_value3(head->next,key,size);
}

int HTTP_Param_pop(HTTP_Param_node **head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_Param_node *node = (*head)->next;
	HTTP_Param_destroy_node(*head);
	*head = node;
	return 0;
}

int HTTP_Param_destroy_node(HTTP_Param_node *node)
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

int HTTP_Param_destroy(HTTP_Param_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_Param_destroy(head->next);
	HTTP_Param_destroy_node(head);
	return 0;
}
