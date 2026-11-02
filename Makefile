CC = gcc 
CFLAGS = -Wall -Wextra -g -Iheader

test_bitmap: src/bitmap.c test/test_bitmap.c
	$(CC) $(CFLAGS) $^ -o $@

clean: rm -f test_bitmap

.Phony: clean