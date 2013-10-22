#ifndef HTTP_URLTREE_H
#define HTTP_URLTREE_H

#include <stdint.h>

typedef struct HTTP_urltree_node
{
	struct HTTP_urltree_node *child;
	struct HTTP_urltree_node *sibling;
	HTTP_string *key;
	int (*handler)(HTTP_reqest*,HTTP_response*);
} HTTP_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_node* HTTP_create_node(char *key,
	int (*handler)(HTTP_request *request,HTTP_response *response));
extern HTTP_node* HTTP_create_node3(char *key,int32_t size,
	int (*handler)(HTTP_request *request,HTTP_response *response));
extern HTTP_node* HTTP_insert_node(HTTP_node **node,char *url,
	int (*handler)(HTTP_request *request,HTTP_response *response));
extern HTTP_node* HTTP_find_node(HTTP_node *head,char *url);
extern int (*)(HTTP_request*,HTTP_response*) HTTP_node_value(HTTP_node *head,char *url);
extern int HTTP_destroy_tree(HTTP_node *head);
extern int HTTP_destroy_node(HTTP_node *node);

#ifdef __cplusplus
}
#endif

#endif
