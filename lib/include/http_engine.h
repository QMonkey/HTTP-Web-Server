#ifndef HTTP_ENGINE_H
#define HTTP_ENGINE_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int render(HTTP_socket *response,char *path,HTTP_param_node *args);

#ifdef __cplusplus
}
#endif

#endif
