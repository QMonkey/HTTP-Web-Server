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

#define MAX_SOCKET 1024

static void* proc(void *args)
{
	int sfd = *(int*)args;
	char buffer[4096];
	int rd;
	if((rd = read(sfd,buffer,4096)) == -1)
	{
		perror("read");
	}
	write(STDOUT_FILENO,buffer,rd);
	write(STDOUT_FILENO,"\n",1);
	if(write(sfd,buffer,rd) == -1)
	{
		perror("write");
	}
	close(sfd);
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
	while(1)
	{
		struct sockaddr addr;
		socklen_t addrlen;
		int clientsfd = accept(serversfd,&addr,&addrlen);
		if(clientsfd == -1)
		{
			continue;
		}
		pthread_create(malloc(sizeof(pthread_t)),NULL,proc,&clientsfd);
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
