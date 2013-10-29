#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_request.h"

int HTTP_request_init(HTTP_socket *request)
{
	if(request == NULL)
	{
		return -1;
	}

	char buffer[DEFAULT_BUFFER_LENGTH] = {0};
	int rd = 0;
	while((rd = recv(request->sfd,buffer,DEFAULT_BUFFER_LENGTH,0)) > 0)
	{
		HTTP_write(request->buffer,buffer,rd);
	}
	return 0;
}

int32_t HTTP_request_get_url(HTTP_socket *request,char *url)
{
	HTTP_seek(request->buffer,HTTP_STRING_BEGIN,0);
	int32_t rd = HTTP_readline(request->buffer,url);
	char *scanner = url;
	char *end = scanner + rd;
	while(scanner != end && *scanner != '/')
	{
		++scanner;
	}
	char *begin = scanner;
	while(scanner != end && *scanner != ' ')
	{
		++scanner;
	}
	int32_t size = scanner - begin;
	memmove(url,begin,size);
	return size;
}

int32_t HTTP_request_get_header(HTTP_socket *request,char *key,char *content)
{
	return HTTP_get_header(request,key,content);
}

int32_t HTTP_request_get_content(HTTP_socket *request,char *content)
{
	return HTTP_get_content(request,content);
}
