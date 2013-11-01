#include <stdio.h>
#include <string.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

#define URL_SIZE 8192

int default_handler(HTTP_socket *request,HTTP_socket *response)
{
	char url[URL_SIZE] = "public";
	int32_t len = strlen(url);
	int32_t size = HTTP_request_get_url(request,url + len);
	url[size + len] = 0;
	fprintf(stdout,"%s\n",url);
	if(HTTP_engine_render(response,url,NULL) == -1)
	{
		error404_handler(request,response);
		return -1;
	}
	fprintf(stdout,"default_handler\n");
	return 0;
}
