#include <stdio.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

static int do_get(HTTP_Socket *request,HTTP_Socket *response);
static int do_post(HTTP_Socket *request,HTTP_Socket *response);

int index_handler(HTTP_Socket *request,HTTP_Socket *response)
{
	switch(HTTP_Request_get_method(request))
	{
	case 0:
		do_get(request,response);
		break;
	case 1:
		do_post(request,response);
		break;
	default:
		error404_handler(request,response);
		break;
	}
	return 0;
}

static int do_get(HTTP_Socket *request,HTTP_Socket *response)
{
	HTTP_Engine_render(response,"public/html/index.html",NULL);
	fprintf(stdout,"index_handler\n");
	return 0;
}

static int do_post(HTTP_Socket *request,HTTP_Socket *response)
{
	error404_handler(request,response);
	return 0;
}
