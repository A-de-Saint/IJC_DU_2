CC = gcc
CFLAGS = -g -std=c11 -Wall -Werror -Wextra -pedantic
S_LIB = ../static_lib
D_LIB = ../dynamic_lib

.PHONY: all clean

all: test_s test_d

test_s: htab_test.c
	$(CC) $(CFLAGS) $< -L$(S_LIB) -lhtab -o $@

test_d: htab_test.c
	$(CC) $(CFLAGS) $< -L$(D_LIB) -lhtab -o $@

clean: 
	rm -f test_s test_d

