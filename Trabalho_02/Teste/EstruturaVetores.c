#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 10

#include "EstruturaVetores.h"

vetor_Principal* vetorPrincipal[TAM];

// se posição é um valor válido {entre 1 e 10} retorna true
bool ehPosicaoValida(int posicao)
{
    if (posicao < 1 || posicao > 10) return false;
    else return true;
}
// se tamanho é um valor válido {maior que 0} retorna true
bool ehTamanhoValido(int tamanho)
{
    if (tamanho < 1) return false;
    else return true;
}
// se existe estrutura na posição 'posição' retorna true
bool existeEstruturaAuxiliar(int posicao)
{
    if (vetorPrincipal[posicao]->estruturaAuxiliar == NULL) return false;
    else return true;
}
// se a estrutura na posição 'posição' esta cheia retorna true
bool EstruturaCheia(int posicao)
{
    if ((vetorPrincipal[posicao]->qtdDeElementos >= vetorPrincipal[posicao]->tamanho)) return true;
    else return false;
}
// se a estrutura na posição 'posição' esta vazia retorna true
bool EstruturaVazia(int posicao)
{
    if ((vetorPrincipal[posicao]->qtdDeElementos == 0)) return true;
    else return false;
}
// se o novo tamanho da estrutura é valido retorna true
bool novoTamanhoEhValido(int posicao, int novoTamanho)
{
    if ((vetorPrincipal[posicao]->tamanho + novoTamanho < 1)) return false;
    else return true;
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!ehTamanhoValido(tamanho)) {
        return TAMANHO_INVALIDO;
    }
    if (existeEstruturaAuxiliar(posicao)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (EstruturaCheia(posicao)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (EstruturaVazia(posicao)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (EstruturaVazia(posicao)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
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
        if (existeEstruturaAuxiliar(i) && !EstruturaVazia(i)) {
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
    if (naoTemEstrtutura) { return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS; }
    else { return SUCESSO; }
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
        if (existeEstruturaAuxiliar(i) && !EstruturaVazia(i)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (!novoTamanhoEhValido(posicao, novoTamanho)) {
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
    if (!ehPosicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }
    posicao -= 1;
    if (!existeEstruturaAuxiliar(posicao)) {
        return SEM_ESTRUTURA_AUXILIAR;
    }
    if (EstruturaVazia(posicao)) {
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
        if (/* vetorPrincipal[i]->estruturaAuxiliar != NULL */existeEstruturaAuxiliar(i) &&
            /* vetorPrincipal[i]->qtdDeElementos > 0 */!EstruturaVazia(i)) {
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
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    for ( int i = 0; i < 10; i++) {
        if (vetorPrincipal[i]->estruturaAuxiliar != NULL) {
            free(vetorPrincipal[i]->estruturaAuxiliar);
            free(vetorPrincipal[i]);
        }
    }
}
