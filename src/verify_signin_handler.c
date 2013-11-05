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
	error404_handler(request,response);
	return 0;
}

static int do_post(HTTP_Socket *request,HTTP_Socket *response)
{
	/*
	HTTP_Param_node *args = NULL;
	HTTP_Param_insert(&args,HTTP_String_create2("Monkey",strlen("Monkey")),
			HTTP_String_create2("QMonkey",strlen("QMonkey")));
	HTTP_Param_insert(&args,HTTP_String_create2("OMonkey",strlen("OMonkey")),
			HTTP_String_create2("Monkey",strlen("Monkey")));
	HTTP_Param_insert(&args,HTTP_String_create2("QMonkey",strlen("QMonkey")),
			HTTP_String_create2("OMonkey",strlen("OMonkey")));
	HTTP_Param_insert(&args,HTTP_String_create2("QYoCiMonkey",strlen("QYoCiMonkey")),
			HTTP_String_create2("QYoCiMonkey",strlen("QYoCiMonkey")));
			*/
	HTTP_Param_node *args = HTTP_Request_get_params(request);
	/*
	while(args != NULL)
	{
		write(STDOUT_FILENO,"key:\t",5);
		write(STDOUT_FILENO,args->key->content,HTTP_String_capacity(args->key));
		write(STDOUT_FILENO,"\n",1);
		write(STDOUT_FILENO,"value:\t",7);
		write(STDOUT_FILENO,args->value->content,HTTP_String_capacity(args->value));
		write(STDOUT_FILENO,"\n",1);
		args = args->next;
	}
	*/
	HTTP_String *name = HTTP_Param_node_value3(args,"name",4);
	HTTP_String *password = HTTP_Param_node_value3(args,"psw",3);
	write(STDOUT_FILENO,name->content,HTTP_String_capacity(name));
	write(STDOUT_FILENO,"\n",1);
	write(STDOUT_FILENO,password->content,HTTP_String_capacity(password));
	write(STDOUT_FILENO,"\n",1);
	error404_handler(request,response);
	fprintf(stdout,"verify_signin_handler\n");
	return 0;
}
