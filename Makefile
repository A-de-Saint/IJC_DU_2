CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra

OBJ_DIR = obj
BIN_DIR = bin
LIB_OBJ = $(OBJ_DIR)/libhtab
S_LIB = static_lib
D_LIB = dynamic_lib

LIB_SRC = $(wildcard htab*.c)
LIB_OBJS = $(patsubst %.c, $(LIB_OBJ)/%.o, $(LIB_SRC))

.PHONY: all clean check

all: $(BIN_DIR)/tac $(S_LIB)/libhtab.a $(D_LIB)/libhtab.so

check: all
	./$(BIN_DIR)/tac tac.c -l 10

$(BIN_DIR)/tac: tac.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(S_LIB)/libhtab.a: $(LIB_OBJS) | $(S_LIB)
	ar rcs $@ $^

$(D_LIB)/libhtab.so: $(LIB_OBJS) | $(D_LIB)
	gcc --shared -o $@ $^

$(LIB_OBJ)/%.o: %.c | $(LIB_OBJ)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@
	
$(BIN_DIR):
	mkdir -p $@

$(LIB_OBJ): | $(OBJ_DIR)
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

$(S_LIB):
	mkdir -p $@

$(D_LIB):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(S_LIB) $(D_LIB)
