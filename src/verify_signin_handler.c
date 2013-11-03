#include <unistd.h>
#include <stdio.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

static int do_get(HTTP_Socket *request,HTTP_Socket *response);
static int do_post(HTTP_Socket *request,HTTP_Socket *response);

int verify_signin_handler(HTTP_Socket *request,HTTP_Socket *response)
{
	if(HTTP_Request_get_method(request) == 0)
	{
		do_get(request,response);
	}
	return 0;
}

static int do_get(HTTP_Socket *request,HTTP_Socket *response)
{
	error404_handler(request,response);
	return 0;
}

static int do_post(HTTP_Socket *request,HTTP_Socket *response)
{
	HTTP_Param_node *args = HTTP_Request_get_params(request);
	HTTP_String *name = HTTP_Param_node_value3(args,"name",4);
	HTTP_String *password = HTTP_Param_node_value3(args,"password",8);
	write(STDOUT_FILENO,name->content,HTTP_String_capacity(name));
	write(STDOUT_FILENO,"\n",1);
	write(STDOUT_FILENO,password->content,HTTP_String_capacity(password));
	write(STDOUT_FILENO,"\n",1);
	error404_handler(request,response);
	fprintf(stdout,"verify_signin_handler\n");
	return 0;
}
