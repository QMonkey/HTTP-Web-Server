#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_urltree.h"

HTTP_URLTree_node* HTTP_URLTree_create_node(char *key,int (*handler)(HTTP_Socket*,HTTP_Socket*))
{
	return HTTP_URLTree_create_node3(key,strlen(key),handler);
}

HTTP_URLTree_node* HTTP_URLTree_create_node3(char *key,int32_t size,
	int (*handler)(HTTP_Socket*,HTTP_Socket*))
{
	HTTP_URLTree_node *node = (HTTP_URLTree_node*)malloc(sizeof(HTTP_URLTree_node));
	node->child = NULL;
	node->sibling = NULL;
	node->key = HTTP_String_create2(key,size);
	node->handler = handler;
	return node;
}

HTTP_URLTree_node* HTTP_URLTree_insert_node(HTTP_URLTree_node **node,char *url,
	int (*handler)(HTTP_Socket*,HTTP_Socket*))
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
	int32_t offset = (*ptr ? 1 : 0);
	int32_t size = ptr - url + offset;
	int flag = 0;
	HTTP_URLTree_node *ret_node = NULL;
	do
	{
		flag = 0;
		if(*node == NULL)
		{
			*node = HTTP_URLTree_create_node3(url,size,NULL);
			if(*ptr != 0 && *(ptr+1) != 0)
			{
				ret_node = HTTP_URLTree_insert_node(&((*node)->child),ptr+1,handler);
			}
			else
			{
				(*node)->handler = handler;
				ret_node = *node;
			}
		}
		else if(!HTTP_String_strcmp((*node)->key,url,size))
		{
			if(*ptr != 0 && *(ptr+1) != 0)
			{
				ret_node = HTTP_URLTree_insert_node(&((*node)->child),ptr+1,handler);
			}
			else
			{
				(*node)->handler = handler;
				ret_node = *node;
			}
		}
		else
		{
			node = &((*node)->sibling);
			flag = 1;
//			HTTP_insert_node(&((*node)->sibling),url,handler);
		}
	}
	while(flag);

	return ret_node;
}

HTTP_URLTree_node* HTTP_URLTree_find_node(HTTP_URLTree_node *head,char *url)
{
}

HTTP_Handler HTTP_URLTree_node_value(HTTP_URLTree_node *node,char *url)
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
	int (*handler)(HTTP_Socket*,HTTP_Socket*) = NULL;
	int flag = 0;
	do
	{
		flag = 0;
		if(!HTTP_String_strcmp(node->key,url,size))
		{
			if(*ptr != 0 && *(ptr+1) != 0)
			{
				handler = HTTP_URLTree_node_value(node->child,ptr+1);
			}
			else
			{
				handler = node->handler;
			}
		}
		else
		{
//			handler = HTTP_node_value(node->sibling,url);
			if(node->sibling != NULL)
			{
				node = node->sibling;
				flag = 1;
			}
		}
	}
	while(flag);

	return handler;
}

int HTTP_URLTree_destroy(HTTP_URLTree_node *head)
{
	if(head == NULL)
	{
		return -1;
	}
	HTTP_URLTree_destroy(head->child);
	HTTP_URLTree_destroy(head->sibling);
	HTTP_URLTree_destroy_node(head);
	return 0;
}

int HTTP_URLTree_destroy_node(HTTP_URLTree_node *node)
{
	if(node == NULL)
	{
		return -1;
	}
	HTTP_String_destroy(node->key);
	free(node);
	return 0;
}
