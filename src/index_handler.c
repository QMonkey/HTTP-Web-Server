#include <stdio.h>

#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

int index_handler(HTTP_socket *request,HTTP_socket *response)
{
	fprintf(stdout,"index\n");
	return 0;
}
