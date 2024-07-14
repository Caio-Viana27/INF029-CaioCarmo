#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

vetor_Principal* vetorPrincipal[TAM];

void displayEstrutura () {
    int i = 0;
    while (i < TAM) {

        if (i < TAM - 1) { printf(" %d => ", i + 1); }
        else { printf("%d => ", i + 1); }

        if (vetorPrincipal[i]->estruturaAuxiliar == NULL) {
            printf("Sem Estrutura!\n");
        }
        else if (vetorPrincipal[i]->qtdDeElementos < 1) {
            printf("TAM[%d] => ", vetorPrincipal[i]->tamanho);
            printf("Sem elementos!\n");
        }
        else {
            int j = 0;
            printf("TAM[%d] => ", vetorPrincipal[i]->tamanho);
            while (j < vetorPrincipal[i]->qtdDeElementos) {
                printf("[%d] ", vetorPrincipal[i]->estruturaAuxiliar[j]);
                j++;
            }
            printf("\n");
        }
        i++;
    }
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }
    if (vetorPrincipal[posicao]->estruturaAuxiliar != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }
    else {
        vetorPrincipal[posicao]->estruturaAuxiliar = (int*) malloc(sizeof(int) * tamanho);
        if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
            return SEM_ESPACO_DE_MEMORIA;
        }
        else {
            vetorPrincipal[posicao]->tamanho = tamanho;
            vetorPrincipal[posicao]->qtdDeElementos = 0;
            return SUCESSO;
        }
    }
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao]->qtdDeElementos >= vetorPrincipal[posicao]->tamanho) {
        return SEM_ESPACO;
    }
    else {
        int qtdDeElementos = vetorPrincipal[posicao]->qtdDeElementos;
        vetorPrincipal[posicao]->estruturaAuxiliar[qtdDeElementos] = valor;
        vetorPrincipal[posicao]->qtdDeElementos++;
        return SUCESSO;
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao]->qtdDeElementos == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    else {
        vetorPrincipal[posicao]->qtdDeElementos--;
        return SUCESSO;
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao]->qtdDeElementos == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    int i = 0;
    int qtdElementos = vetorPrincipal[posicao]->qtdDeElementos;
    while (i < qtdElementos) {

        if (vetorPrincipal[posicao]->estruturaAuxiliar[i] == valor) {
            int j = i + 1;
            if (j == qtdElementos) {
                vetorPrincipal[posicao]->qtdDeElementos--;
                return SUCESSO;
            }
            else {

                while (j < qtdElementos) {
                    vetorPrincipal[posicao]->estruturaAuxiliar[i] = vetorPrincipal[posicao]->estruturaAuxiliar[j];
                    i++;
                    j++;
                }
                vetorPrincipal[posicao]->qtdDeElementos--;
                return SUCESSO;
            }
        }
        i++;
    }
    return NUMERO_INEXISTENTE;
}

int excluir(int opcao)
{
    int ret;
    switch(opcao) {
        case 1:
        {
            int posicao, valor;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Excluir Numero Especifico                     |\n");
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
            printf("| Defina o valor a ser excluido                       |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Valor: ");
            scanf("%d", &valor);
            getchar();
            system("clear");

            ret = excluirNumeroEspecificoDeEstrutura(posicao, valor);
            if (ret == SUCESSO)
            {
                return SUCESSO;
            }
            else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
            {
                return ESTRUTURA_AUXILIAR_VAZIA;
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                return SEM_ESTRUTURA_AUXILIAR;
            }
            else if (ret == NUMERO_INEXISTENTE)
            {
                return NUMERO_INEXISTENTE;
            }
            else if (ret == POSICAO_INVALIDA)
            {
                return POSICAO_INVALIDA;
            }
            break;
            }
        case 2:
        {
            int posicao;
            printf(" _____________________________________________________\n");
            printf("|                                                     |\n");
            printf("| Menu: Excluir do Final da Estrutura                 |\n");
            printf("|_____________________________________________________|\n");
            printf("|                                                     |\n");
            printf("| Defina a posicao da estrutura [1...10]              |\n");
            printf("|_____________________________________________________|\n");
            printf("\n");
            printf("Posicao: ");
            scanf("%d", &posicao);
            getchar();
            system("clear");

            ret = excluirNumeroDoFinaldaEstrutura(posicao);
            if (ret == SUCESSO)
            {
                return SUCESSO;
            }
            else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
            {
                return ESTRUTURA_AUXILIAR_VAZIA;
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                return SEM_ESTRUTURA_AUXILIAR;
            }
            else if (ret == POSICAO_INVALIDA)
            {
                return POSICAO_INVALIDA;
            }
            break;
        }
        default:
        {
            return POSICAO_INVALIDA;
        }
    }
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    else {
        int i = 0;
        int qtdElementos = vetorPrincipal[posicao]->qtdDeElementos;
        while (i < qtdElementos) {
            vetorAux[i] = vetorPrincipal[posicao]->estruturaAuxiliar[i];
            i++;
        }
        return SUCESSO;
    }
}

void insertionSort (int qtdElementos, int vetorAux[]) 
{
    for (int i = 1; i < qtdElementos; i++) {
        int key = vetorAux[i];
        int j = i - 1;

        while (j >= 0 && vetorAux[j] > key) {
            vetorAux[j + 1] = vetorAux[j];
            j--;
        }
        vetorAux[j + 1] = key;
    }
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    else {
        int qtdElementos = vetorPrincipal[posicao]->qtdDeElementos;
        insertionSort (qtdElementos, vetorAux);
        return SUCESSO;
    }
}

void printVetor (int * vetor, int tamanho) {
    for (int i = 0; i < tamanho; i++)
        printf("%d ", vetor[i]);
    printf("\n");
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int naoTemEstrtutura = 1;
    int i = 0;
    int j = 0;
    while (i < TAM) {
        if (vetorPrincipal[i]->estruturaAuxiliar != NULL &&
            vetorPrincipal[i]->qtdDeElementos > 0) {
            naoTemEstrtutura = 0;
            int k = 0;
            int size = vetorPrincipal[i]->qtdDeElementos;
            while (k < size) {
                vetorAux[j] = vetorPrincipal[i]->estruturaAuxiliar[k];
                k++;
                j++;
            }
        }
        i++;
    }
    if (naoTemEstrtutura) {return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;}
    else {
        //printf("sem ordenacao ");
        //printVetor (vetorAux, j);
        return SUCESSO;}
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int naoTemEstrtutura = 1;
    int i = 0;
    int j = 0;
    while (i < TAM) {
        if (vetorPrincipal[i]->estruturaAuxiliar != NULL &&
            vetorPrincipal[i]->qtdDeElementos > 0) {
            naoTemEstrtutura = 0;
            int k = 0;
            int size = vetorPrincipal[i]->qtdDeElementos;
            while (k < size) {
                vetorAux[j] = vetorPrincipal[i]->estruturaAuxiliar[k];
                k++;
                j++;
            }
        }
        i++;
    }
    if (naoTemEstrtutura) {return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;}
    else {
        insertionSort (j, vetorAux);
        //printf("com ordenacao ");
        //printVetor (vetorAux, j);
        return SUCESSO;
    }
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao]->tamanho + novoTamanho < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int temp = vetorPrincipal[posicao]->tamanho + novoTamanho;
    int* array = realloc(vetorPrincipal[posicao]->estruturaAuxiliar, temp);

    if (array == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }
    else {
        vetorPrincipal[posicao]->estruturaAuxiliar = array;
        vetorPrincipal[posicao]->tamanho = temp;
        if (vetorPrincipal[posicao]->qtdDeElementos > temp) {
            vetorPrincipal[posicao]->qtdDeElementos = temp;
        }
        return SUCESSO;
    }
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correspondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{
    if (posicao < 1 || posicao > 10) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (vetorPrincipal[posicao]->qtdDeElementos < 1) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }
    return vetorPrincipal[posicao]->qtdDeElementos;
}

void createNode (list* lista, int valor) {
    No* novoNode = (No*) malloc(sizeof(No));
    novoNode->conteudo = valor;

    if (lista->head == NULL) {
        lista->head = lista->tail = novoNode;
        novoNode->prox = NULL;
    }
    else {
        lista->tail->prox = novoNode;
        lista->tail = novoNode;
        novoNode->prox = NULL;
    }
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    list* lista = (list*) malloc(sizeof(list));
    lista->head = lista->tail = NULL;

    int i = 0;
    while (i < TAM) {
        if (vetorPrincipal[i]->estruturaAuxiliar != NULL &&
            vetorPrincipal[i]->qtdDeElementos > 0) {
            int j  = 0;
            while (j < vetorPrincipal[i]->qtdDeElementos) {
                createNode(lista, vetorPrincipal[i]->estruturaAuxiliar[j]);
                j++;
            }
        }
        i++;
    }
    No* cabecote = lista->head;
    free(lista);
    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No* atual = inicio;
    int i = 0;
    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No* atual = (No*) malloc(sizeof(No));
    atual = *inicio;

    while (atual != NULL) {
        No* prox = atual->prox;
        free(atual);
        atual = prox;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for ( int i = 0; i < 10; i++) {
        vetorPrincipal[i] = (vetor_Principal*) malloc(sizeof(vetor_Principal));
        vetorPrincipal[i]->estruturaAuxiliar = NULL;
        vetorPrincipal[i]->tamanho = 0;
        vetorPrincipal[i]->qtdDeElementos = 0;
    }
    int load = loadData();
    if (load) {
        printf("Dados carregados com sucesso!\n");
    }
    else {
        printf("Os dados falharam ao carregar!\n");
    }
    printf("\n");
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    int save = saveData();
    if (save) {
        printf("save concluido!");
    }
    else {
        printf("save falhou!");
    }
    for ( int i = 0; i < 10; i++) {
        if (vetorPrincipal[i]->estruturaAuxiliar != NULL) {
            free(vetorPrincipal[i]->estruturaAuxiliar);
            free(vetorPrincipal[i]);
        }
    }
}

int loadData () {    // dataSave\\data.txt
    FILE* file = fopen("dataSave\\data.txt", "r");
    if (file == NULL) {
        return 0;
    }
    
    int i = 0;
    char* buffer = malloc(sizeof(char) * 100);
    while (fgets(buffer,  100, file) != NULL/* i < TAM */) {

        int j = 0;
        while (buffer[j] != ' ') { j++; }
        j++;
        if (buffer[j] == 'T') {
            
            while (buffer[j] < '1' || buffer[j] > '9') { j++; }
            int h = 0;
            char temp[11];
            while (buffer[j] != ']') {
                temp[h] = buffer[j];
                h++;
                temp[h] = '\0';
                j++;
            }
            int Tam = atoi(temp);

            j += 2;
            if (buffer[j] != 'S') {
                criarEstruturaAuxiliar(i + 1, Tam);
                while (buffer[j] != '\n' && buffer[j] != '\0') {
                    int k = 0;
                    char temp[11];
                    while (buffer[j] != ' ' && buffer[j] != '\n') {
                        temp[k] = buffer[j];
                        k++;
                        temp[k] = '\0';
                        j++;
                    }
                inserirNumeroEmEstrutura(i + 1, atoi(temp));
                j++;
                }
            }
            else {
                criarEstruturaAuxiliar(i + 1, Tam);
            }
        }
        i++;
    }
    free(buffer);
    fclose(file);
    return 1;
}

int saveData () {    // dataSave\\data.txt
    FILE* file = fopen("dataSave\\data.txt", "w+");
    if (file == NULL) {
        return 0;
    }

    int i = 0;
    while (i < TAM) {
        fprintf(file, "Posicao(%d)=> ", i + 1);
        if (vetorPrincipal[i]->estruturaAuxiliar == NULL) {
            fprintf(file, "SE\n");
        }
        else if (vetorPrincipal[i]->qtdDeElementos < 1) {
            fprintf(file, "TAM[%d] ", vetorPrincipal[i]->tamanho);
            fprintf(file, "SN\n");
        }
        else {
            int j = 0;
            fprintf(file, "TAM[%d] ", vetorPrincipal[i]->tamanho);
            while (j < vetorPrincipal[i]->qtdDeElementos) {
                if (j + 1 == vetorPrincipal[i]->qtdDeElementos) {
                    fprintf(file, "%d", vetorPrincipal[i]->estruturaAuxiliar[j]);
                }
                else {
                    fprintf(file, "%d ", vetorPrincipal[i]->estruturaAuxiliar[j]);
                }
                j++;
            }
            fprintf(file, "\n");
        }
        i++;
    }
    fclose(file);
    return 1;
}

//Posicao(1)=> TAM[3] -1 6 3
//Posicao(2)=> TAM[5] 23 -12 56 3 5
//Posicao(3)=> Sem elementos!
//Posicao(4)=> Sem elementos!
//Posicao(5)=> Sem Estrutura!
//Posicao(6)=> Sem Estrutura!
//Posicao(7)=> Sem Estrutura!
//Posicao(8)=> Sem Estrutura!
//Posicao(9)=> Sem Estrutura!
//Posicao(10)=> Sem Estrutura!