#include <stdlib.h>
#include <regex.h>

#include "http_engine.h"
#include "http_file.h"
#include "http_string.h"
#include "http_socket.h"
#include "http_response.h"
#include "http_param_linkedlist.h"
#include "http_replacer_linkedlist.h"

static int HTTP_Engine_match_param(HTTP_String *buffer,HTTP_param_node *args,
		HTTP_replacer_node **replacer)
{
	/*
	regex_t reg;
	HTTP_write(buffer,"\0",1);
	while(args != NULL)
	{
		HTTP_insert(args->key,"${\s*",5);
		HTTP_write(args->key,"\s*}\0",5);
		HTTP_write(args->value,"\0",1);
		if(!regcomp(&reg,args->key->content,0))
		{
			fprintf(stderr,"regcomp\n");
			return -1;
		}
		int nmatch = reg.re_nsub + 1;
		regmatch_t *pm = (regmatch_t*)malloc(sizeof(regmatch_t) * nmatch);
		if(!regexec(&reg,buffer,nmatch,pm,0))
		{
			fprintf(stderr,"regexec\n");
			return -1;
		}
	}
	*/
}

int HTTP_Engine_render(HTTP_Socket *response,char *path,HTTP_param_node *args)
{
	if(response == NULL || path == NULL || HTTP_File_read_all(response->buffer,path) == -1)
	{
		return -1;
	}
/*
	HTTP_String *buffer = HTTP_create_string(FILE_BUFFER_LENGTH);
	HTTP_file_read_all(buffer,path);
	HTTP_replacer_node *replacer = NULL;
	HTTP_match_param(buffer,args,&replacer);

	while(args != NULL)
	{
		HTTP_response_set_param(response,args->key,args->value);
		HTTP_param_pop(&args);
	}
*/
	HTTP_Response_flush(response);
	return 0;
}
