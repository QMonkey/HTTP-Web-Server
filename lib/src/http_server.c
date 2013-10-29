#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "http_server.h"
#include "http_socket.h"
#include "http_request.h"
#include "http_response.h"
#include "http_router.h"

#define MAX_SOCKET 1024
#define BUFFER_LENGTH 4096

static void* proc(void *arg)
{
	HTTP_socket **http_sockets = (HTTP_socket**)arg;
	HTTP_socket *request = http_sockets[0];
	HTTP_socket *response = http_sockets[1];

	HTTP_request_init(request);
	char url[BUFFER_LENGTH] = {0};
	int32_t size = HTTP_request_get_url(request,url);
	url[size] = 0;
	HTTP_route(url)(request,response);

	HTTP_destroy_socket(request);
	HTTP_destroy_socket(response);
	free(http_sockets);
	return NULL;
}

int HTTP_serve()
{
	int serversfd = socket(AF_INET,SOCK_STREAM,0);
	if(serversfd == -1)
	{
		perror("socket");
		exit(1);
	}

	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("0.0.0.0",&addr.sin_addr);

	if(bind(serversfd,(struct sockaddr*)&addr,sizeof(addr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(serversfd,MAX_SOCKET) == -1)
	{
		perror("listen");
		exit(1);
	}
	HTTP_init_router();
	while(1)
	{
		struct sockaddr addr;
		socklen_t addrlen;
		int clientsfd = accept(serversfd,&addr,&addrlen);
		if(clientsfd == -1)
		{
			continue;
		}
		HTTP_socket **http_sockets = (HTTP_socket**)malloc(sizeof(HTTP_socket*) * 2);
		http_sockets[0] = HTTP_create_socket(clientsfd);
		http_sockets[1] = HTTP_create_socket(clientsfd);
		pthread_create(malloc(sizeof(pthread_t)),NULL,proc,http_sockets);
/*
		if(!fork())
		{
			char msg[] = "<h1>Hello! Nice to meet you!</h1>";
			if(write(clientsfd,msg,sizeof(msg)) == -1)
			{
				perror("write");
			}
			fprintf(stdout,"A connection comming.\n");
		}
		close(clientsfd);
*/
	}
	close(serversfd);
	return 0;
}
