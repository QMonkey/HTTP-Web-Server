#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_response_flush(HTTP_socket *response);
extern int HTTP_response_set_header(HTTP_socket *response,char *header);
extern int HTTP_response_set_content(HTTP_socket *response,char *content);
extern int HTTP_response_set_param(HTTP_socket *response,HTTP_string *key,HTTP_string *value);

#ifdef __cplusplus
}
#endif

#endif
