#include <stdio.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_handler.h"
#include "http_urltree.h"
#include "http_router.h"

static HTTP_node *head = NULL;

int HTTP_init_router()
{
	HTTP_insert_node(&head,"/html/",index_handler);
	HTTP_insert_node(&head,"/html/index.html",index_handler);
	HTTP_insert_node(&head,"/html/signIn.html",signin_handler);
	HTTP_insert_node(&head,"/html/signUp.html",signup_handler);
}

HTTP_Handler HTTP_route(char *url)
{
	int (*handler)(HTTP_socket*,HTTP_socket*) = HTTP_node_value(head,url);
	return handler != NULL ? handler : error404_handler;
}
