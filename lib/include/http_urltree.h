#ifndef HTTP_URLTREE_H
#define HTTP_URLTREE_H

#include <stdint.h>

typedef int (*HTTP_Handler)(HTTP_Socket*,HTTP_Socket*);

typedef struct HTTP_Tree_node
{
	struct HTTP_Tree_node *child;
	struct HTTP_Tree_node *sibling;
	HTTP_String *key;
	int (*handler)(HTTP_Socket*,HTTP_Socket*);
} HTTP_URLTree_node;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_URLTree_node* HTTP_URLTree_create_node(char *key,int (*handler)(HTTP_Socket*,HTTP_Socket*));
extern HTTP_URLTree_node* HTTP_URLTree_create_node3(char *key,int32_t size,
	int (*handler)(HTTP_Socket*,HTTP_Socket*));
extern HTTP_URLTree_node* HTTP_URLTree_insert_node(HTTP_URLTree_node **node,char *url,
	int (*handler)(HTTP_Socket*,HTTP_Socket*));
extern HTTP_URLTree_node* HTTP_URLTree_find_node(HTTP_URLTree_node *head,char *url);
extern HTTP_Handler HTTP_URLTree_node_value(HTTP_URLTree_node *head,char *url);
extern int HTTP_URLTree_destroy(HTTP_URLTree_node *head);
extern int HTTP_URLTree_destroy_node(HTTP_URLTree_node *node);

#ifdef __cplusplus
}
#endif

#endif
