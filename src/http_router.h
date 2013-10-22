#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_init_router();
extern int (*)(HTTP_request*,HTTP_response*) HTTP_route(char *url);

#ifdef __cplusplus
}
#endif

#endif
