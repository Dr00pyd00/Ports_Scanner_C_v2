
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -pthread
OBJ = main.o scan.o

prog: $(OBJ)
	$(CC) $(CFLAGS) -o prog $(OBJ)

main.o: main.c scan.h
	$(CC) $(CFLAGS) -c main.c

scan.o: scan.c scan.h
	$(CC) $(CFLAGS) -c scan.c

clean:
	rm -f prog $(OBJ)


