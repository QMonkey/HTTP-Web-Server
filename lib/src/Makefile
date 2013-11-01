PROG = ../../HTTP_Web_Server
OBJS = main.o http_server.o http_socket.o http_string.o http_urltree.o http_router.o http_request.o http_response.o http_param_linkedlist.o http_replacer_linkedlist.o http_engine.o http_file.o
HANDLERS=../../src/error404_handler.o ../../src/index_handler.o ../../src/signin_handler.o ../../src/signup_handler.o
CC = gcc

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -g -o $@ *.o -lpthread $(HANDLERS)
	make -C test

$(OBJS): %.o:%.c
	$(CC) -g -c $< -I ../include -I ../../include

clean:
	make clean -C test
	-rm -rf $(PROG) $(OBJS)
