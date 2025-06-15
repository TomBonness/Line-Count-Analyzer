CC = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main.o scanner.o counter.o

linecount: $(OBJS)
	$(CC) $(CFLAGS) -o linecount $(OBJS)

clean:
	rm -f *.o linecount
