#include <stdio.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_handler.h"
#include "http_urltree.h"
#include "http_router.h"

static HTTP_URLTree_node *head = NULL;

int HTTP_Router_init()
{
	HTTP_URLTree_insert_node(&head,"/html/",index_handler);
	HTTP_URLTree_insert_node(&head,"/html/index.html",index_handler);
	HTTP_URLTree_insert_node(&head,"/html/signIn.html",signin_handler);
	HTTP_URLTree_insert_node(&head,"/html/signUp.html",signup_handler);
	HTTP_URLTree_insert_node(&head,"/html/verifySignIn",verify_signin_handler);
	HTTP_URLTree_insert_node(&head,"/html/verifySignUp",verify_signup_handler);
}

HTTP_Handler HTTP_Router_route(char *url)
{
	int (*handler)(HTTP_Socket*,HTTP_Socket*) = HTTP_URLTree_node_value(head,url);
	return handler != NULL ? handler : default_handler;
}

int HTTP_Router_destroy()
{
	return HTTP_URLTree_destroy(head);
}
