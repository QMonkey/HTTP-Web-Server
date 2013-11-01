#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "http_string.h"

static int HTTP_String_resize(HTTP_String *str,int32_t size);

HTTP_String* HTTP_String_create(int32_t size)
{
	HTTP_String *str = (HTTP_String*)malloc(sizeof(HTTP_String));

	str->content = (char*)malloc(sizeof(char) * size);

	str->current = str->capacity_end = str->begin = str->content;
	str->end = str->begin + size;

	return str;
}

HTTP_String* HTTP_String_create2(char *str,int32_t size)
{
	HTTP_String *http_string = HTTP_String_create(size);
	HTTP_String_write(http_string,str,size);
	return http_string;
}

HTTP_String* HTTP_String_copy(HTTP_String *str)
{
	int32_t capacity = HTTP_String_capacity(str);
	HTTP_String *strbak = HTTP_String_create2(str->content,capacity);
	strbak->capacity_end = strbak->begin + capacity;
	memcpy(strbak->content,str->content,capacity);
	return strbak;
}

HTTP_String* HTTP_String_adjust_to(HTTP_String *src,HTTP_String *dest)
{
	if(src == NULL || dest == NULL)
	{
		return NULL;
	}

	HTTP_String_resize(src,HTTP_String_size(dest));
	int32_t capacity = HTTP_String_capacity(dest);
	src->capacity_end = src->content + capacity;
	memcpy(src->content,dest->content,capacity);
	return src;
}

int32_t HTTP_String_offset(HTTP_String *str)
{
	return str->current - str->begin;
}

int32_t HTTP_String_size(HTTP_String *str)
{
	return str->end - str->begin;
}

int32_t HTTP_String_capacity(HTTP_String *str)
{
	return str->capacity_end - str->begin;
}

int32_t HTTP_String_seek(HTTP_String *str,int32_t flag,int32_t offset)
{
	switch(flag)
	{
	case HTTP_STRING_BEGIN:
		break;
	case HTTP_STRING_CURRENT:
		offset += str->current - str->begin;
		break;
	case HTTP_STRING_END:
		offset += HTTP_String_capacity(str);
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

static int HTTP_String_resize(HTTP_String *str,int32_t size)
{
	if(str == NULL)
	{
		return -1;
	}
	if(size < HTTP_String_size(str))
	{
		return 0;
	}

	char *new_str = (char*)malloc(sizeof(char) * size);
	int32_t capacity = HTTP_String_capacity(str);
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

int HTTP_String_strcmp(HTTP_String *str,char *cstr,int32_t size)
{
	int32_t ssize = HTTP_String_size(str);
	int res = memcmp(str->content,cstr,size < ssize ? size : ssize);
	res = (!res && ssize != size ? 
		(ssize > size ? str->content[size] : cstr[ssize]) : res);
	return res;
}

int HTTP_String_strcmp2(HTTP_String *first,HTTP_String *second)
{
	return HTTP_String_strcmp(first,second->content,HTTP_String_capacity(second));
}

int HTTP_String_replace(HTTP_String *str,HTTP_String *src,HTTP_String *dest)
{
}

int32_t HTTP_String_readline(HTTP_String *str,char *dest)
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

int32_t HTTP_String_read(HTTP_String *str,char *dest)
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

int32_t HTTP_String_insert(HTTP_String *dest,char *src,int32_t size)
{
	if(dest == NULL || src == NULL)
	{
		return -1;
	}

	while(dest->capacity_end + size > dest->end)
	{
		HTTP_String_resize(dest,HTTP_String_size(dest)<<1);
	}
	memmove(dest->begin+size,dest->begin,HTTP_String_capacity(dest));
	memcpy(dest->begin,src,size);
	return size;
}

int32_t HTTP_String_writeline(HTTP_String *str,char *src,int32_t size)
{
	if(str == NULL || src == NULL || size < 0)
	{
		return -1;
	}
	HTTP_String_write(str,src,size);
	*str->capacity_end++ = '\r';
	*str->capacity_end++ = '\n';

	return size;
}

int32_t HTTP_String_write(HTTP_String *str,char *src,int32_t size)
{	
	if(str == NULL || src == NULL || size < 0)
	{
		return -1;
	}

	while(str->capacity_end + size > str->end)
	{
		HTTP_String_resize(str,HTTP_String_size(str)<<1);
	}

	memcpy(str->capacity_end,src,sizeof(char) * size);
	str->capacity_end += size;

	return size;
}

int HTTP_String_destroy(HTTP_String *str)
{
	if(str == NULL)
	{
		return -1;
	}
	free(str->content);
	free(str);
	return 0;
}
