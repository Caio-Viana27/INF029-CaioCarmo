#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Professor.h"
#define max_nome 50
#define max_CPF 12
#define max_tam 5
#define data 3
#define max_idade 3
#define CADASTRO_SUCESSO -1
#define CADASTRO_FALHOU -2
#define CADASTRO_ATUALIZADO -3
#define ATUALIZAR_FALHOU -4
#define CADASTRO_EXCLUIDO -5
#define EXCLUIR_FALHOU -6
#define true 1

typedef struct {
  char Nome[max_nome];
  int idade[data];
} ordenarData;

int main();
int menuProfessor();
int cadastrarProfessor(Professor listaProfessor[], int qtdProfessor);
int atualizarProfessor(Professor listaProfessor[], int qtdProfessor);
int ExcluirProfessor(Professor listaProfessor[], int qtdProfessor);
void listarProfessor(Professor listaProfessor[], int qtdProfessor);

int DataNascimentoProfessor(Professor listaProfessor[], int qtdProfessor);
int validarSexoProfessor(Professor listaProfessor[], int qtdProfessor);
int validarMatriculaProfessor( Professor listaProfessor[], int qtdProfessor);
int validarCpfProfessor(Professor listaProfessor[], int qtdProfessor);
int validarNomeProfessor(Professor listaProfessor[], int qtdProfessor);
void string_captilize_Professor (Professor listaProfessor[], int qtdProfessor);
void char_captilize_Professor (Professor listaProfessor[], int qtdProfessor);
char char_captilize (char sexo);

void quicksort(char sortedListProfessor[][max_nome], int qtdProfessor);
void quicksort_recursion(char sortedListProfessor[][max_nome],int menor_index, int qtdProfessor);
int partition(char sortedListProfessor[][max_nome],int menor_index, int qtdProfessor);
void copiarProfessor(Professor listaProfessor[], char sortedListProfessor[][max_nome], int qtdProfessor);
void quicksortData(ordenarData sortedListData[], int qtdProfessor);
void quicksort_recursionData(ordenarData sortedListData[],int menor_index, int qtdProfessor);
int partitionData(ordenarData sortedListData[],int menor_index, int qtdProfessor);
void copiarProfessorData(Professor listaProfessor[], ordenarData sortedListData[], int qtdProfessor);

Professor listaProfessor[max_tam];
int qtdProfessor = 0;

FILE *arquivoProfessor;

int menuProfessor() {

  arquivoProfessor = fopen("Professor.txt", "w");
  if (arquivoProfessor == NULL) {
    printf("Falha ao abrir o arquivo!\n");
  }

  int opcao;

  printf("----------------------------------------\n");
  printf("|  Menu Professor:                     |\n");
  printf("|  Professor(es) cadastrado(s): %d      |\n", qtdProfessor);
  printf("----------------------------------------\n");
  printf("|  0 - Voltar                          |\n");
  printf("|  1 - Cadastrar Professor             |\n");
  printf("|  2 - Atualizar Professor             |\n");
  printf("|  3 - Excluir Professor               |\n");
  printf("|  4 - Listar                          |\n");
  printf("----------------------------------------\n");
  scanf("%d", &opcao);
  system("clear");

  switch (opcao) { 

     case 0:
        opcao = main();
        system("clear");
        break;

     case 1:
        opcao = cadastrarProfessor(listaProfessor, qtdProfessor);
        if (opcao == CADASTRO_SUCESSO) {
           qtdProfessor += 1;
           printf("Professor cadastrado com sucesso!\n");
        }else if (opcao == CADASTRO_FALHOU) {
           printf("Não foi possível cadastrar o professor!\n");
        }         
        if(opcao == CADASTRO_SUCESSO || opcao == CADASTRO_FALHOU)
          opcao = menuProfessor(qtdProfessor);
        fclose(arquivoProfessor);
        break;

    case 2:
        opcao = atualizarProfessor(listaProfessor, qtdProfessor);
        if (opcao == CADASTRO_ATUALIZADO) {
          printf("Professor(a) Atualizado(a) com sucesso!\n");
        }else if (opcao == ATUALIZAR_FALHOU) {
          printf("Não foi possível Atualizar o Professor!\n");
        }         
        if(opcao == CADASTRO_ATUALIZADO || opcao == ATUALIZAR_FALHOU)
        opcao = menuProfessor(qtdProfessor);
    break;

    case 3:
        opcao = ExcluirProfessor(listaProfessor, qtdProfessor);
        if (opcao == CADASTRO_EXCLUIDO) {
            qtdProfessor--;
          printf("Professor(a) excluido(a) com sucesso!\n");
        }else if (opcao == EXCLUIR_FALHOU) {
          printf("Não foi possível excluir o Professor!\n");
        }         
        if(opcao == CADASTRO_EXCLUIDO || opcao == EXCLUIR_FALHOU)
        opcao = menuProfessor(qtdProfessor);
    break;

    case 4:
        listarProfessor(listaProfessor, qtdProfessor);
        menuProfessor(qtdProfessor);
    break;
    default:
      printf("Opção inválida");
    break;
  }
  return opcao;
}

int cadastrarProfessor(Professor listaProfessor[], int qtdProfessor) {

  int sair = 1;

  if (qtdProfessor < max_tam) {

    while(sair != 0) {

      validarMatriculaProfessor(listaProfessor, qtdProfessor); 

      validarNomeProfessor(listaProfessor, qtdProfessor);

      validarSexoProfessor(listaProfessor, qtdProfessor);

      validarCpfProfessor(listaProfessor, qtdProfessor);

      DataNascimentoProfessor(listaProfessor, qtdProfessor); 

      sair = 0;
    }
    return CADASTRO_SUCESSO;
  }else {
    printf("Lista de Professores cheia!\n");
    return CADASTRO_FALHOU;
  }
}

void listarProfessor(Professor listaProfessor[], int qtdProfessor) {
  int mes;
  int selecionar;
  char sexo;

  if (qtdProfessor == 0) {
    printf("Não há professores cadastrados!\n");
  }else {



    printf("----------------------------------------\n");
    printf("|  Lista Professor:                    |\n");
    printf("|  Professor(es) cadastrado(s): %d      |\n", qtdProfessor);
    printf("----------------------------------------\n");
    printf("|  0 - listar Professores              |\n");
    printf("|  1 - listar Professores por Nome     |\n");
    printf("|  2 - listar Prof. por Nascimento     |\n");
    printf("|  3 - listar Profefessores pro sexo   |\n");
    printf("|  4 - listar aniversariantes do mês   |\n");
    printf("----------------------------------------\n");
    scanf("%d", &selecionar);
    getchar();

    switch (selecionar) {

      case 0:
          printf("----------------------------------------\n");
          printf("| Lista de Professores:                |\n");
          printf("| %d professor(es) cadastrado(s)        |\n", qtdProfessor);
          printf("----------------------------------------\n");

          for(int i = 0; i < qtdProfessor; i++) {

            printf("Nome: %s",                listaProfessor[i].Nome);
            printf("CPF: %s",                 listaProfessor[i].CPF);
            printf("Matricula: %d\n",         listaProfessor[i].Matricula);
            printf("Sexo: %c\n",              listaProfessor[i].Sexo);
            printf("Data de nascimento: %d/", listaProfessor[i].idade[0]);
            printf("%d/",                     listaProfessor[i].idade[1]);
            printf("%d\n",                    listaProfessor[i].idade[2]);
            printf("----------------------------------------\n");
          }
      break;

     case 1:
        printf("----------------------------------------\n");
        printf("| Lista de Professores por Nome:       |\n");
        printf("| %d professor(es) cadastrado(s)        |\n", qtdProfessor);
        printf("----------------------------------------\n");

        char sortedListProfessor[max_tam][max_nome];

        copiarProfessor(listaProfessor, sortedListProfessor, qtdProfessor);
        quicksort(sortedListProfessor, qtdProfessor);

        for(int j = 0; j < qtdProfessor; j++) {
          printf("Nome: %s", sortedListProfessor[j]);
        }
      break;

      case 2:
        printf("----------------------------------------\n");
        printf("| Lista de Professores por nascimento: |\n");
        printf("| %d professor(es) cadastrado(s)        |\n", qtdProfessor);
        printf("----------------------------------------\n");

        ordenarData sortedListDataProfessor[max_tam];

        copiarProfessorData(listaProfessor, sortedListDataProfessor, qtdProfessor);
        quicksortData(sortedListDataProfessor, qtdProfessor);

        for(int j = 0; j < qtdProfessor; j++) {
          printf("Nome: %s",                sortedListDataProfessor[j].Nome);
          printf("Data de nascimento: %d/", sortedListDataProfessor[j].idade[0]);
          printf("%d/",                     sortedListDataProfessor[j].idade[1]);
          printf("%d\n",                    sortedListDataProfessor[j].idade[2]);
          printf("----------------------------------------\n");
        }
      break;

      case 3:
        printf("Digite o sexo: ");
        scanf("%c", &sexo);

        sexo = char_captilize (sexo);

        if(sexo != 'F' && sexo != 'M') {
            printf("Digite um sexo válido!\n");
        } else {
          printf("----------------------------------------\n");
          printf("| Lista de Alunos por sexo:             |\n");
          printf("----------------------------------------\n");

          for(int i = 0; i < qtdProfessor; i++){
            if(listaProfessor[i].Sexo == sexo){
              printf("Nome: %s", listaProfessor[i].Nome);
              printf("Matricula: %d", listaProfessor[i].Matricula);
               printf("----------------------------------------\n");
            }
          }
        }
      break;
      case 4:

        printf("Digite o mes: ");  
        scanf("%d", &mes);
        getchar();
        if(mes < 1 || mes > 12){
          printf("Mes invalido!\n");
        } else{
        printf("----------------------------------------\n");
        printf("| Aniversariantes do mês:               |\n");
        printf("----------------------------------------\n");

        for(int i = 0; i < qtdProfessor; i++){
          if(listaProfessor[i].idade[1] == mes){
            printf("Nome: %s", listaProfessor[i].Nome);
            printf("Matricula: %d\n", listaProfessor[i].Matricula);
            printf("Data de nascimento: %d/", listaProfessor[i].idade[0]);
            printf("%d\n", listaProfessor[i].idade[1]);
            printf("----------------------------------------\n");
          }
        }
      }
      break;
      default:
        printf("Opção inválida");
      break;
    }
  }
}

int ExcluirProfessor(Professor listaProfessor[], int qtdProfessor) {

  int excluir;

  if (qtdProfessor == 0) {
    printf("Não há Professor(es) cadastrado(s)!\n");
    return EXCLUIR_FALHOU;
  }else {
    printf("-----------------------------------\n");
    printf("| Excluir Professor:              |\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < qtdProfessor; i++) {
      printf("Digite %d para excluir: %s", i, listaProfessor[i].Nome);
    }
    scanf("%d", &excluir);
    getchar();
    while (excluir < qtdProfessor) {
        listaProfessor[excluir] = listaProfessor[excluir+1];
      excluir++;
    }
    return CADASTRO_EXCLUIDO;
  }
}

int atualizarProfessor(Professor listaProfessor[], int qtdProfessor) {

  int atualizar;
  int selecionar;

  if (qtdProfessor == 0) {
    printf("Não há Professor(es) cadastrado(s)!\n");
    return ATUALIZAR_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Atualizar Professor:                 |\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < qtdProfessor; i++) {
      printf("Digite %d para Atualizar: %s", i, listaProfessor[i].Nome);
    }
    scanf("%d", &atualizar);
    getchar();

    printf("----------------------------------------\n");
    printf("Atualizar Professor(a): %s\n", listaProfessor[atualizar].Nome);
    printf("Digite 0 para Atualizar o Nome\n");
    printf("Digite 1 para Atualizar o CPF\n");
    printf("Digite 2 para Atualizar o Matricula\n");
    printf("Digite 3 para Atualizar o Sexo\n");
    printf("Digite 4 para Atualizar a Data de Nascimento\n");

    scanf("%d", &selecionar);
    getchar();

    switch (selecionar) {
      case 0:
          printf("Digite o novo Nome:");
          fgets(listaProfessor[atualizar].Nome, max_nome, stdin);
        fflush(stdin);
      break;
      case 1:
         validarCpfProfessor(listaProfessor, atualizar);
      break;
      case 2:
         validarMatriculaProfessor(listaProfessor, atualizar);
      break;
      case 3:
         validarSexoProfessor(listaProfessor, atualizar);
      break;
      case 4:
          DataNascimentoProfessor(listaProfessor, atualizar);
      break;
    }
    return CADASTRO_ATUALIZADO;
  }
}

int DataNascimentoProfessor(Professor listaProfessor[], int atualizar) {

  int valido = 1;

    while(valido == 1) {

      printf("Digite o dia de nascimento: ");
      scanf("%d", &listaProfessor[atualizar].idade[0]);
      getchar();

      printf( "Digite o mes de nascimento: ");
      scanf("%d", &listaProfessor[atualizar].idade[1]);
      getchar();

      printf("Digite o ano de nascimento: ");
      scanf("%d", &listaProfessor[atualizar].idade[2]);
      getchar();

      if (listaProfessor[atualizar].idade[0] <= 0 || listaProfessor[atualizar].idade[0] > 31) {
        printf("Por favor entre um dia válido\n");

      }else if (listaProfessor[atualizar].idade[1] <= 0 || listaProfessor[atualizar].idade[1] > 12) {
        printf("Por favor entre um mes válido\n");

      }else if (listaProfessor[atualizar].idade[2] < 1900 || listaProfessor[atualizar].idade[2] > 2024) {
        printf("Por favor entre um ano válido\n");

      }else {
        valido = 0;
        fprintf (arquivoProfessor, "Data de Nascimento: ");
        for (int i = 0; i < data; i++) {
          if (i != 2) {
            fprintf (arquivoProfessor, "%d/", listaProfessor[qtdProfessor].idade[i]);
          }else 
            fprintf (arquivoProfessor, "%d\n", listaProfessor[qtdProfessor].idade[i]);
        }
      }
   }
  return 0;
}

int validarMatriculaProfessor( Professor listaProfessor[], int qtdProfessor) {
    int valido = 1;

    while (valido == 1) {
        printf("\nDigite o numero da Matricula: ");
        if (scanf("%d", &listaProfessor[qtdProfessor].Matricula) != true) {
            printf("Digite uma matricula válida!\n");
            while (getchar() != '\n'); 
            continue;
        }

        if (listaProfessor[qtdProfessor].Matricula <= 0 || listaProfessor[qtdProfessor].Matricula > 9999999) {
            printf("Digite uma matricula válida!\n");
        } else {
            int matriculaExistente = 0;
            for (int i = 0; i < qtdProfessor; i++) {
                if (listaProfessor[i].Matricula == listaProfessor[qtdProfessor].Matricula) {
                    matriculaExistente = true;
                    break;
                }
            }
            if (matriculaExistente) {
              printf("Esta matricula ja esta sendo utilizada!\n");
            } else {
              valido = 0;
              fprintf (arquivoProfessor, "Matricula: %d\n", listaProfessor[qtdProfessor].Matricula);
            }
        }
    }
    return 0;
}

int validarSexoProfessor(Professor listaProfessor[], int qtdProfessor) {

  int valido = 1;

  while(valido == 1) {
    printf("Digite o Sexo(F/M): ");
    scanf(" %c", &listaProfessor[qtdProfessor].Sexo); 
    getchar();

    if(listaProfessor[qtdProfessor].Sexo != 'F' && listaProfessor[qtdProfessor].Sexo != 'f' &&
      listaProfessor[qtdProfessor].Sexo != 'M' && listaProfessor[qtdProfessor].Sexo != 'm') {
        printf("Digite um sexo válido!\n");
    } else {
        valido = 0;
    }
  }
  char_captilize_Professor(listaProfessor, qtdProfessor);
  fprintf (arquivoProfessor, "Sexo: %c\n", listaProfessor[qtdProfessor].Sexo);

  return 0; 
}

int validarCpfProfessor(Professor listaProfessor[], int qtdProfessor) {
    int valido = 1;
    int soma1, soma2, resto1, resto2;
    int digitos[11];

    while (valido == 1) {
        printf("Digite o CPF: ");
        fgets(listaProfessor[qtdProfessor].CPF, max_CPF, stdin);

        int i;
        for (i = 0; i < 11; i++) {
            if (listaProfessor[qtdProfessor].CPF[i] < '0' || listaProfessor[qtdProfessor].CPF[i] > '9') {
                printf("Digite um CPF válido.\n");
                break;
            }
            digitos[i] = listaProfessor[qtdProfessor].CPF[i] - '0';
        }
        if (i < 11) {
            continue; 
        }

        int icont = 1;
        for (i = 0; i < 10; i++) {
            if (digitos[i] == digitos[i + 1]) {
                icont++;
            } else {
                icont = 1;
            }
            if (icont > 5) {
                printf("CPF inválido devido a dígitos repetidos.\n");
                valido = 1;
                break;
            }
        }
        if (icont > 5) {
            continue;
        }
        soma1 = 0;
        for (i = 0; i < 9; i++) {
            soma1 += digitos[i] * (10 - i);
        }
        resto1 = (soma1 * 10) % 11;
        if (resto1 == 10) {
            resto1 = 0;
        }
        soma2 = 0;
        for (i = 0; i < 10; i++) {
            soma2 += digitos[i] * (11 - i);
        }
        resto2 = (soma2 * 10) % 11;
        if (resto2 == 10) {
            resto2 = 0;
        }
        if (resto1 == digitos[9] && resto2 == digitos[10]) {
          valido = 0;
          fprintf (arquivoProfessor, "CPF: %s\n", listaProfessor[qtdProfessor].CPF);
        } else {
          printf("CPF inválido.\n");
        }
    }

    return 0;
}

int validarNomeProfessor(Professor listaProfessor[], int qtdProfessor) {

  int valido = 1;

  printf("Digite o nome completo: ");
  getchar();

  while (valido == 1) {

    fgets(listaProfessor[qtdProfessor].Nome, max_nome, stdin);

    char teste = listaProfessor[qtdProfessor].Nome[0];
    if ((teste >= 'A' && teste <= 'Z') || (teste >= 'a' && teste <= 'z')) {
      valido = 0;
    } else {
      printf("Digite um nome válido: ");

    }
  }
  string_captilize_Professor (listaProfessor, qtdProfessor);
  fprintf (arquivoProfessor, "Professor: %s", listaProfessor[qtdProfessor].Nome);

  return 0;
}

void string_captilize_Professor (Professor listaProfessor[], int qtdProfessor) {

  for (int i = 0; listaProfessor[qtdProfessor].Nome[i] != '\0'; i++) {
    if ((listaProfessor[qtdProfessor].Nome[i] >= 'a' && listaProfessor[qtdProfessor].Nome[i] <= 'z')
         && listaProfessor[qtdProfessor].Nome[i] != ' ') {

        listaProfessor[qtdProfessor].Nome[i] = listaProfessor[qtdProfessor].Nome[i] - 32;
    }
  }
}

void char_captilize_Professor (Professor listaProfessor[], int qtdProfessor) {

  if (listaProfessor[qtdProfessor].Sexo >= 'a' && listaProfessor[qtdProfessor].Sexo <= 'z') {

      listaProfessor[qtdProfessor].Sexo = listaProfessor[qtdProfessor].Sexo - 32;
  }
}

char char_captilize (char sexo) {

  if (sexo >= 'a' && sexo <= 'z')
    sexo -= 32;

  return sexo;
}

void quicksort(char sortedList[][max_nome], int qtdProfessor) {
  quicksort_recursion(sortedList, 0, qtdProfessor-1);
}

void quicksort_recursion(char sortedList[][max_nome],int menor_index, int qtdProfessor) {

  if (menor_index < qtdProfessor) {
    int pivot_index = partition(sortedList, menor_index, qtdProfessor);
    quicksort_recursion(sortedList, menor_index, pivot_index-1);
    quicksort_recursion(sortedList, pivot_index+1, qtdProfessor);
  }
}

int partition (char sortedList[][max_nome], int menor_index, int qtdProfessor) {

  char pivot[max_nome];
  strcpy(pivot, sortedList[qtdProfessor]);
  int i = menor_index;
  int j;

  for (j = menor_index; j < qtdProfessor; j++) {

    if (strcmp(sortedList[j], pivot) < 0) {
      if (j > i) {
        char temp[max_nome];
        strcpy(temp, sortedList[i]);
        strcpy(sortedList[i], sortedList[j]);
        strcpy(sortedList[j], temp);
      }
      i++;
    }
  }
  char temp[max_nome];
  strcpy(temp, sortedList[i]);
  strcpy(sortedList[i], sortedList[qtdProfessor]);
  strcpy(sortedList[j], temp);
  return i;
}

void copiarProfessor(Professor listaProfessor[], char sortedList[][max_nome], int qtdProfessor) {
  for (int i = 0; i < qtdProfessor; i++) {
    strcpy(sortedList[i], listaProfessor[i].Nome);
  }
}

void copiarProfessorData(Professor listaProfessor[], ordenarData sortedListData[], int qtdProfessor) {
  for (int i = 0; i < qtdProfessor; i++) {
    strcpy(sortedListData[i].Nome, listaProfessor[i].Nome);
    sortedListData[i].idade[0] = listaProfessor[i].idade[0];
    sortedListData[i].idade[1] = listaProfessor[i].idade[1];
    sortedListData[i].idade[2] = listaProfessor[i].idade[2];
  }
}

void quicksortData(ordenarData sortedListData[], int qtdProfessor) {
  quicksort_recursionData(sortedListData, 0, qtdProfessor-1);
}

void quicksort_recursionData(ordenarData sortedListData[],int menor_index, int qtdProfessor) {

  if (menor_index < qtdProfessor) {
    int pivot_index = partitionData(sortedListData, menor_index, qtdProfessor);
    quicksort_recursionData(sortedListData, menor_index, pivot_index-1);
    quicksort_recursionData(sortedListData, pivot_index+1, qtdProfessor);
  }
}

int partitionData(ordenarData sortedListData[], int menor_index, int qtdProfessor) {

  char pivotNome[max_nome];
  strcpy(pivotNome, sortedListData[qtdProfessor].Nome);
  int i = menor_index;
  int j;
  int pivot[data];
  for(int k = 0; k < 3; k++){
      pivot[k] = sortedListData[qtdProfessor].idade[k];
  }


  for (j = menor_index; j < qtdProfessor; j++) {

      if (sortedListData[j].idade[2] < pivot[2]) {
        if (j > i) {
        char temp[50];
        strcpy(temp, sortedListData[i].Nome);
        strcpy(sortedListData[i].Nome, sortedListData[j].Nome);
        strcpy(sortedListData[j].Nome, temp);
          for(int k = 0; k < 3; k++){
            int arrTemp[3];
            arrTemp[k] = sortedListData[i].idade[k];
            sortedListData[i].idade[k] = sortedListData[j].idade[k];
            sortedListData[j].idade[k] = arrTemp[k];
          }
        }
        i++;
      }else if (sortedListData[j].idade[2] == pivot[2]) {
              if (sortedListData[j].idade[1] < pivot[1]) {
                if (j > i) {
                  char temp[50];
                  strcpy(temp, sortedListData[i].Nome);
                  strcpy(sortedListData[i].Nome, sortedListData[j].Nome);
                  strcpy(sortedListData[j].Nome, temp);
                  for(int k = 0; k < 3; k++){
                    int arrTemp[3];
                    arrTemp[k] = sortedListData[i].idade[k];
                    sortedListData[i].idade[k] = sortedListData[j].idade[k];
                    sortedListData[j].idade[k] = arrTemp[k];
                  }
                }
                i++;
              }else if (sortedListData[j].idade[1] == pivot[1]) {
                  if (sortedListData[j].idade[0] <= pivot[0]) {
                    if (j > i) {
                      char temp[50];
                      strcpy(temp, sortedListData[i].Nome);
                      strcpy(sortedListData[i].Nome, sortedListData[j].Nome);
                      strcpy(sortedListData[j].Nome, temp);
                      for(int k = 0; k < 3; k++){
                        int arrTemp[3];
                        arrTemp[k] = sortedListData[i].idade[k];
                        sortedListData[i].idade[k] = sortedListData[j].idade[k];
                        sortedListData[j].idade[k] = arrTemp[k];
                      }
                    }
                  i++;
                  }
                }
              }
            }
  char temp[max_nome];
  strcpy(temp, sortedListData[i].Nome);
  strcpy(sortedListData[i].Nome, sortedListData[qtdProfessor].Nome);
  strcpy(sortedListData[j].Nome, temp);
  for(int k = 0; k < 3; k++){
    int arrTemp[3];
    arrTemp[k] = sortedListData[i].idade[k];
    sortedListData[i].idade[k] = sortedListData[qtdProfessor].idade[k];
    sortedListData[j].idade[k] = arrTemp[k];
  }
  return i;
}