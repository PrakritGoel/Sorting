CC=clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: insert.o sorting.o stats.o quick.o heap.o batcher.o
	$(CC) $(CFLAGS) -o sorting insert.o sorting.o stats.o quick.o heap.o batcher.o

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

heap.o: heap.c
	$(CC) $(CFLAGS) -c heap.c

batcher.o: batcher.c
	$(CC) $(CFLAGS) -c batcher.c

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f *.o sorting

format:
	clang-format -i -style=file *.{c,h}
