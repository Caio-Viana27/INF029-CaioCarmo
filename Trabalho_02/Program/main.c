#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "EstruturaVetores.h"

int menu();

//void dobrar(int *x);

int menu()
{
    int op;
    displayEstrutura();
    printf(" _____________________________________________________\n");
    printf("|                                                     |\n");
    printf("| Menu                                                |\n");
    printf("|_____________________________________________________|\n");
    printf("|                                                     |\n");
    printf("| Digite a opcao desejada                             |\n");
    printf("| 0 - Sair                                            |\n");
    printf("| 1 - Criar estrutura                                 |\n");
    printf("| 2 - Inserir                                         |\n");
    printf("| 3 - Excluir                                         |\n");
    printf("| 4 - Modificar tamanho de uma estrutura              |\n");
    printf("|_____________________________________________________|\n");
    printf("\n");
    printf("Opcao: ");
    scanf("%d", &op);
    getchar();
    system("clear");
    return op;
}

int main()
{
    inicializar();
    int op;
    int sair = 0;
    int ret;
    while (!sair)
    {
        op = menu();
        switch (op)
        {
        case 0:
        {
            sair = 1;
            finalizar();
            break;
        }
        case 1: //criar esturtura auxiliar
        {
            int posicao;
            int tamanho;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Criar Estrutura                               |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Defina a posicao para criar a estrutura [1...10]    |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Posicao: ");
            scanf("%d", &posicao);
            getchar();
            printf("\n");

            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Defina o tamanho da estrutura                       |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Tamanho: ");
            scanf("%d", &tamanho);
            getchar();
            system("clear");

            ret = criarEstruturaAuxiliar(posicao, tamanho);
            displayMessage (ret);
            // ret SUCESSO
            // ret POSICAO_INVALIDA
            // ret SEM_ESPACO_DE_MEMORIA
            // ret == TAMANHO_INVALIDO
            // ret == JA_TEM_ESTRUTURA_AUXILIAR
            break;
        }
        case 2: //inserir
        {
            int posicao;
            int valor;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Inserir na Estrutura                          |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Defina a posicao para inserir na estrutura [1...10] |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Posicao: ");
            scanf("%d", &posicao);
            getchar();
            printf("\n");

            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Defina o valor da estrutura                         |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Valor: ");
            scanf("%d", &valor);
            getchar();
            system("clear");

            ret = inserirNumeroEmEstrutura(posicao, valor);
            displayMessage (ret);
            // ret == SUCESSO
            // ret == SEM_ESPACO
            // ret == SEM_ESTRUTURA_AUXILIAR
            break;
        }
        case 3: //excluir
        {
            int opcao;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Excluir                                       |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Para excluir um valor especifico digite (1)         |\n");
            printf("| Para excluir um valor do final digite (2)           |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            getchar();
            system("clear");

            ret = excluir(opcao);
            displayMessage (ret);
            // ret == SUCESSO
            // ret == ESTRUTURA_AUXILIAR_VAZIA
            // ret == SEM_ESTRUTURA_AUXILIAR
            // ret == NUMERO_INEXISTENTE
            // ret == POSICAO_INVALIDA
            break;
        }
        case 4: // aumenta o tamanho de uma estrutura
        {
            int posicao;
            int somaTam;
            int novoTamanho;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: modificar tamanho da Estrutura                |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Defina a posicao da estrutura [1...10]              |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Posicao: ");
            scanf("%d", &posicao);
            getchar();
            printf("\n");

            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Defina o novo tamanho                               |\n");
            printf("| Novo tamanho sera = tamanho Atual + novo Tamanho    |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("tamanho: ");
            scanf("%d", &novoTamanho);
            getchar();
            system("clear");

            ret = modificarTamanhoEstruturaAuxiliar(posicao, novoTamanho);
            displayMessage (ret);
            // ret = SUCESSO
            // ret = SEM_ESTRUTURA_AUXILIAR
            // ret = POSICAO_INVALIDA
            // ret = NOVO_TAMANHO_INVALIDO
            // ret = SEM_ESPACO_DE_MEMORIA
            break;
        }
        default:
        {
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| ################# opcao invalida ################## |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
        }
        }
    }
    return 0;
}
