#include <stdio.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

int error404_handler(HTTP_socket *request,HTTP_socket *response)
{
	HTTP_engine_render(response,"public/html/error404.html",NULL);
	fprintf(stdout,"error404_handler\n");
	return 0;
}
