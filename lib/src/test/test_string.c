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
	fprintf(stdout,"writeline:\t%d\n",
		HTTP_writeline(str,sendmsg,strlen(sendmsg)));

//	memcpy(sendmsg,"My name is QMonkey!\r\n",22);
	fprintf(stdout,"writeline:\t%d\n",
		HTTP_writeline(str,sendmsg,strlen(sendmsg)));

	char recvmsg[sizeof(sendmsg)] = {0};
	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);

	memset(recvmsg,0,sizeof(recvmsg));

	fprintf(stdout,"readline:\t%d\t%s\n",HTTP_readline(str,recvmsg),recvmsg);

	HTTP_destroy_string(str);
	return 0;
}
