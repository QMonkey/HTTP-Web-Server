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

	if(listen(sfd,50) == -1)
	{
		perror("listen");
		exit(1);
	}

	char content[1024] = {0};
	int32_t rd = 0;
	while(1)
	{
		int cfd = accept(sfd,NULL,NULL);
		if(cfd == -1)
		{
			perror("accept");
			continue;
		}

		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(cfd,&rfds);
		switch(select(cfd+1,&rfds,NULL,NULL,NULL))
		{
			case -1:
				perror("select");
				exit(1);
				break;
			case 0:
				continue;
				break;
			default:
				if(FD_ISSET(cfd,&rfds))
				{
					rd = recv(cfd,content,1024,MSG_DONTWAIT);
					write(STDOUT_FILENO,content,rd);
					send(cfd,content,rd,MSG_DONTWAIT);
				}
				close(cfd);
				FD_ZERO(&rfds);
				break;
		}
	}

	close(sfd);
	return 0;
}
