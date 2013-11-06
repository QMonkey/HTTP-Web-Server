#include <unistd.h>
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

#include "http_engine.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"

static int do_get(HTTP_Socket *request,HTTP_Socket *response);
static int do_post(HTTP_Socket *request,HTTP_Socket *response);
static int relogin(HTTP_Socket *response);

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
	HTTP_Param_node *args = HTTP_Request_get_params(request);
	HTTP_String *name = HTTP_Param_node_value3(args,"name",4);
	HTTP_String *password = HTTP_Param_node_value3(args,"psw",3);

	int32_t nsize = HTTP_String_capacity(name);
	int32_t psize = HTTP_String_capacity(password);

	if(nsize == 0 || psize == 0)
	{
		relogin(response);
		return 0;
	}
	MYSQL *conn = mysql_init(NULL);
	if(conn == NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		relogin(response);
		return 0;
	}
	
	if(mysql_real_connect(conn,"localhost","root","root","testdb",0,NULL,0) == NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		relogin(response);
		mysql_close(conn);
		return 0;
	}

	HTTP_String *sql = HTTP_String_create2("SELECT * FROM account WHERE name='",34);
	HTTP_String_write(sql,name->content,nsize);
	HTTP_String_write(sql,"' AND password='",16);
	HTTP_String_write(sql,password->content,psize);
	HTTP_String_write(sql,"'\0",2);

	if(mysql_query(conn,sql->content))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		relogin(response);
		mysql_close(conn);
		return 0;
	}

	MYSQL_RES *result = mysql_store_result(conn);
	if(result == NULL)
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		relogin(response);
		mysql_close(conn);
		return 0;
	}

	MYSQL_ROW row;
	if(!(row = mysql_fetch_row(result)))
	{
		relogin(response);
		mysql_free_result(result);
		mysql_close(conn);
		return 0;
	}

	HTTP_Param_destroy(args);
	mysql_free_result(result);
	mysql_close(conn);

	HTTP_Response_set_header(response,"HTTP/1.1 302");
	HTTP_Response_set_header(response,"Location: http://localhost:9999/html/");
	HTTP_Response_flush(response);

	fprintf(stdout,"verify_signin_handler\n");
	return 0;
}

static int relogin(HTTP_Socket *response)
{
	HTTP_Response_set_header(response,"HTTP/1.1 302");
	HTTP_Response_set_header(response,"Location: http://localhost:9999/html/signIn.html");
	HTTP_Response_flush(response);
	return 0;
}
