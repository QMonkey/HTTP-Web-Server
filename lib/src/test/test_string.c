#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "http_string.h"

int main()
{
	HTTP_String *str = HTTP_String_create(10);

	fprintf(stdout,"size:\t%d\n",HTTP_String_size(str));
	fprintf(stdout,"capacity:\t%d\n",HTTP_String_capacity(str));

	char sendmsg[100] = "Nice to meet you!";
	char recvmsg[sizeof(sendmsg)] = {0};
	fprintf(stdout,"writeline:\t%d\n",
		HTTP_String_writeline(str,sendmsg,strlen(sendmsg)));

	fprintf(stdout,"writeline:\t%d\n",
		HTTP_String_writeline(str,sendmsg,strlen(sendmsg)));

	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_String_readline(str,recvmsg),recvmsg);

	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_String_readline(str,recvmsg),recvmsg);

	fprintf(stdout,"HTTP_seek:\t%d\n",HTTP_String_seek(str,HTTP_STRING_BEGIN,0));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_String_readline(str,recvmsg),recvmsg);
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_String_readline(str,recvmsg),recvmsg);

	fprintf(stdout,"HTTP_seek:\t%d\n",HTTP_String_seek(str,HTTP_STRING_BEGIN,0));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"HTTP_read:\t%d\t%s\n",HTTP_String_read(str,recvmsg),recvmsg);

	HTTP_String_destroy(str);

	str = HTTP_String_create2(sendmsg,strlen(sendmsg));
	memset(recvmsg,0,sizeof(recvmsg));
	fprintf(stdout,"HTTP_write:\t%d\n",HTTP_String_write(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_write:\t%d\n",HTTP_String_write(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_read:\t%d\t%s\n",HTTP_String_read(str,recvmsg),recvmsg);

	HTTP_String_destroy(str);

	str = HTTP_String_create2(sendmsg,strlen(sendmsg));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_String_strcmp(str,sendmsg,strlen(sendmsg)));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_String_strcmp(str,"Hello",6));
	fprintf(stdout,"HTTP_strcmp:\t%d\n",HTTP_String_strcmp(str,"QMonkey",8));
	HTTP_String_destroy(str);
	return 0;
}
