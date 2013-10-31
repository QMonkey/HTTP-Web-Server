#include <stdlib.h>
#include <regex.h>

#include "http_engine.h"
#include "http_file.h"
#include "http_string.h"
#include "http_socket.h"
#include "http_response.h"
#include "http_param_linkedlist.h"

static int HTTP_match_param(HTTP_string *buffer,HTTP_param_node *args,
		HTTP_replacer_node **replacer)
{
	regex_t reg;
	while(args != NULL)
	{
	}
}

int render(HTTP_socket *response,char *path,HTTP_param_node *args)
{
	if(response == NULL || path == NULL)
	{
		return -1;
	}

	HTTP_string *buffer = HTTP_create_string(FILE_BUFFER_LENGTH);
	HTTP_file_read_all(buffer,path);
	HTTP_replacer_node *replacer = NULL;
	HTTP_match_param(buffer,args,&replacer);

	while(args != NULL)
	{
		HTTP_response_set_param(response,args->key,args->value);
		HTTP_param_pop(&args);
	}

	HTTP_response_flush(response);
	return 0;
}
