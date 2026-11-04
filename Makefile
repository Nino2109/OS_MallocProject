CC = gcc 
CFLAGS = -Wall -Wextra -g -Iheader

all: test_bitmap test_buddy

test_bitmap: src/bitmap.c test/test_bitmap.c
	$(CC) $(CFLAGS) $^ -o $@

test_buddy: src/buddy.c test/test_buddy.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	rm -f test_buddy test_bitmap

.Phony: all clean