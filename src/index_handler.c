#include <stdio.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

int index_handler(HTTP_socket *request,HTTP_socket *response)
{
	HTTP_engine_render(response,"public/html/index.html",NULL);
	fprintf(stdout,"index_handler\n");
	return 0;
}
