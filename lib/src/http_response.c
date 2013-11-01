#include <sys/socket.h>
#include <unistd.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_response.h"

int HTTP_Response_flush(HTTP_Socket *response)
{
	if(response == NULL)
	{
		return -1;
	}

	send(response->sfd,response->buffer->content,HTTP_String_capacity(response->buffer),MSG_DONTWAIT);
	return 0;
}

int HTTP_Response_set_param(HTTP_Socket *response,HTTP_String *key,HTTP_String *value)
{
}

int HTTP_Response_set_header(HTTP_Socket *response,char *header)
{
	return HTTP_Socket_set_header(response,header);
}

int HTTP_Response_set_content(HTTP_Socket *response,char *content)
{
	return HTTP_Socket_set_content(response,content);
}
