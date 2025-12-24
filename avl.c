#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// Funçao auxiliar pra retornar o maior entre dois numeros inteiros
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Retorna a altura de um no ou 0 se ele for nulo (vazio)
int altura(NoAVL *no)
{
    return no ? no->altura : 0;
}

// Calcula o balanco do no: altura da esquerda menos altura da direita
int fator_balanceamento(NoAVL *no)
{
    return no ? altura(no->esquerdo) - altura(no->direito) : 0;
}

// Recalcula a altura do no com base na altura dos filhos mais 1
void atualizar_altura(NoAVL *no)
{
    if (no)
    {
        no->altura = 1 + max(altura(no->esquerdo), altura(no->direito));
    }
}

// Faz a rotacao simples para a direita pra balancear a arvore
NoAVL *rotacao_direita(NoAVL *y)
{
    NoAVL *x = y->esquerdo;
    NoAVL *T2 = x->direito;

    x->direito = y;
    y->esquerdo = T2;

    atualizar_altura(y);
    atualizar_altura(x);

    return x;
}

// Faz a rotacao simples para a esquerda pra corrigir desequilibrio
NoAVL *rotacao_esquerda(NoAVL *x)
{
    NoAVL *y = x->direito;
    NoAVL *T2 = y->esquerdo;

    y->esquerdo = x;
    x->direito = T2;

    atualizar_altura(x);
    atualizar_altura(y);

    return y;
}

// Aloca memoria e cria um novo no da AVL com a palavra e coordenadas
NoAVL *criar_no_avl(const char *palavra, Coordenadas coord)
{
    NoAVL *no = (NoAVL *)malloc(sizeof(NoAVL));
    no->palavra = (char *)malloc(strlen(palavra) + 1);
    strcpy(no->palavra, palavra);
    no->coord = coord;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    return no;
}

// Insere uma palavra na arvore e aplica rotacoes se precisar balancear
NoAVL *inserir_avl(NoAVL *raiz, const char *palavra, Coordenadas coord)
{
    if (!raiz)
    {
        return criar_no_avl(palavra, coord);
    }

    int cmp = strcmp(palavra, raiz->palavra);

    if (cmp < 0)
    {
        raiz->esquerdo = inserir_avl(raiz->esquerdo, palavra, coord);
    }
    else if (cmp > 0)
    {
        raiz->direito = inserir_avl(raiz->direito, palavra, coord);
    }
    else
    {
        return raiz;
    }

    atualizar_altura(raiz);
    int fb = fator_balanceamento(raiz);

    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) < 0)
    {
        return rotacao_direita(raiz);
    }

    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) > 0)
    {
        return rotacao_esquerda(raiz);
    }

    if (fb > 1 && strcmp(palavra, raiz->esquerdo->palavra) > 0)
    {
        raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && strcmp(palavra, raiz->direito->palavra) < 0)
    {
        raiz->direito = rotacao_direita(raiz->direito);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

// Busca o no com menor valor (mais a esquerda) pra ajudar na remocao
NoAVL *obter_menor(NoAVL *no)
{
    NoAVL *atual = no;
    while (atual && atual->esquerdo)
    {
        atual = atual->esquerdo;
    }
    return atual;
}

// Remove um no da arvore e rebalanceia se nescessario
NoAVL *remover_avl(NoAVL *raiz, const char *palavra)
{
    if (!raiz)
    {
        return raiz;
    }

    int cmp = strcmp(palavra, raiz->palavra);

    if (cmp < 0)
    {
        raiz->esquerdo = remover_avl(raiz->esquerdo, palavra);
    }
    else if (cmp > 0)
    {
        raiz->direito = remover_avl(raiz->direito, palavra);
    }
    else
    {
        if (!raiz->esquerdo || !raiz->direito)
        {
            NoAVL *temp = raiz->esquerdo ? raiz->esquerdo : raiz->direito;

            if (!temp)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }

            free(temp->palavra);
            free(temp);
        }
        else
        {
            NoAVL *temp = obter_menor(raiz->direito);
            free(raiz->palavra);
            raiz->palavra = (char *)malloc(strlen(temp->palavra) + 1);
            strcpy(raiz->palavra, temp->palavra);
            raiz->coord = temp->coord;
            raiz->direito = remover_avl(raiz->direito, temp->palavra);
        }
    }

    if (!raiz)
    {
        return raiz;
    }

    atualizar_altura(raiz);
    int fb = fator_balanceamento(raiz);

    if (fb > 1 && fator_balanceamento(raiz->esquerdo) >= 0)
    {
        return rotacao_direita(raiz);
    }

    if (fb > 1 && fator_balanceamento(raiz->esquerdo) < 0)
    {
        raiz->esquerdo = rotacao_esquerda(raiz->esquerdo);
        return rotacao_direita(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->direito) <= 0)
    {
        return rotacao_esquerda(raiz);
    }

    if (fb < -1 && fator_balanceamento(raiz->direito) > 0)
    {
        raiz->direito = rotacao_direita(raiz->direito);
        return rotacao_esquerda(raiz);
    }

    return raiz;
}

// Funcao recursiva que imprime a arvore em ordem alfabetica (esq-raiz-dir)
void imprimir_avl_recursivo(NoAVL *raiz)
{
    if (raiz)
    {
        imprimir_avl_recursivo(raiz->esquerdo);
        printf("%-15s [(%d,%d) -> (%d,%d)]\n", raiz->palavra,
               raiz->coord.linha_inicio, raiz->coord.coluna_inicio,
               raiz->coord.linha_fim, raiz->coord.coluna_fim);
        imprimir_avl_recursivo(raiz->direito);
    }
}

// Funcao principal pra exibir todas as palavras achadas no jogo
void imprimir_avl(NoAVL *raiz)
{
    printf("\n=== Palavras Encontradas ===\n");
    if (!raiz)
    {
        printf("Nenhuma palavra encontrada.\n");
    }
    else
    {
        imprimir_avl_recursivo(raiz);
    }
    printf("\n");
}

// Busca se uma palavra especifica existe na arvore avl
int buscar_avl(NoAVL *raiz, const char *palavra)
{
    if (!raiz)
    {
        return 0;
    }

    int cmp = strcmp(palavra, raiz->palavra);

    if (cmp == 0)
    {
        return 1;
    }
    else if (cmp < 0)
    {
        return buscar_avl(raiz->esquerdo, palavra);
    }
    else
    {
        return buscar_avl(raiz->direito, palavra);
    }
}

// Libera toda memoria alocada pela arvore pra nao vazar memoria
void liberar_avl(NoAVL *raiz)
{
    if (raiz)
    {
        liberar_avl(raiz->esquerdo);
        liberar_avl(raiz->direito);
        free(raiz->palavra);
        free(raiz);
    }
}