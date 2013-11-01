#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int HTTP_Response_flush(HTTP_Socket *response);
extern int HTTP_Response_set_header(HTTP_Socket *response,char *header);
extern int HTTP_Response_set_content(HTTP_Socket *response,char *content);
extern int HTTP_Response_set_param(HTTP_Socket *response,HTTP_String *key,HTTP_String *value);

#ifdef __cplusplus
}
#endif

#endif
