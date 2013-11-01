#include <stdio.h>
#include <string.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

#define URL_SIZE 8192

static int do_get(HTTP_Socket *request,HTTP_Socket *response);
static int do_post(HTTP_Socket *request,HTTP_Socket *response);

int default_handler(HTTP_Socket *request,HTTP_Socket *response)
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
	char url[URL_SIZE] = "public";
	int32_t len = strlen(url);
	int32_t size = HTTP_Request_get_url(request,url + len);
	url[size + len] = 0;
	if(HTTP_Engine_render(response,url,NULL) == -1)
	{
		error404_handler(request,response);
		return -1;
	}
	fprintf(stdout,"default_handler\n");
	return 0;
}

static int do_post(HTTP_Socket *request,HTTP_Socket *response)
{
	error404_handler(request,response);
	return 0;
}
