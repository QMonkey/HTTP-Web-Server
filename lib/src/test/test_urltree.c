#include <stdio.h>
#include <string.h>

#include "http_string.h"
#include "http_socket.h"
#include "http_urltree.h"

int hello_handler(HTTP_socket *request,HTTP_socket *response)
{
	fprintf(stdout,"Hello world!\n");
	return 0;
}

int index_handler(HTTP_socket *requdst,HTTP_socket *response)
{
	fprintf(stdout,"Index\n");
	return 0;
}

int web_index_handler(HTTP_socket *request,HTTP_socket *response)
{
	fprintf(stdout,"Web Index\n");
	return 0;
}

int main()
{
	HTTP_node *head = HTTP_create_node("/",hello_handler);
	fprintf(stdout,"handler:\n",head->handler(NULL,NULL));
	HTTP_destroy_node(head);

	head = NULL;
	char url[100] = "/demo/http/web/server/index.html";

	fprintf(stdout,"HTTP_insert_node:\t");
	HTTP_insert_node(&head,url,index_handler)->handler(NULL,NULL);

	HTTP_node *node = head;
	while(node != NULL)
	{
		fprintf(stdout,"key:\t%s\t%d\n",node->key->content,node->handler == NULL);
		node = node->child;
	}

	fprintf(stdout,"HTTP_node_value:\t%s\t",url);
	HTTP_node_value(head,url)(NULL,NULL);

	strcpy(url,"/demo/http/web/index.html");

	fprintf(stdout,"HTTP_insert_node:\t");
	HTTP_insert_node(&head,url,web_index_handler)->handler(NULL,NULL);

	fprintf(stdout,"HTTP_node_value:\t%s\t",url);
	HTTP_node_value(head,url)(NULL,NULL);

	HTTP_destroy_tree(head);
	return 0;
}
