#ifndef HTTP_ENGINE_H
#define HTTP_ENGINE_H

#include "http_socket.h"
#include "http_param_linkedlist.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_Engine_render(HTTP_Socket *response,char *path,HTTP_Param_node *args);

#ifdef __cplusplus
}
#endif

#endif
