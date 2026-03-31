CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

OBJ_DIR = obj
BIN_DIR = bin

.PHONY: all clean

all: $(BIN_DIR)/tac

$(BIN_DIR)/tac: tac.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
