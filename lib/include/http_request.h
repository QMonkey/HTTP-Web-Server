#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern char *HTTP_Request_method[];
extern int HTTP_Request_init(HTTP_Socket *request);
extern int HTTP_Request_get_method(HTTP_Socket *request);
extern int32_t HTTP_Request_get_url(HTTP_Socket *request,char *url);
extern int32_t HTTP_Request_get_header(HTTP_Socket *request,char *key,char *content);
extern int32_t HTTP_Request_get_content(HTTP_Socket *request,char *content);

#ifdef __cplusplus
}
#endif

#endif
