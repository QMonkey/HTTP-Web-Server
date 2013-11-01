#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
	if(argc < 2)
	{
		char errmsg[] = "No enough parameter.\n";
		write(STDERR_FILENO,errmsg,sizeof(errmsg));
		exit(1);
	}
	struct stat st;
	if(!stat(argv[1],&st))
	{
		if(S_ISREG(st.st_mode))
		{
			fprintf(stdout,"Regular\n");
		}
		if(S_ISDIR(st.st_mode))
		{
			fprintf(stdout,"Directory\n");
		}
		if(S_ISCHR(st.st_mode))
		{
			fprintf(stdout,"Character\n");
		}
		if(S_ISBLK(st.st_mode))
		{
			fprintf(stdout,"Block\n");
		}
		if(S_ISFIFO(st.st_mode))
		{
			fprintf(stdout,"FIFO\n");
		}
		if(S_ISLNK(st.st_mode))
		{
			fprintf(stdout,"Link\n");
		}
		if(S_ISSOCK(st.st_mode))
		{
			fprintf(stdout,"Socket\n");
		}
	}
	else
	{
		perror("stat");
		exit(1);
	}
	return 0;
}
