#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"

// Mostra as opcoes do menu na tela pro usuario escolher
void exibir_menu()
{
    printf("\n===============================================\n");
    printf("          JOGO DE CACA-PALAVRAS\n");
    printf("===============================================\n");
    printf("1 - Buscar palavras automaticamente\n");
    printf("2 - Exibir palavras encontradas\n");
    printf("3 - Remover palavra\n");
    printf("4 - Exibir tabuleiro\n");
    printf("5 - Sair\n");
    printf("===============================================\n");
    printf("Escolha uma opcao: ");
}

// Funcao principal que inicia tudo e controla o loop do jogo
int main()
{
    // Carrega o tabuleiro do arquivo txt
    Tabuleiro *tabuleiro = ler_tabuleiro("tabuleiro.txt");
    if (!tabuleiro)
    {
        printf("Erro ao carregar tabuleiro.\n");
        return 1;
    }

    // Carrega as palavras validas na estrutura trie
    NoTrie *trie = ler_palavras("palavras.txt");
    if (!trie)
    {
        printf("Erro ao carregar palavras.\n");
        liberar_tabuleiro(tabuleiro);
        return 1;
    }

    NoAVL *avl = NULL;
    int opcao;
    int buscou = 0;

    printf("Tabuleiro e palavras carregados com sucesso!\n");

    do
    {
        exibir_menu();
        if (scanf("%d", &opcao) != 1)
        {
            while (getchar() != '\n')
                ;
            opcao = 0;
        }
        getchar();

        switch (opcao)
        {
        case 1:
            if (!buscou)
            {
                printf("\nBuscando palavras no tabuleiro...\n");
                avl = buscar_palavras(tabuleiro, trie);
                printf("Busca concluida!\n");
                buscou = 1;
            }
            else
            {
                printf("\nBusca ja foi realizada!\n");
            }
            break;

        case 2:
            if (buscou)
            {
                imprimir_avl(avl);
            }
            else
            {
                printf("\nRealize a busca primeiro (opcao 1).\n");
            }
            break;

        case 3:
            if (buscou)
            {
                printf("\nDigite a palavra a remover: ");
                char palavra[100];
                scanf("%s", palavra);
                getchar();

                for (int i = 0; palavra[i]; i++)
                {
                    palavra[i] = tolower(palavra[i]);
                }

                if (buscar_avl(avl, palavra))
                {
                    avl = remover_avl(avl, palavra);
                    printf("Palavra '%s' removida com sucesso!\n", palavra);
                }
                else
                {
                    printf("Palavra '%s' nao encontrada.\n", palavra);
                }
            }
            else
            {
                printf("\nRealize a busca primeiro (opcao 1).\n");
            }
            break;

        case 4:
            imprimir_tabuleiro(tabuleiro);
            break;

        case 5:
            printf("\nEncerrando jogo...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 5);

    liberar_avl(avl);
    liberar_trie(trie);
    liberar_tabuleiro(tabuleiro);

    return 0;
}