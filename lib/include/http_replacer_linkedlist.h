#ifndef HTTP_REPLACER_LINKEDLIST_H
#define HTTP_REPLACER_LINKEDLIST_H

#include "http_string.h"

typedef struct HTTP_replacer_linkedlist_node
{
	char *begin;
	char *end;
	HTTP_string *value;
	struct HTTP_replacer_linkedlist_node *next;
} HTTP_replacer_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_replacer_node* HTTP_replacer_create(char *begin,char *end,HTTP_string *value);
extern HTTP_replacer_node* HTTP_replacer_insert(HTTP_replacer_node **head,char *begin,char *end,HTTP_string *value);
extern int HTTP_replacer_pop(HTTP_replacer_node **head);
extern int HTTP_replacer_destroy(HTTP_replacer_node *head);
extern int HTTP_replacer_destroy_node(HTTP_replacer_node *node);

#ifdef __cplusplus
}
#endif

#endif
