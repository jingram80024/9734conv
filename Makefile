CC ?= gcc
CFLAGS += -std=c99 -O0 -g

conv9734: conv9734.o repack.o
	$(CC) $(CFLAGS) -o conv9734 conv9734.o repack.o

repack.o: repack.c repack.h

.PHONY: clean
clean:
	rm -f conv9734 *.o *8.raw