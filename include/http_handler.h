#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#include "http_socket.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int default_handler(HTTP_Socket *request,HTTP_Socket *response);
extern int error404_handler(HTTP_Socket *request,HTTP_Socket *response);
extern int index_handler(HTTP_Socket *request,HTTP_Socket *response);
extern int signin_handler(HTTP_Socket *request,HTTP_Socket *response);
extern int signup_handler(HTTP_Socket *request,HTTP_Socket *response);

#ifdef __cplusplus
}
#endif

#endif
