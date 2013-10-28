#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_urltree.h"

HTTP_node* HTTP_create_node(char *key,int (*handler)(HTTP_socket*,HTTP_socket*))
{
	return HTTP_create_node3(key,strlen(key),handler);
}

HTTP_node* HTTP_create_node3(char *key,int32_t size,
	int (*handler)(HTTP_socket*,HTTP_socket*))
{
	HTTP_node *node = (HTTP_node*)malloc(sizeof(HTTP_node));
	node->child = NULL;
	node->sibling = NULL;
	node->key = HTTP_create_string2(key,size);
	node->handler = handler;
	return node;
}

HTTP_node* HTTP_insert_node(HTTP_node **node,char *url,
	int (*handler)(HTTP_socket*,HTTP_socket*))
{
	if(url == NULL || *url == 0)
	{
		return NULL;
	}

	char *ptr = url;
	while(*ptr != '/' && *ptr != 0)
	{
		++ptr;
	}
	int32_t size = ptr - url + (*ptr ? 1 : 0);
	int flag = 0;
	do
	{
		if(*node == NULL)
		{
			*node = HTTP_create_node3(url,size,
				*ptr ? handler : NULL);
			HTTP_insert_node(&((*node)->child),ptr+1,handler);
		}
		else if(!(flag = HTTP_strcmp((*node)->key,url,size)))
		{
			HTTP_insert_node(&((*node)->child),ptr+1,handler);
		}
		else
		{
			node = &((*node)->sibling);
//			HTTP_insert_node(&((*node)->sibling),url,handler);
		}
	}
	while(flag);
}

HTTP_node* HTTP_find_node(HTTP_node *head,char *url)
{
}

HTTP_Handler HTTP_node_value(HTTP_node *node,char *url)
{
	if(node == NULL || url == NULL || *url == 0)
	{
		return NULL;
	}

	char *ptr = url;
	while(*ptr != '/' && *ptr != 0)
	{
		++ptr;
	}
	int32_t size = ptr - url + (*ptr ? 1 : 0);
	int (*handler)(HTTP_socket*,HTTP_socket*) = NULL;
	int flag = 0;
	do
	{
		if(!(flag = HTTP_strcmp(node->key,url,size)))
		{
			if(*ptr == 0 || *ptr == '/' && *(ptr+1) == 0)
			{
				handler = node->handler;
			}
			else
			{
				handler = HTTP_node_value(node->child,ptr+1);
			}
		}
		else
		{
//			handler = HTTP_node_value(node->sibling,url);
			node = node->sibling;
		}
	}
	while(flag && node != NULL);

	return handler;
}

int HTTP_destroy_tree(HTTP_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_destroy_tree(head->child);
	HTTP_destroy_tree(head->sibling);
	HTTP_destroy_node(head);
	return 0;
}

int HTTP_destroy_node(HTTP_node *node)
{
	if(node == NULL)
	{
		return -1;
	}
	HTTP_destroy_string(node->key);
	free(node);
	return 0;
}
