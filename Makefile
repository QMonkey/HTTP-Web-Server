PROG = HTTP_Web_Server
CC = gcc

all: $(PROG)

$(PROG): 
	make -C lib/src
	make -C src

clean:
	make clean -C lib/src
	make clean -C src
