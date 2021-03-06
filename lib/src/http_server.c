#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <signal.h>
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

/*
static void signal_proc(int signo)
{
	pid_t pid;
	int status;
	if(signo == SIGCHLD)
	{
		while((pid = waitpid(-1,&status,WNOHANG)) > 0);
	}
	return;
}
*/

static void* dispatcher(void *arg)
{
	int cfd = (int)arg;
	HTTP_Socket *request = HTTP_Socket_create(cfd);
	HTTP_Socket *response = HTTP_Socket_create(cfd);

	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(cfd,&rfds);

	int flag = 1;
	while(flag)
	{
		char url[BUFFER_LENGTH] = {0};
		int32_t size = 0;
		switch(select(cfd+1,&rfds,NULL,NULL,NULL))
		{
			case -1:
				perror("select");
				break;
			case 0:
				break;
			default:
				if(FD_ISSET(cfd,&rfds))
				{
					HTTP_Request_init(request);
					size = HTTP_Request_get_url(request,url);
					url[size] = 0;
					HTTP_Router_route(url)(request,response);
					flag = 0;
				}
				break;
		}
	}

	FD_ZERO(&rfds);
	HTTP_Socket_destroy(request,SHUT_RD);
	HTTP_Socket_destroy(response,SHUT_WR);
	return NULL;
}

/*
static void handle(int sfd)
{
	HTTP_Socket *request = HTTP_create_socket(sfd);
	HTTP_Socket *response = HTTP_create_socket(sfd);

	HTTP_request_init(request);
	char url[BUFFER_LENGTH] = {0};
	int32_t size = HTTP_request_get_url(request,url);
	fprintf(stdout,"%s\n",url);
	url[size] = 0;
	HTTP_route(url)(request,response);

	HTTP_destroy_socket(request,SHUT_RD);
	HTTP_destroy_socket(response,SHUT_WR);
}
*/

int HTTP_Server_serve()
{
/*
	struct sigaction action;
	action.sa_handler = signal_proc;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	action.sa_flags |= SA_INTERRUPT;
	action.sa_flags |= SA_RESTART;
	if(sigaction(SIGCHLD,&action,NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
*/
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
	HTTP_Router_init();
	while(1)
	{
		struct sockaddr addr;
		socklen_t addrlen;
		int clientsfd = accept(serversfd,&addr,&addrlen);
		if(clientsfd == -1)
		{
			continue;
		}
		pthread_create(malloc(sizeof(pthread_t)),NULL,dispatcher,(void*)clientsfd);
/*
		if(!fork())
		{
			handle(clientsfd);
		}
		else
		{
			shutdown(clientsfd,SHUT_RDWR);
		}
*/
	}
	close(serversfd);
	HTTP_Router_destroy();
	return 0;
}
