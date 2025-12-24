#ifndef TRIE_H
#define TRIE_H

#define TAMANHO_ALFABETO 26

typedef struct NoTrie
{
    struct NoTrie *filhos[TAMANHO_ALFABETO];
    int fim_palavra;
} NoTrie;

// Prototipos
NoTrie *criar_no_trie();
void inserir_trie(NoTrie *raiz, const char *palavra);
int buscar_trie(NoTrie *raiz, const char *palavra);
void liberar_trie(NoTrie *raiz);

#endif