#include <stdio.h>

#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

int error404_handler(HTTP_socket *request,HTTP_socket *response)
{
	HTTP_response_set_content(response,"<h1>Nice to meet you.</h1>");
	HTTP_response_flush(response);
	fprintf(stdout,"error404\n");
	return 0;
}
