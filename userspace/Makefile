#
# Author Feng Gao
#
#

.PHONY: all clean test

CC		:= gcc
CFLAGS  := -Wall -Werror -g
LFLAGS  :=

TARGET	:= mmap_app

all: mmap_app.o
	$(CC) $(CFLAGS) $(LFLAGS) mmap_app.o -o $(TARGET)

comm_cache.o: mmap_app.c *.h


clean:
	rm -rf *.o $(TARGET) test

