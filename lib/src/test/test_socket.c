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

#include "http_socket.h"
#include "http_request.h"

void* proc(void *arg)
{
	HTTP_socket *http_socket = (HTTP_socket*)arg;
	char content[1000] = {0};
	HTTP_request_init(http_socket);
	HTTP_read(http_socket->buffer,content);
	write(STDOUT_FILENO,content,1000);
	int32_t size = HTTP_get_header(http_socket,"Accept",content);
	write(STDOUT_FILENO,content,size);
	fprintf(stdout,"\n");
	HTTP_destroy_socket(http_socket);
	return NULL;
}

int main()
{
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	if(sfd == -1)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);
	inet_aton("0.0.0.0",&addr.sin_addr);
	
	if(bind(sfd,(struct sockaddr*)&addr,sizeof(addr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if(listen(sfd,100) == -1)
	{
		perror("listen");
		exit(1);
	}
	char buffer[1000] = {0};

	while(1)
	{
		int cfd = accept(sfd,NULL,NULL);
		if(cfd == -1)
		{
			perror("accept");
			continue;
		}
		HTTP_socket *http_socket = HTTP_create_socket(cfd);
		pthread_create(malloc(sizeof(pthread_t)),NULL,proc,http_socket);
	}
	close(sfd);
	return 0;
}
