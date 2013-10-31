PROG = test_string test_urltree test_socket test_select test_access test_regex
OBJS = test_string.o test_urltree.o test_socket.o test_select.o test_access.o test_regex.o
LIBOBJS = ../http_string.o ../http_urltree.o ../http_socket.o ../http_request.o
CC = gcc

all: $(PROG)

test_string: test_string.o
	$(CC) -g -o $@ test_string.o $(LIBOBJS)

test_urltree: test_urltree.o
	$(CC) -g -o $@ test_urltree.o $(LIBOBJS) 

test_socket: test_socket.o
	$(CC) -g -o $@ test_socket.o $(LIBOBJS) -lpthread

$(OBJS): %.o:%.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(PROG) $(OBJS)
