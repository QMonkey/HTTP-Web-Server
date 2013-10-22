#ifndef HTTP_ROUTER_H
#define HTTP_ROUTER_H

typedef int (*HTTP_handler)(HTTP_reqest*,HTTP_response*);

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_route(HTTP_handler *handler);

#ifdef __cplusplus
}
#endif

#endif
