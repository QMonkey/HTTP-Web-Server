#include "http_engine.h"
#include "http_socket.h"
#include "http_response.h"

int render(HTTP_socket *response,char *path,HTTP_list_node *args)
{
	if(response == NULL || path == NULL)
	{
		return -1;
	}

	HTTP_set_content(response,"");
	HTTP_file_read_all(response->buffer,path);

	while(args != NULL)
	{
	}

	HTTP_response_flush(response);
	return 0;
}
