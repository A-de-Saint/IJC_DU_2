# Autor: Antonín Hrnčíř, FIT
# Makefile pro IJC-DU2

CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
CPP = g++
CPPFLAGS = -std=c++17 -pedantic -Wall

OBJ_DIR = obj
BIN_DIR = bin
LIB_OBJ = $(OBJ_DIR)/libhtab
S_LIB = static_lib
D_LIB = dynamic_lib

LIB_SRC = $(wildcard htab*.c)
LIB_OBJS = $(patsubst %.c, $(LIB_OBJ)/%.o, $(LIB_SRC))

.PHONY: all clean check

all: $(BIN_DIR)/tac $(BIN_DIR)/maxwordcount $(BIN_DIR)/maxwordcount-dynamic $(BIN_DIR)/maxwordcount-cpp

check: all
	./$(BIN_DIR)/tac tac.c -l 10
	@printf "\n%s\n" "CPP reference output:"
	(cat /usr/share/dict/words; echo yes no error) | ./$(BIN_DIR)/maxwordcount-cpp
	@printf "\n%s\n" "C static output:"
	(cat /usr/share/dict/words; echo yes no error) | ./$(BIN_DIR)/maxwordcount
	@printf "\n%s\n" "C dynamic output:"
	(cat /usr/share/dict/words; echo yes no error) | (LD_LIBRARY_PATH="$(D_LIB)/" ./$(BIN_DIR)/maxwordcount-dynamic)

$(BIN_DIR)/tac: tac.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/maxwordcount: $(OBJ_DIR)/maxwordcount.o $(OBJ_DIR)/io.o $(S_LIB)/libhtab.a | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/maxwordcount.o $(OBJ_DIR)/io.o -L$(S_LIB) -lhtab -o $@

$(BIN_DIR)/maxwordcount-dynamic: $(OBJ_DIR)/maxwordcount.o $(OBJ_DIR)/io.o $(D_LIB)/libhtab.so | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_DIR)/maxwordcount.o $(OBJ_DIR)/io.o -L$(D_LIB) -lhtab -o $@

$(BIN_DIR)/maxwordcount-cpp: maxwordcount-cpp.cc
	$(CPP) $(CPPFLAGS) $< -o $@

$(S_LIB)/libhtab.a: $(LIB_OBJS) | $(S_LIB)
	ar rcs $@ $^

$(D_LIB)/libhtab.so: $(LIB_OBJS) | $(D_LIB)
	gcc --shared -o $@ $^

$(LIB_OBJ)/%.o: %.c | $(LIB_OBJ)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
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
