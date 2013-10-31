#include <stdlib.h>

#include "http_string.h"
#include "http_linked_list.h"

HTTP_list_node* HTTP_list_create(void *data)
{
	HTTP_list_node *node = (HTTP_list_node*)malloc(sizeof(HTTP_list_node));
	node->data =data;
	node->next = NULL;
	return node;
}

HTTP_list_node* HTTP_list_insert(HTTP_list_node **head,void *data,
		int (*comparator)(void*,void*),int (*destructor)(void*))
{
	if(head == NULL)
	{
		return NULL;
	}
	int res;
	HTTP_list_node *node = NULL;
	if((res = comparator((*head)->data,data)) == 0)
	{
		destructor((*head)->data);
		(*head)->data = data;
	}
	else if(res < 0)
	{
		node = HTTP_list_create(data);
		node->next = *head;
		*head = node;
	}
	else
	{
		node = HTTP_list_insert(&(*head)->next,data,destructor);
	}
	return node;
}

int HTTP_list_pop(HTTP_list_node **head,int (*destructor)(void*))
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_list_node *node = (*head)->next;
	HTTP_list_destroy_node(*head,destructor);
	*head = node;
	return 0;
}

int HTTP_list_destroy_node(HTTP_list_node *node,int (*destructor)(void*))
{
	if(node == NULL)
	{
		return -1;
	}
	destructor(node->data);
	free(node);
	return 0;
}

int HTTP_list_destroy(HTTP_list_node *head,int (*destructor)(void*))
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_list_destroy(head->next,destructor);
	HTTP_list_destroy_node(head,destructor);
	return 0;
}
