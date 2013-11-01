#include <stdio.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

int signin_handler(HTTP_socket *request,HTTP_socket *response)
{
	HTTP_engine_render(response,"public/html/signIn.html",NULL);
	fprintf(stdout,"signin_handler\n");
	return 0;
}
