#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"

HTTP_socket* HTTP_create_socket(int sfd)
{
	HTTP_socket *http_socket = (HTTP_socket*)malloc(sizeof(HTTP_socket));
	http_socket->sfd = sfd;
	http_socket->buffer = HTTP_create_string(DEFAULT_BUFFER_LENGTH);
	return http_socket;
}

int HTTP_set_header(HTTP_socket *http_socket,char *header)
{
	if(http_socket == NULL || header == NULL)
	{
		return -1;
	}
	int32_t length = strlen(header);
	HTTP_writeline(http_socket->buffer,header,length);
	return 0;
}

int32_t HTTP_get_header(HTTP_socket *http_socket,char *key,char *content)
{
	HTTP_seek(http_socket->buffer,HTTP_STRING_BEGIN,0);
	int32_t rd = 0;
	int32_t hsize = 0;
	while(rd = HTTP_readline(http_socket->buffer,content))
	{
		int32_t size = strlen(key);
		if(!memcmp(key,content,size))
		{
			char *scanner = content + size;
			while(*scanner == ' ')
			{
				++scanner;
			}
			if(*scanner == ':')
			{
				scanner += 2;
				hsize = rd - (scanner - content);
				memmove(content,scanner,hsize);
				break;
			}
		}
	}
	return hsize;
}

int HTTP_set_content(HTTP_socket *http_socket,char *content)
{
	int32_t length = strlen(content);
	HTTP_writeline(http_socket->buffer,"",0);
	HTTP_write(http_socket->buffer,content,length);
	return 0;
}

int32_t HTTP_get_content(HTTP_socket *http_socket,char *content)
{
	HTTP_seek(http_socket->buffer,HTTP_STRING_BEGIN,0);
	while(HTTP_readline(http_socket->buffer,content));
	return HTTP_read(http_socket->buffer,content);
}

int HTTP_destroy_socket(HTTP_socket *http_socket)
{
	if(http_socket == NULL)
	{
		return -1;
	}
	close(http_socket->sfd);
	HTTP_destroy_string(http_socket->buffer);
	free(http_socket);
	return 0;
}
