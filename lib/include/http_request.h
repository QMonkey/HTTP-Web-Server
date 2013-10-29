#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_request_init(HTTP_socket *request);
extern int32_t HTTP_request_get_url(HTTP_socket *request,char *url);
extern int32_t HTTP_request_get_header(HTTP_socket *request,char *key,char *content);
extern int32_t HTTP_request_get_content(HTTP_socket *request,char *content);

#ifdef __cplusplus
}
#endif

#endif
