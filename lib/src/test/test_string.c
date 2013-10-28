#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "http_string.h"

int main()
{
	HTTP_string *str = HTTP_create_string(10);

	fprintf(stdout,"size:\t%d\n",HTTP_size(str));
	fprintf(stdout,"capacity:\t%d\n",HTTP_capacity(str));

	char sendmsg[100] = "Nice to meet you!";
	char recvmsg[sizeof(sendmsg)] = {0};
	fprintf(stdout,"writeline:\t%d\n",
		HTTP_writeline(str,sendmsg,strlen(sendmsg)));

	fprintf(stdout,"writeline:\t%d\n",
		HTTP_writeline(str,sendmsg,strlen(sendmsg)));

	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);

	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);

	fprintf(stdout,"HTTP_seek:\t%d\n",HTTP_seek(str,HTTP_STRING_BEGIN,0));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);

	fprintf(stdout,"HTTP_seek:\t%d\n",HTTP_seek(str,HTTP_STRING_BEGIN,0));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"HTTP_read:\t%d\t%s\n",HTTP_read(str,recvmsg),recvmsg);

	HTTP_destroy_string(str);

	str = HTTP_create_string2(sendmsg,strlen(sendmsg));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"HTTP_write:\t%d\n",HTTP_write(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_write:\t%d\n",HTTP_write(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_read:\t%d\t%s\n",HTTP_read(str,recvmsg),recvmsg);

	HTTP_destroy_string(str);

	str = HTTP_create_string2(sendmsg,strlen(sendmsg));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_strcmp(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_strcmp(str,"Hello",6));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_strcmp(str,"QMonkey",8));
	HTTP_destroy_string(str);
	return 0;
}
