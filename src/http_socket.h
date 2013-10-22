#ifndef HTTP_SOCKET_H
#define HTTP_SOCKET_H

typedef struct
{
	int sfd;
	HTTP_string *buffer;
} HTTP_socket;

#define DEFAULT_BUFFER_LENGTH 1024

#ifdef __cplusplus
extern "C"
{
#endif

extern HTTP_socket* HTTP_create_socket(int sfd);
extern int HTTP_set_header(HTTP_socket *http_socket,char *header);
extern int HTTP_get_header(HTTP_socket *http_socket,char *key,char *content);
extern int HTTP_set_content(HTTP_socket *http_socket,char *content);
extern int HTTP_get_content(HTTP_socket *http_socket,char *content);
extern int HTTP_destroy_socket(HTTP_socket *http_socket);

#ifdef __cplusplus
}
#endif

#endif
