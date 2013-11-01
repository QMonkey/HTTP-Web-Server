#ifndef HTTP_SOCKET_H
#define HTTP_SOCKET_H

#include <stdint.h>

#include "http_string.h"

typedef struct
{
	int sfd;
	HTTP_String *buffer;
} HTTP_Socket;

#define DEFAULT_BUFFER_LENGTH 1024

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_Socket* HTTP_Socket_create(int sfd);
extern int HTTP_Socket_set_header(HTTP_Socket *http_socket,char *header);
extern int32_t HTTP_Socket_get_header(HTTP_Socket *http_socket,char *key,char *content);
extern int HTTP_Socket_set_content(HTTP_Socket *http_socket,char *content);
extern int32_t HTTP_Socket_get_content(HTTP_Socket *http_socket,char *content);
extern int HTTP_Socket_destroy(HTTP_Socket *http_socket,int how);

#ifdef __cplusplus
}
#endif

#endif
