PROG = ../main
OBJS = main.o http_server.o http_socket.o http_string.o
CC = gcc

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -g -o $@ *.o -lpthread

$(OBJS): %.o:%.c
	$(CC) -g -c $<

clean:
	-rm -rf $(PROG) $(OBJS)
