#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#include "http_urltree.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_Router_init();
extern HTTP_Handler HTTP_Router_route(char *url);
extern int HTTP_Router_destroy();

#ifdef __cplusplus
}
#endif

#endif
