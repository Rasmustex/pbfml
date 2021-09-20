CC=clang
CFLAGS=-g -Wall
INCLUDE=include
SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

BINDIR=bin
BIN=$(BINDIR)/pbfml

all:$(BIN)

release: CFLAGS=-O2 -DNDEBUG
release: clean
release: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/cell.h | dirsetup
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	$(RM) -r $(BINDIR)/* $(OBJ)/*

dirsetup: 
	mkdir -p $(BINDIR) $(OBJ) 