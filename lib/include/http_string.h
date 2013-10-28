#ifndef HTTP_STRING_H
#define HTTP_STRING_H

#include <stdint.h>

typedef struct
{
	char *begin;
	char *current;
	char *capacity_end;
	char *end;
	char *content;
} HTTP_string;

#define HTTP_STRING_BEGIN 0
#define HTTP_STRING_CURRENT 1
#define HTTP_STRING_END 2

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_string* HTTP_create_string(int32_t size);
extern HTTP_string* HTTP_create_string2(char *str,int32_t size);
extern int32_t HTTP_size(HTTP_string *str);
extern int32_t HTTP_capacity(HTTP_string *str);
extern int HTTP_seek(HTTP_string *str,int32_t flag,int32_t offset);
extern int HTTP_strcmp(HTTP_string *str,char *cstr,int32_t size);
extern int32_t HTTP_readline(HTTP_string *str,char *dest);
extern int32_t HTTP_read(HTTP_string *str,char *dest);
extern int32_t HTTP_writeline(HTTP_string *str,char *src,int32_t size);
extern int32_t HTTP_write(HTTP_string *str,char *src,int32_t size);
extern int HTTP_destroy_string(HTTP_string *str);

#ifdef __cplusplus
}
#endif

#endif
