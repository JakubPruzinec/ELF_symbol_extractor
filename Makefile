CFLAGS = -std=c99 -pedantic -Wall -Wextra
CCX = gcc

HDRDEP = $(wildcard *.h)

all:
	make nm

clear:
	rm *.o nm

# COMPILE OBJECTS
nm_api.o: $(HDRDEP) nm_api.c
	$(CCX) $(CFLAGS) nm_api.c -c -o nm_api.o

nm.o: $(HDRDEP) nm.c
	$(CCX) $(CFLAGS) nm.c -c -o nm.o

# LINK OBJECTS
nm: $(HDRDEP) nm_api.o nm.o
	$(CCX) $(CFLAGS) nm_api.o nm.o -l elf -o nm