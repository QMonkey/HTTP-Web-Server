OBJS = error404_handler.o index_handler.o signin_handler.o signup_handler.o default_handler.o verify_signin_handler.o verify_signup_handler.o
CC = gcc

all: $(OBJS)

$(OBJS): %.o:%.c
	$(CC) -g -c $< -I ../include -I ../lib/include `mysql_config --cflags --libs`

clean:
	-rm -rf $(OBJS)
