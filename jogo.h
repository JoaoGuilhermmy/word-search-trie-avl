#ifndef JOGO_H
#define JOGO_H

#include "trie.h"
#include "avl.h"

// Estrutura que representa o tabuleiro do jogo
typedef struct
{
    char **matriz;
    int tamanho;
} Tabuleiro;

// Prototipos das funcoes do jogo
Tabuleiro *ler_tabuleiro(const char *arquivo);
NoTrie *ler_palavras(const char *arquivo);
NoAVL *buscar_palavras(Tabuleiro *tab, NoTrie *trie);
void imprimir_tabuleiro(Tabuleiro *tab);
void liberar_tabuleiro(Tabuleiro *tab);

#endif