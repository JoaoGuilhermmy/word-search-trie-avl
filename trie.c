#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "trie.h"

// Cria um novo no da trie inicializando os filhos como NULL
NoTrie *criar_no_trie()
{
    NoTrie *no = (NoTrie *)malloc(sizeof(NoTrie));
    no->fim_palavra = 0;

    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        no->filhos[i] = NULL;
    }

    return no;
}

// Insere uma palavra na trie letra por letra convertendo pra minusculo
void inserir_trie(NoTrie *raiz, const char *palavra)
{
    NoTrie *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char c = tolower(palavra[i]);
        int indice = c - 'a';

        if (indice < 0 || indice >= TAMANHO_ALFABETO)
        {
            continue;
        }

        if (!atual->filhos[indice])
        {
            atual->filhos[indice] = criar_no_trie();
        }

        atual = atual->filhos[indice];
    }

    atual->fim_palavra = 1;
}

// Verifica se uma palavra existe na trie percorrendo seus nos
int buscar_trie(NoTrie *raiz, const char *palavra)
{
    NoTrie *atual = raiz;

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char c = tolower(palavra[i]);
        int indice = c - 'a';

        if (indice < 0 || indice >= TAMANHO_ALFABETO || !atual->filhos[indice])
        {
            return 0;
        }

        atual = atual->filhos[indice];
    }

    return atual && atual->fim_palavra;
}

// Libera a memoria da trie recursivamente
void liberar_trie(NoTrie *raiz)
{
    if (!raiz)
    {
        return;
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (raiz->filhos[i])
        {
            liberar_trie(raiz->filhos[i]);
        }
    }

    free(raiz);
}