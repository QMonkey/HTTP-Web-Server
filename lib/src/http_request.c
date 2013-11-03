#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_param_linkedlist.h"

char *HTTP_Request_method[] = {"GET","POST"};

int HTTP_Request_init(HTTP_Socket *request)
{
	if(request == NULL)
	{
		return -1;
	}

	char buffer[DEFAULT_BUFFER_LENGTH] = {0};
	int rd = 0;
	while((rd = recv(request->sfd,buffer,DEFAULT_BUFFER_LENGTH,MSG_DONTWAIT)) > 0)
	{
		HTTP_String_write(request->buffer,buffer,rd);
	}
	return 0;
}

int HTTP_Request_get_method(HTTP_Socket *request)
{
	char buff[DEFAULT_BUFFER_LENGTH] = {0};
	HTTP_String_seek(request->buffer,HTTP_STRING_BEGIN,0);
	int32_t size = HTTP_String_readline(request->buffer,buff);
	char *end = buff + size;
	char *scanner = buff;
	while(scanner != end && *scanner != ' ')
	{
		++scanner;
	}
	int msize = scanner - buff;
	int res = -1;
	int i = 0;
	while(i < 2)
	{
		int32_t rmsize = strlen(*HTTP_Request_method);
		if(msize != rmsize)
		{
			continue;
		}
		else
		{
			res = strncmp(*HTTP_Request_method,buff,msize);
		}
		if(res == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

int32_t HTTP_Request_get_url(HTTP_Socket *request,char *url)
{
	HTTP_String_seek(request->buffer,HTTP_STRING_BEGIN,0);
	int32_t rd = HTTP_String_readline(request->buffer,url);
	char *scanner = url;
	char *end = scanner + rd;
	while(scanner != end && *scanner != '/')
	{
		++scanner;
	}
	char *begin = scanner;
	while(scanner != end && *scanner != ' ' && *scanner != '?')
	{
		++scanner;
	}
	int32_t size = scanner - begin;
	memmove(url,begin,size);
	return size;
}

HTTP_Param_node* HTTP_Request_get_params(HTTP_Socket *request)
{
	char *begin = NULL;
	char buffer[DEFAULT_BUFFER_LENGTH];
	switch(HTTP_Request_get_method(request))
	{
	case 0:
		begin = request->buffer->begin;
		while(*begin++ != 0);
		break;
	case 1:
		HTTP_String_seek(request->buffer,HTTP_STRING_BEGIN,0);
		while(HTTP_String_readline(request->buffer,buffer));
		begin = request->buffer->current;
		break;
	default:
		break;
	}
	char *scanner = begin;
	HTTP_Param_node *head = NULL;

	HTTP_String *key = NULL;
	HTTP_String *value = NULL;
	while(*begin != ' ')
	{
		while(*scanner != '=' && *scanner != '&' && *scanner != ' ')
		{
			++scanner;
		}
		switch(*scanner)
		{
		case '=':
			key = HTTP_String_create2(begin,scanner-begin);
			break;
		case '&':
			value = HTTP_String_create2(begin,scanner-begin);
			HTTP_Param_insert(&head,key,value);
			HTTP_String_destroy(key);
			HTTP_String_destroy(value);
			break;
		default:
			break;
		}
		begin = scanner++;
	}
	return head;
}

int32_t HTTP_Request_get_header(HTTP_Socket *request,char *key,char *content)
{
	return HTTP_Socket_get_header(request,key,content);
}

int32_t HTTP_Request_get_content(HTTP_Socket *request,char *content)
{
	return HTTP_Socket_get_content(request,content);
}
