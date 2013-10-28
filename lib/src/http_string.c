#include <stdlib.h>
#include <string.h>

#include "http_string.h"

HTTP_string* HTTP_create_string(int32_t size)
{
	HTTP_string *str = (HTTP_string*)malloc(sizeof(HTTP_string));

	str->content = (char*)malloc(sizeof(char) * size);

	str->current = str->capacity_end = str->begin = str->content;
	str->end = str->begin + size;

	return str;
}

HTTP_string* HTTP_create_string2(char *str,int32_t size)
{
	HTTP_string *http_string = HTTP_create_string(size);
	HTTP_write(http_string,str,size);
	return http_string;
}

int32_t HTTP_size(HTTP_string *str)
{
	return str->end - str->begin;
}

int32_t HTTP_capacity(HTTP_string *str)
{
	return str->capacity_end - str->begin;
}

int32_t HTTP_seek(HTTP_string *str,int32_t flag,int32_t offset)
{
	switch(flag)
	{
	case HTTP_STRING_BEGIN:
		break;
	case HTTP_STRING_CURRENT:
		offset += str->current - str->begin;
		break;
	case HTTP_STRING_END:
		offset += HTTP_capacity(str);
		break;
	default:
		break;
	}
	char *tmpptr = str->current;
	str->current = str->begin + offset;
	if(str->current < str->begin || str->current > str->capacity_end)
	{
		str->current = tmpptr;
		return -1;
	}
	return 0;
}

static int HTTP_resize(HTTP_string *str,int32_t size)
{
	if(str == NULL)
	{
		return -1;
	}

	char *new_str = (char*)malloc(sizeof(char) * size);
	int32_t capacity = HTTP_capacity(str);
	memcpy(new_str,str->content,capacity * sizeof(char));

	int32_t offset = str->current - str->begin;
	free(str->content);
	str->content = new_str;

	str->current = str->content + offset;
	str->capacity_end = str->content + capacity;
	str->begin = str->content;
	str->end = str->begin + size;
	return 0;
}

int HTTP_strcmp(HTTP_string *str,char *cstr,int32_t size)
{
	int32_t ssize = HTTP_size(str);
	int res = memcmp(str->content,cstr,size < ssize ? size : ssize);
	res = (!res && ssize != size ? 
		(ssize > size ? str->content[size] : cstr[ssize]) : res);
/*
	if(!res && ssize != size)
	{
		res = ssize > size ? str->content[size] : cstr[ssize];
	}
*/
	return res;
}

int32_t HTTP_readline(HTTP_string *str,char *dest)
{
	if(str == NULL || dest == NULL)
	{
		return -1;
	}

	int32_t size = 0;
	while(str->current != str->capacity_end)
	{
		char c = *str->current++;
		if(c != '\r' || c == '\r' && *str->current != '\n')
		{
			*dest++ = c;
			++size;
		}
		else
		{
			++str->current;
			break;
		}
	}
	return size;
}

int32_t HTTP_read(HTTP_string *str,char *dest)
{
	if(str == NULL || dest == NULL)
	{
		return -1;
	}

	int32_t size = str->capacity_end - str->current;
	memcpy(dest,str->current,size);
	str->current = str->capacity_end;

	return size;
}

int32_t HTTP_writeline(HTTP_string *str,char *src,int32_t size)
{
	if(str == NULL || src == NULL || size < 0)
	{
		return -1;
	}
	HTTP_write(str,src,size);
	*str->capacity_end++ = '\r';
	*str->capacity_end++ = '\n';

	return size;
}

int32_t HTTP_write(HTTP_string *str,char *src,int32_t size)
{	
	if(str == NULL || src == NULL || size < 0)
	{
		return -1;
	}

	if(str->capacity_end + size > str->end)
	{
		HTTP_resize(str,HTTP_size(str)<<1);
	}

	memcpy(str->capacity_end,src,sizeof(char) * size);
	str->capacity_end += size;

	return size;
}

int HTTP_destroy_string(HTTP_string *str)
{
	if(str == NULL)
	{
		return -1;
	}
	free(str->content);
	free(str);
	return 0;
}
