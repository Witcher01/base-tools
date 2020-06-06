CC = gcc
CFLAGS = -Wall -std=c99 -pedantic
DEPS = util.h args.h file_util.h

cat: cat.o util.o file_util.o $(DEPS)
	$(CC) $(CFLAGS) -o $@ cat.o util.o file_util.o

head: head.o util.o $(DEPS)
	$(CC) $(CFLAGS) -o $@ head.o util.o

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm cat head *.o
