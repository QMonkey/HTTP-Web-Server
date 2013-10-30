#include <sys/socket.h>
#include <unistd.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_response.h"

int HTTP_response_flush(HTTP_socket *response)
{
	if(response == NULL)
	{
		return -1;
	}

	send(response->sfd,response->buffer->content,HTTP_capacity(response->buffer),MSG_DONTWAIT);
	return 0;
}

int HTTP_response_set_header(HTTP_socket *response,char *header)
{
	return HTTP_set_header(response,header);
}

int HTTP_response_set_content(HTTP_socket *response,char *content)
{
	return HTTP_set_content(response,content);
}
