#ifndef HTTP_FILE_H
#define HTTP_FILE_H

#include <stdint.h>

#include "http_string.h"

#define FILE_BUFFER_LENGTH 4096

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_file_exists(char *path);
extern int32_t HTTP_file_read_all(HTTP_string *buffer,char *path);

#ifdef __cplusplus
}
#endif

#endif
