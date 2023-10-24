
CC = gcc
CFLAGS = -Wall -Wextra

app: main.c
	$(CC)  $(CFLAGS)  main.c -o app -lseccomp

.PHONY: clean
clean:
	rm -f app

