#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		char errmsg[] = "No enough parameters.";
		write(STDERR_FILENO,errmsg,sizeof(errmsg));
		exit(1);
	}
	if(access(argv[1],F_OK) != -1)
	{
		char msg[] = "File exists.";
		write(STDOUT_FILENO,msg,sizeof(msg));
	}
	else
	{
		perror("access");
	}
	return 0;
}
