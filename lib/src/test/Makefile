PROG = test_string test_urltree
OBJS = test_string.o test_urltree.o
LIBOBJS = ../http_string.o ../http_urltree.o
CC = gcc

all: $(PROG)

test_string: test_string.o
	$(CC) -g -o $@ test_string.o $(LIBOBJS)

test_urltree: test_urltree.o
	$(CC) -g -o $@ test_urltree.o $(LIBOBJS) 

$(OBJS): %.o:%.c
	$(CC) -g -c $< -I ../../include

clean:
	-rm -rf $(PROG) $(OBJS)
