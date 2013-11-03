#ifndef HTTP_PARAM_LINKEDLIST_H
#define HTTP_PARAM_LINKEDLIST_H

#include "http_string.h"

typedef struct HTTP_param_linkedlist_node
{
	HTTP_String *key;
	HTTP_String *value;
	struct HTTP_param_linkedlist_node *next;
} HTTP_Param_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_Param_node* HTTP_Param_create_node(HTTP_String *key,HTTP_String *value);
extern HTTP_Param_node* HTTP_Param_insert(HTTP_Param_node **head,
		HTTP_String *key,HTTP_String *value);
extern HTTP_String* HTTP_Param_node_value(HTTP_Param_node *head,HTTP_String *key);
extern HTTP_String* HTTP_Param_node_value3(HTTP_Param_node *head,char *key,int32_t size);
extern int HTTP_Param_pop(HTTP_Param_node **head);
extern int HTTP_Param_destroy(HTTP_Param_node *head);
extern int HTTP_Param_destroy_node(HTTP_Param_node *node);

#ifdef __cplusplus
}
#endif

#endif
