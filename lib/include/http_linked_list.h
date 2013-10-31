#ifndef HTTP_LINKED_LIST_H
#define HTTP_LINKED_LIST_H

#include "http_string.h"

typedef struct HTTP_linked_list_node
{
	HTTP_string *key;
	HTTP_string *value;
	struct HTTP_linked_list_node *next;
} HTTP_list_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_list_node* HTTP_list_create(HTTP_string *key,HTTP_string *value);
extern HTTP_list_node* HTTP_list_insert(HTTP_list_node **head,HTTP_string *key,HTTP_string *value);
extern int HTTP_list_pop(HTTP_list_node **head);
extern int HTTP_list_destroy_node(HTTP_list_node *node);
extern int HTTP_list_destroy(HTTP_list_node *head);

#ifdef __cplusplus
}
#endif

#endif
