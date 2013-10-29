#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_response_flush(HTTP_socket *response);
extern int HTTP_response_set_header(HTTP_socket *response,char *header);
extern int HTTP_response_set_content(HTTP_socket *response,char *content);

#ifdef __cplusplus
}
#endif

#endif
