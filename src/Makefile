OBJS = error404_handler.o
CC = gcc

all: $(OBJS)

$(OBJS): %.o:%.c
	$(CC) -g -c $< -I ../include -I ../lib/include

clean:
	-rm -rf $(OBJS)
