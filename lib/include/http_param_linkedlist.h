#ifndef HTTP_PARAM_LINKEDLIST_H
#define HTTP_PARAM_LINKEDLIST_H

#include "http_string.h"

typedef struct HTTP_param_linkedlist_node
{
	HTTP_String *key;
	HTTP_String *value;
	struct HTTP_param_linkedlist_node *next;
} HTTP_param_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_param_node* HTTP_param_create(HTTP_String *key,HTTP_String *value);
extern HTTP_param_node* HTTP_param_insert(HTTP_param_node **head,
		HTTP_String *key,HTTP_String *value);
extern int HTTP_param_pop(HTTP_param_node **head);
extern int HTTP_param_destroy(HTTP_param_node *head);
extern int HTTP_param_destroy_node(HTTP_param_node *node);

#ifdef __cplusplus
}
#endif

#endif
