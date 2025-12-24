CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = caca-palavras

ifeq ($(OS),Windows_NT)
    RM = del /Q
    TARGET := $(TARGET).exe
else
    RM = rm -f
endif

OBJS = main.o jogo.o avl.o trie.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Adicionei jogo.h nas dependencias abaixo
main.o: main.c avl.h trie.h jogo.h
	$(CC) $(CFLAGS) -c main.c

jogo.o: jogo.c avl.h trie.h jogo.h
	$(CC) $(CFLAGS) -c jogo.c

avl.o: avl.c avl.h
	$(CC) $(CFLAGS) -c avl.c

trie.o: trie.c trie.h
	$(CC) $(CFLAGS) -c trie.c

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all clean