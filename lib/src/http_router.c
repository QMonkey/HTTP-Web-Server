#include "http_handler.h"
#include "http_urltree.h"
#include "http_router.h"

static int (*head)(HTTP_socket*,HTTP_socket*) = NULL;

int HTTP_init_router()
{
}

int (*)(HTTP_socket*,HTTP_socket*) HTTP_route(char *url)
{
	int (*handler)(HTTP_socket*,HTTP_socket) = HTTP_node_value(head,url);
	return handler != NULL ? handler : error404_handler;
}
