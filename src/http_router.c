#include "http_handler.h"
#include "http_urltree.h"
#include "http_router.h"

static int (*head)(HTTP_request*,HTTP_response*) = NULL;

int HTTP_init_router()
{
}

int (*)(HTTP_request*,HTTP_response*) HTTP_route(char *url)
{
	int (*handler)(HTTP_request*,HTTP_response) = HTTP_node_value(head,url);
	return handler != NULL ? handler : error404_handler;
}
