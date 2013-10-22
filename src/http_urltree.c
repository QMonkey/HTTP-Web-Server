#include "http_string.h"
#include "http_urltree.h"

HTTP_node* HTTP_create_node(char *key,
	int (*handler)(HTTP_request *request,HTTP_response *response))
{
	return HTTP_create_node3(key,strlen(key),handler);
}

HTTP_node* HTTP_create_node3(char *key,int32_t size,
	int (*handler)(HTTP_request *request,HTTP_response *response))
{
	HTTP_node *node = (HTTP_node*)malloc(sizeof(HTTP_node));
	node->child = NULL;
	node->sibling = NULL;
	node->key = HTTP_create_string2(key,size);
	node->handler = handler;
	return node;
}

HTTP_node* HTTP_insert_node(HTTP_node **node,char *url,
	int (*handler)(HTTP_request *request,HTTP_response *response))
{
	if(url == NULL || *url == 0)
	{
		return NULL;
	}
	if(*url == '/')
	{
		HTTP_insert_node(node,url+1,handler);
	}
	else
	{
		char *ptr = url;
		while(*ptr != '/' && *ptr != 0)
		{
			++ptr;
		}
		int32_t length = ptr-url;
		if(**node == NULL)
		{
			*node = HTTP_create_node3(url,length,
				*ptr ? handler : DEFAULT_HANDLER);
			HTTP_insert_node(&((*node)->child),ptr+1,handler);
		}
		else if(!HTTP_strcmp((*node)->key,url,length))
		{
			HTTP_insert_node(&((*node)->child),ptr+1,handler);
		}
		else
		{
			HTTP_insert_node(&((*node)->sibling),url,handler);
		}
	}
}

HTTP_node* HTTP_find_node(HTTP_node *head,char *url)
{
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
