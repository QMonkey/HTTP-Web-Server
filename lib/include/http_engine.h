#ifndef HTTP_ENGINE_H
#define HTTP_ENGINE_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int render(HTTP_socket *response,char *page,HTTP_list_node *args);

#ifdef __cplusplus
}
#endif

#endif
