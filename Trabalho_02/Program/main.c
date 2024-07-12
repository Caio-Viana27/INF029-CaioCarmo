#include <stdio.h>
#include <stdlib.h>

#include "EstruturaVetores.h"

int menu();

//void dobrar(int *x);

int menu()
{
    int op;
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
    printf("| 4 - Listar uma estrutura                            |\n");
    printf("| 5 - Dobrar Numero                                   |\n");
    printf("| 6 - Exibir todas as estruturas                      |\n");
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
        case 1:
        { //criar esturtura auxiliar
            //TODO
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
            if (ret == SUCESSO)
            {
                printf("Estrutura criada com sucesso\n");
            }
            else if (ret == POSICAO_INVALIDA)
            {
                printf("A posicao nao eh um valor valido\n");
            }
            else if (ret == SEM_ESPACO_DE_MEMORIA)
            {
                printf("Sem espaço de memoria\n");
            }
            else if (ret == TAMANHO_INVALIDO)
            {
                printf("tamanho nao eh um valor valido\n");
            }
            else if (ret == JA_TEM_ESTRUTURA_AUXILIAR)
            {
                printf("Ja existe um estrutura auxiliar nesta posicao\n");
            }
            break;
        }
        case 2:
        { //inserir
            //TODO
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
            printf("Posição: ");
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
            if (ret == SUCESSO)
            {
                printf("Inserido com sucesso\n");
            }
            else if (ret == SEM_ESPACO)
            {
                printf("Sem Espaco\n");
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura Auxiliar\n");
            }
            break;
        }
        case 3:
        { //excluir
            //TODO
            int opcao;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Excluir                                       |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Para excluir um valor especifico digite 1           |\n");
            printf("| Para excluir um valor do final digite 2             |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
            getchar();
            system("clear");

            ret = excluir(opcao);
            if (ret == SUCESSO)
            {
                printf("Inserido com sucesso\n");
            }
            else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
            {
                printf("Estrutura auxiliar vazia\n");
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura Auxiliar\n");
            }
            else if (ret == NUMERO_INEXISTENTE)
            {
                printf("Este valor nao existena estrutura\n");
            }
            else if (ret == POSICAO_INVALIDA)
            {
                printf("Posicao invalida\n");
            }
            break;
        }
        case 4:
        { //recuperar dados estrutura auxiliar
            int posicao, retorno;
            printf("Qual a estrutura a ser listada (1..10)?\n");
            scanf("%d", &posicao);

            int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

            if (qtd == POSICAO_INVALIDA)
            {
                printf("Posicao invalida\n");
            }
            else
            { // existe elemento
                int vetorAux[qtd];

                retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

                if (retorno == SUCESSO)
                {
                    //imprimir os dados para o usuário
                    int i = 0;
                    for (; i < qtd; i++)
                    {
                        printf("%d", vetorAux[i]);
                    }
                }
            }
            break;
        }
        case 5:
        { //dobrar
            //ler um numero
            int valor;
            scanf("%i", &valor);

            //dobrar(&valor);

            //passar para um funcao (void dobrar(...)) que recebe o numero e dobra (EstruturaVetores.c)

            printf("%i", valor);

            break;
        }
        case 6:
        {
            break;
        }
        default:
        {
            printf("opcao invalida\n");
        }
        }
    }
    return 0;
}
