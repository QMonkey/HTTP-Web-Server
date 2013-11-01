#ifndef HTTP_STRING_H
#define HTTP_STRING_H

#include <stdint.h>

#define HTTP_STRING_BEGIN 0
#define HTTP_STRING_CURRENT 1
#define HTTP_STRING_END 2

typedef struct
{
	char *begin;
	char *current;
	char *capacity_end;
	char *end;
	char *content;
} HTTP_String;

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_String* HTTP_String_create(int32_t size);
extern HTTP_String* HTTP_String_create2(char *str,int32_t size);
extern HTTP_String* HTTP_String_copy(HTTP_String *str);
extern HTTP_String* HTTP_String_adjust_to(HTTP_String *src,HTTP_String *dest);
extern int32_t HTTP_String_size(HTTP_String *str);
extern int32_t HTTP_String_capacity(HTTP_String *str);
extern int HTTP_String_offset(HTTP_String *str);
extern int HTTP_String_seek(HTTP_String *str,int32_t flag,int32_t offset);
extern int HTTP_String_strcmp(HTTP_String *str,char *cstr,int32_t size);
extern int HTTP_String_strcmp2(HTTP_String *first,HTTP_String *second);
extern int HTTP_String_replace(HTTP_String *str,HTTP_String *src,HTTP_String *dest);
extern int32_t HTTP_String_readline(HTTP_String *str,char *dest);
extern int32_t HTTP_String_read(HTTP_String *str,char *dest);
extern int32_t HTTP_String_insert(HTTP_String *dest,char *src,int32_t size);
extern int32_t HTTP_String_writeline(HTTP_String *str,char *src,int32_t size);
extern int32_t HTTP_String_write(HTTP_String *str,char *src,int32_t size);
extern int HTTP_String_destroy(HTTP_String *str);

#ifdef __cplusplus
}
#endif

#endif
