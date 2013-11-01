#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

#include "http_file.h"

int HTTP_file_exists(char *path)
{
	return access(path,F_OK) != -1;
}

int32_t HTTP_file_read_all(HTTP_string *buffer,char *path)
{
	if(buffer == NULL || !HTTP_file_exists(path))
	{
		return -1;
	}

	int32_t sum = 0;
	char buf[FILE_BUFFER_LENGTH];
	int fd = open(path,O_RDONLY);
	int rd = 0;
	while((rd = read(fd,buf,FILE_BUFFER_LENGTH)) > 0)
	{
		HTTP_write(buffer,buf,rd);
		sum += rd;
	}
	return sum;
}
