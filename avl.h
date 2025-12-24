#ifndef AVL_H
#define AVL_H

typedef struct
{
    int linha_inicio;
    int coluna_inicio;
    int linha_fim;
    int coluna_fim;
} Coordenadas;

typedef struct NoAVL
{
    char *palavra;
    Coordenadas coord;
    struct NoAVL *esquerdo;
    struct NoAVL *direito;
    int altura;
} NoAVL;

// Apenas protótipos das funções
NoAVL *criar_no_avl(const char *palavra, Coordenadas coord);
NoAVL *inserir_avl(NoAVL *raiz, const char *palavra, Coordenadas coord);
NoAVL *remover_avl(NoAVL *raiz, const char *palavra);
void imprimir_avl(NoAVL *raiz);
void liberar_avl(NoAVL *raiz);
int buscar_avl(NoAVL *raiz, const char *palavra);

#endif