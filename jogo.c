#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "avl.h"
#include "trie.h"
#include "jogo.h"

// Le o tabuleiro do arquivo e retorna uma estrutura com a matriz
Tabuleiro *ler_tabuleiro(const char *arquivo)
{
    FILE *f = fopen(arquivo, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return NULL;
    }

    Tabuleiro *tab = (Tabuleiro *)malloc(sizeof(Tabuleiro));
    int linhas, colunas;
    fscanf(f, "%d %d", &linhas, &colunas);
    tab->tamanho = linhas;

    tab->matriz = (char **)malloc(linhas * sizeof(char *));
    for (int i = 0; i < linhas; i++)
    {
        tab->matriz[i] = (char *)malloc(colunas * sizeof(char));
        for (int j = 0; j < colunas; j++)
        {
            char c;
            do
            {
                fscanf(f, " %c", &c);
            } while (c == '\n' || c == '\r');
            tab->matriz[i][j] = tolower(c);
        }
    }

    fclose(f);
    return tab;
}

// Le as palavras do arquivo e insere na trie
NoTrie *ler_palavras(const char *arquivo)
{
    FILE *f = fopen(arquivo, "r");
    if (!f)
    {
        printf("Erro ao abrir arquivo %s\n", arquivo);
        return NULL;
    }

    NoTrie *raiz = criar_no_trie();
    char palavra[100];

    while (fscanf(f, "%s", palavra) != EOF)
    {
        for (int i = 0; palavra[i]; i++)
        {
            palavra[i] = tolower(palavra[i]);
        }
        inserir_trie(raiz, palavra);
    }

    fclose(f);
    return raiz;
}

// Inverte uma string pra buscar palavras ao contrario
void inverter_string(char *str)
{
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        char temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
}

// Busca palavras na horizontal (esquerda-direita e direita-esquerda)
NoAVL *buscar_horizontal(Tabuleiro *tab, NoTrie *trie, NoAVL *avl)
{
    for (int i = 0; i < tab->tamanho; i++)
    {
        for (int j = 0; j < tab->tamanho; j++)
        {
            for (int tam = 2; j + tam <= tab->tamanho; tam++)
            {
                char palavra[100];
                for (int k = 0; k < tam; k++)
                {
                    palavra[k] = tab->matriz[i][j + k];
                }
                palavra[tam] = '\0';

                if (buscar_trie(trie, palavra) && !buscar_avl(avl, palavra))
                {
                    Coordenadas coord = {i, j, i, j + tam - 1};
                    avl = inserir_avl(avl, palavra, coord);
                }

                char invertida[100];
                strcpy(invertida, palavra);
                inverter_string(invertida);

                if (buscar_trie(trie, invertida) && !buscar_avl(avl, invertida))
                {
                    Coordenadas coord = {i, j + tam - 1, i, j};
                    avl = inserir_avl(avl, invertida, coord);
                }
            }
        }
    }
    return avl;
}

// Busca palavras na vertical (cima-baixo e baixo-cima)
NoAVL *buscar_vertical(Tabuleiro *tab, NoTrie *trie, NoAVL *avl)
{
    for (int j = 0; j < tab->tamanho; j++)
    {
        for (int i = 0; i < tab->tamanho; i++)
        {
            for (int tam = 2; i + tam <= tab->tamanho; tam++)
            {
                char palavra[100];
                for (int k = 0; k < tam; k++)
                {
                    palavra[k] = tab->matriz[i + k][j];
                }
                palavra[tam] = '\0';

                if (buscar_trie(trie, palavra) && !buscar_avl(avl, palavra))
                {
                    Coordenadas coord = {i, j, i + tam - 1, j};
                    avl = inserir_avl(avl, palavra, coord);
                }

                char invertida[100];
                strcpy(invertida, palavra);
                inverter_string(invertida);

                if (buscar_trie(trie, invertida) && !buscar_avl(avl, invertida))
                {
                    Coordenadas coord = {i + tam - 1, j, i, j};
                    avl = inserir_avl(avl, invertida, coord);
                }
            }
        }
    }
    return avl;
}

// Busca palavras na diagonal principal (canto superior esquerdo pra inferior direito)
NoAVL *buscar_diagonal_principal(Tabuleiro *tab, NoTrie *trie, NoAVL *avl)
{
    for (int i = 0; i < tab->tamanho; i++)
    {
        for (int j = 0; j < tab->tamanho; j++)
        {
            for (int tam = 2; i + tam <= tab->tamanho && j + tam <= tab->tamanho; tam++)
            {
                char palavra[100];
                for (int k = 0; k < tam; k++)
                {
                    palavra[k] = tab->matriz[i + k][j + k];
                }
                palavra[tam] = '\0';

                if (buscar_trie(trie, palavra) && !buscar_avl(avl, palavra))
                {
                    Coordenadas coord = {i, j, i + tam - 1, j + tam - 1};
                    avl = inserir_avl(avl, palavra, coord);
                }

                char invertida[100];
                strcpy(invertida, palavra);
                inverter_string(invertida);

                if (buscar_trie(trie, invertida) && !buscar_avl(avl, invertida))
                {
                    Coordenadas coord = {i + tam - 1, j + tam - 1, i, j};
                    avl = inserir_avl(avl, invertida, coord);
                }
            }
        }
    }
    return avl;
}

// Busca palavras na diagonal secundaria (canto superior direito pra inferior esquerdo)
NoAVL *buscar_diagonal_secundaria(Tabuleiro *tab, NoTrie *trie, NoAVL *avl)
{
    for (int i = 0; i < tab->tamanho; i++)
    {
        for (int j = 0; j < tab->tamanho; j++)
        {
            for (int tam = 2; i + tam <= tab->tamanho && j - tam + 1 >= 0; tam++)
            {
                char palavra[100];
                for (int k = 0; k < tam; k++)
                {
                    palavra[k] = tab->matriz[i + k][j - k];
                }
                palavra[tam] = '\0';

                if (buscar_trie(trie, palavra) && !buscar_avl(avl, palavra))
                {
                    Coordenadas coord = {i, j, i + tam - 1, j - tam + 1};
                    avl = inserir_avl(avl, palavra, coord);
                }

                char invertida[100];
                strcpy(invertida, palavra);
                inverter_string(invertida);

                if (buscar_trie(trie, invertida) && !buscar_avl(avl, invertida))
                {
                    Coordenadas coord = {i + tam - 1, j - tam + 1, i, j};
                    avl = inserir_avl(avl, invertida, coord);
                }
            }
        }
    }
    return avl;
}

// Funcao principal que busca palavras em todas as direcoes
NoAVL *buscar_palavras(Tabuleiro *tab, NoTrie *trie)
{
    NoAVL *avl = NULL;

    avl = buscar_horizontal(tab, trie, avl);
    avl = buscar_vertical(tab, trie, avl);
    avl = buscar_diagonal_principal(tab, trie, avl);
    avl = buscar_diagonal_secundaria(tab, trie, avl);

    return avl;
}

// Exibe o tabuleiro na tela
void imprimir_tabuleiro(Tabuleiro *tab)
{
    printf("\n=== Tabuleiro %dx%d ===\n", tab->tamanho, tab->tamanho);
    for (int i = 0; i < tab->tamanho; i++)
    {
        for (int j = 0; j < tab->tamanho; j++)
        {
            printf("%c ", toupper(tab->matriz[i][j]));
        }
        printf("\n");
    }
    printf("\n");
}

// Libera a memoria do tabuleiro
void liberar_tabuleiro(Tabuleiro *tab)
{
    if (tab)
    {
        for (int i = 0; i < tab->tamanho; i++)
        {
            free(tab->matriz[i]);
        }
        free(tab->matriz);
        free(tab);
    }
}