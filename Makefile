PROG = HTTP_Web_Server
CC = gcc

all: $(PROG)

$(PROG): 
	make -C src
	make -C lib/src

clean:
	make clean -C lib/src
	make clean -C src
