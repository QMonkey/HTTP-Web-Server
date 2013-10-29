#ifndef HTTP_HANDLER_H
#define HTTP_HANDLER_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int error404_handler(HTTP_socket *request,HTTP_socket *response);
//extern int _handler(HTTP_socket *request,HTTP_socket *response);

#ifdef __cplusplus
}
#endif

#endif
