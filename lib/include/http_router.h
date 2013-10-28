#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#include "http_urltree.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_init_router();
extern HTTP_Handler HTTP_route(char *url);

#ifdef __cplusplus
}
#endif

#endif
