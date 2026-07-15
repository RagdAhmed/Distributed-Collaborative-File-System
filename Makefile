CC = gcc
CFLAGS = -Wall -Iinclude

COMMON_SRC = src/common/net_utils.c

all: server client

server: src/server/main.c $(COMMON_SRC)
	$(CC) $(CFLAGS) src/server/main.c $(COMMON_SRC) -o server

client: src/client/main.c $(COMMON_SRC)
	$(CC) $(CFLAGS) src/client/main.c $(COMMON_SRC) -o client

clean:
	rm -f server client

.PHONY: all clean