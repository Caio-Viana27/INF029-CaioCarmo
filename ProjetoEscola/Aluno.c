#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Aluno.h"
#define max_nome 50
#define max_CPF 12
#define max_tam 5
#define data 3
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
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int ExcluirAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);

int DataNascimentoAluno(Aluno listaAluno[], int qtdAluno);
int validarMatriculaAluno(Aluno listaAluno[], int qtdAluno);
int validarSexoAluno(Aluno listaAluno[], int qtdAluno);
int validarCpfAluno(Aluno listaAluno[], int qtdAluno);
int validarNomeAluno(Aluno listaAluno[], int qtdAluno);
void string_captilize_Aluno (Aluno listaAluno[], int qtdAluno);
void char_captilize_Aluno (Aluno listaAluno[], int qtdAluno);
char char_captilize (char sexo);

void quicksort(char sortedList[][max_nome], int qtdAluno);
void quisort_recursion(char sortedList[][max_nome],int menor_index, int qtdAluno);
int partition(char sortedList[][max_nome],int menor_index, int qtdAluno);
void copiarAluno(Aluno listaAluno[], char sortedList[][max_nome], int qtdAluno);
void copiarAlunoData(Aluno listaAluno[], ordenarData sortedListData[], int qtdAluno);
void quicksortData(ordenarData sortedListData[], int qtdAluno);
void quisort_recursionData(ordenarData sortedListData[],int menor_index, int qtdAluno);
int partitionData(ordenarData sortedListData[],int menor_index, int qtdAluno);

Aluno listaAluno[max_tam];
int qtdAluno = 0;

FILE *arquivoAluno;

int menuAluno() {

  arquivoAluno = fopen("Aluno.txt", "w");
  if (arquivoAluno == NULL) {
    printf("Falha ao abrir o arquivo!\n");
  }

  int opcao;

  printf("----------------------------------------\n");
  printf("|  Menu Aluno:                         |\n");
  printf("|  Aluno(s) cadastrado(s): %d           |\n", qtdAluno);
  printf("----------------------------------------\n");
  printf("|  0 - Voltar                          |\n");
  printf("|  1 - Cadastrar Aluno                 |\n");
  printf("|  2 - Atualizar Aluno                 |\n");
  printf("|  3 - Excluir Aluno                   |\n");
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
        opcao = cadastrarAluno(listaAluno, qtdAluno);
        if (opcao == CADASTRO_SUCESSO) {
          qtdAluno += 1;
        printf("Aluno(a) cadastrado(a) com sucesso!\n");
        }else if (opcao == CADASTRO_FALHOU) {
          printf("Nao foi possivel cadastrar o aluno!\n");
        }
        if(opcao == CADASTRO_SUCESSO || opcao == CADASTRO_FALHOU)
        opcao = menuAluno(qtdAluno);
        fclose(arquivoAluno);
        break;

    case 2:
        opcao = atualizarAluno(listaAluno, qtdAluno);
        if (opcao == CADASTRO_ATUALIZADO) {
          printf("Aluno(a) Atualizado(a) com sucesso!\n");
        }else if (opcao == ATUALIZAR_FALHOU) {
          printf("Nao foi possivel Atualizar o aluno!\n");
        }         
        if(opcao == CADASTRO_ATUALIZADO || opcao == ATUALIZAR_FALHOU)
          opcao = menuAluno(qtdAluno);
        break;

    case 3:
        opcao = ExcluirAluno(listaAluno, qtdAluno);
        if (opcao == CADASTRO_EXCLUIDO) {
          qtdAluno--;
          printf("Aluno(a) excluido(a) com sucesso!\n");
        }else if (opcao == EXCLUIR_FALHOU) {
          printf("Nao foi possivel excluir o aluno!\n");
        }
        if(opcao == CADASTRO_EXCLUIDO || opcao == EXCLUIR_FALHOU)
        opcao = menuAluno(qtdAluno);
        break;

    case 4:
        listarAluno(listaAluno, qtdAluno);
        menuAluno(qtdAluno);
        break;
    default:
      printf("Opçao invalida");
    break;
  }
  return opcao;
}

int cadastrarAluno(Aluno listaAluno[], int qtdAluno) {

  int sair = 1;

  if (qtdAluno < max_tam) {

    while(sair != 0) {

      validarMatriculaAluno(listaAluno, qtdAluno); 

      validarNomeAluno(listaAluno, qtdAluno);

      validarSexoAluno(listaAluno, qtdAluno);

      validarCpfAluno(listaAluno, qtdAluno); 

      DataNascimentoAluno(listaAluno, qtdAluno); 

      listaAluno[qtdAluno].qtdMaterias = 0;

      sair = 0;
    }
    return CADASTRO_SUCESSO;
  }else {
    printf("Lista de alunos cheia!\n");
    return CADASTRO_FALHOU;
  }
}

void listarAluno(Aluno listaAluno[], int qtdAluno) {
   int mes;
   int selecionar;
   char sexo;

   if (qtdAluno == 0) {
    printf("Nao ha Aluno(s) cadastrado(s)!\n");
  }else {

    printf("----------------------------------------\n");
    printf("|  Lista Alunos:                       |\n");
    printf("|  Aluno(s) cadastrado(s): %d           |\n", qtdAluno);
    printf("----------------------------------------\n");
    printf("|  0 - listar Alunos                   |\n");
    printf("|  1 - listar Alunos por Nome          |\n");
    printf("|  2 - listar Alunos por Nascimento    |\n");
    printf("|  3 - listar Alunos pro sexo          |\n");
    printf("|  4 - listar aniversariantes do mes   |\n");
    printf("|  5 - listar Alunos com +3 materias   |\n");
    printf("----------------------------------------\n");
    scanf("%d", &selecionar);
    getchar();

    switch (selecionar) {

      case 0:
        printf("----------------------------------------\n");
        printf("| Lista de Alunos:                     |\n");
        printf("| %d Alunos(s) cadastrado(s)            |\n", qtdAluno);
        printf("----------------------------------------\n");

          for(int i = 0; i < qtdAluno; i++) {

          printf("Nome: %s",                listaAluno[i].Nome);
          printf("CPF: %s\n",               listaAluno[i].CPF);
          printf("Matricula: %d\n",         listaAluno[i].Matricula);
          printf("Sexo: %c\n",              listaAluno[i].Sexo);
          printf("Data de nascimento: %d/", listaAluno[i].idade[0]);
          printf("%d/",                     listaAluno[i].idade[1]);
          printf("%d\n",                    listaAluno[i].idade[2]);
          printf("Matriculado em: %d\n",    listaAluno[i].qtdMaterias);
          printf("----------------------------------------\n");
          }
      break;

      case 1:
        printf("----------------------------------------\n");
        printf("| Lista de Aluno por Nome:             |\n");
        printf("| %d Aluno(s) cadastrado(s)             |\n", qtdAluno);
        printf("----------------------------------------\n");

        char sortedListAluno[max_tam][max_nome];

        copiarAluno(listaAluno, sortedListAluno, qtdAluno);
        quicksort(sortedListAluno, qtdAluno);

        for(int j = 0; j < qtdAluno; j++) {
          printf("Nome: %s", sortedListAluno[j]);
        }
      break;

      case 2:
        printf("----------------------------------------\n");
        printf("| Lista de Alunos por nascimento:      |\n");
        printf("| %d Aluno(s) cadastrado(s)             |\n", qtdAluno);
        printf("----------------------------------------\n");

        ordenarData sortedListDataAluno[max_tam];

        copiarAlunoData(listaAluno, sortedListDataAluno, qtdAluno);
        quicksortData(sortedListDataAluno, qtdAluno);

        for(int j = 0; j < qtdAluno; j++) {
          printf("Nome: %s",                sortedListDataAluno[j].Nome);
          printf("Data de nascimento: %d/", sortedListDataAluno[j].idade[0]);
          printf("%d/",                     sortedListDataAluno[j].idade[1]);
          printf("%d\n",                    sortedListDataAluno[j].idade[2]);
          printf("----------------------------------------\n");
        }
      break;

      case 3:
        printf("Digite o sexo: ");
        scanf("%c", &sexo);
        getchar();

        sexo = char_captilize (sexo);

        if(sexo != 'F' && sexo != 'M') {
            printf("Digite um sexo váalido!\n");
        } else {

          printf("----------------------------------------\n");
          printf("| Lista de Alunos por sexo:            |\n");
          printf("----------------------------------------\n");

          for(int i = 0; i < qtdAluno; i++){
            if(listaAluno[i].Sexo == sexo){
              printf("Nome: %s", listaAluno[i].Nome);
              printf("Matricula: %d\n", listaAluno[i].Matricula);
              printf("----------------------------------------\n");
            }
          }
        }
      break;

      case 4:
        printf("Digite o mes: ");  
        scanf("%d", &mes);
        getchar();
        if (mes < 1 || mes > 12) {
          printf("Mes invalido!\n");
        } else {
          printf("----------------------------------------\n");
          printf("| Aniversariantes do mes:              |\n");
          printf("----------------------------------------\n");

          for(int i = 0; i < qtdAluno; i++){

            if (listaAluno[i].idade[1] == mes) {
              printf("Nome: %s",                listaAluno[i].Nome);
              printf("Matricula: %d\n",         listaAluno[i].Matricula);
              printf("Data de nascimento: %d/", listaAluno[i].idade[0]);
              printf("%d\n",                    listaAluno[i].idade[1]);
              printf("----------------------------------------\n");
            }
          }
        }
      break;

      case 5:
        printf("----------------------------------------\n");
          printf("| Alunos matriculados em +3 materias:  |\n");
          printf("----------------------------------------\n");

        for (int i = 0; i < qtdAluno; i++) {
          if (listaAluno[i].qtdMaterias < 3) {
            printf("Nome: %s",             listaAluno[i].Nome);
            printf("Matriculado em: %d\n", listaAluno[i].qtdMaterias);
          }
        }
      break;
      default:
        printf("Opção invalida");
      break;
    }
  }
}

int ExcluirAluno(Aluno listaAluno[], int qtdAluno) {

  int excluir;

  if (qtdAluno == 0) {
    printf("Nao ha aluno(s) cadastrado(s)!\n");
    return EXCLUIR_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Excluir Aluno:                       |\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < qtdAluno; i++) {
      printf("Digite %d para excluir: %s", i, listaAluno[i].Nome);
    }
    scanf("%d", &excluir);
    getchar();
    while (excluir < qtdAluno) {
      listaAluno[excluir] = listaAluno[excluir+1];
      excluir++;
    }
    return CADASTRO_EXCLUIDO;
  }
}

int atualizarAluno(Aluno listaAluno[], int qtdAluno) {

  int atualizar;
  int selecionar;

  if (qtdAluno == 0) {
    printf("Nao ha aluno(s) cadastrado(s)!\n");
    return ATUALIZAR_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Atualizar Aluno:                     |\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < qtdAluno; i++) {
      printf("Digite %d para Atualizar: %s", i, listaAluno[i].Nome);
    }
    scanf("%d", &atualizar);
    getchar();

    printf("----------------------------------------\n");
    printf("Atualizar Aluno(a): %s\n", listaAluno[atualizar].Nome);
    printf("Digite 0 para Atualizar o Nome\n");
    printf("Digite 1 para Atualizar o CPF\n");
    printf("Digite 2 para Atualizar o Matricula\n");
    printf("Digite 3 para Atualizar o Sexo\n");
    printf("Digite 4 para Atualizar a Data de Nascimento\n");

    scanf("%d", &selecionar);
    getchar();

    switch (selecionar) {
      case 0:
       validarNomeAluno(listaAluno, atualizar);
      break;
      case 1:
       validarCpfAluno(listaAluno, atualizar);
      break;
      case 2:
       validarMatriculaAluno(listaAluno, atualizar);
      break;
      case 3:
       validarSexoAluno(listaAluno, atualizar);
      break;
      case 4:
       DataNascimentoAluno(listaAluno, atualizar);
      break;
      default:
          printf("Opçao invalida!\n");
          atualizarAluno(listaAluno, qtdAluno);
      break;
    }
    return CADASTRO_ATUALIZADO;
  }
}

int DataNascimentoAluno(Aluno listaAluno[], int qtdAluno) {

  int valido = 1;

    while(valido == 1) {

      printf("Digite o dia de nascimento: ");
      scanf("%d", &listaAluno[qtdAluno].idade[0]);
      getchar();

      printf( "Digite o mes de nascimento: ");
      scanf("%d", &listaAluno[qtdAluno].idade[1]);
      getchar();

      printf("Digite o ano de nascimento: ");
      scanf("%d", &listaAluno[qtdAluno].idade[2]);
      getchar();

      if (listaAluno[qtdAluno].idade[0] <= 0 || listaAluno[qtdAluno].idade[0] > 31) {
        printf("Por favor entre um dia valido\n");

      }else if (listaAluno[qtdAluno].idade[1] <= 0 || listaAluno[qtdAluno].idade[1] > 12) {
        printf("Por favor entre um mes valido\n");

      }else if (listaAluno[qtdAluno].idade[2] < 1900 || listaAluno[qtdAluno].idade[2] > 2024) {
        printf("Por favor entre um ano valido\n");

      }else {
        valido = 0;
        fprintf (arquivoAluno, "Data de Nascimento: ");
        for (int i = 0; i < data; i++) {
          if (i != 2) {
            fprintf (arquivoAluno, "%d/", listaAluno[qtdAluno].idade[i]);
          }else 
            fprintf (arquivoAluno, "%d\n", listaAluno[qtdAluno].idade[i]);
        }
      } 
   }
  return 0;
}

int validarMatriculaAluno( Aluno listaAluno[], int qtdAluno) {
    int valido = 1;

    while (valido == 1) {
      printf("\nDigite o numero da Matricula: ");
      if (scanf("%d", &listaAluno[qtdAluno].Matricula) != true) {
        printf("Digite uma matricula valida!\n");
        while (getchar() != '\n'); 
        continue;
      }
      if (listaAluno[qtdAluno].Matricula <= 0 || listaAluno[qtdAluno].Matricula > 9999999) {
          printf("Digite uma matricula valida!\n");
      }else {
        int matriculaExistente = 0;
        for (int i = 0; i < qtdAluno; i++) {
          if (listaAluno[i].Matricula == listaAluno[qtdAluno].Matricula) {
            matriculaExistente = true;
            break;
          }
        }
        if (matriculaExistente) {
          printf("Esta matricula ja esta sendo utilizada!\n");
        }else {
          valido = 0;
          fprintf (arquivoAluno, "Matricula: %d\n", listaAluno[qtdAluno].Matricula);
        }
      }
    }
    return 0;
}

int validarSexoAluno(Aluno listaAluno[], int qtdAluno) {
    int valido = 1;

    while(valido == 1) {
      printf("Digite o Sexo(F/M): ");
      scanf("%c", &listaAluno[qtdAluno].Sexo); 
      getchar();


      if(listaAluno[qtdAluno].Sexo != 'F' && listaAluno[qtdAluno].Sexo != 'f' &&
         listaAluno[qtdAluno].Sexo != 'M' && listaAluno[qtdAluno].Sexo != 'm') {
          printf("Digite um sexo valido!\n");
      } else {
          valido = 0;
      }
    }

  char_captilize_Aluno (listaAluno, qtdAluno);
  fprintf (arquivoAluno, "Sexo: %c\n", listaAluno[qtdAluno].Sexo);

  return 0; 
}

int validarCpfAluno(Aluno listaAluno[], int qtdAluno) {
    int valido = 1;
    int soma1, soma2, resto1, resto2;
    int digitos[11];

    while (valido == 1) {
        printf("Digite o CPF: ");
        fgets(listaAluno[qtdAluno].CPF, max_CPF, stdin);

        int i;
        for (i = 0; i < 11; i++) {
            if (listaAluno[qtdAluno].CPF[i] < '0' || listaAluno[qtdAluno].CPF[i] > '9') {
                printf("Digite apenas numeros.\n");
                break;
            }
            digitos[i] = listaAluno[qtdAluno].CPF[i] - '0';
        }
        if (i < 11) {
            continue; 
        } else {
          int CPFExistente = 0;

          for (int i = 0; i < qtdAluno; i++) {
              if (listaAluno[i].CPF == listaAluno[qtdAluno].CPF) {
                  CPFExistente = 1;
                  break;
              }
          }
      if (CPFExistente) {
          printf("Este CPF ja esta sendo utilizado!\n");
          valido = 1;
          break;
      }
        } 
        int icont = 1;
        for (i = 0; i < 10; i++) {
            if (digitos[i] == digitos[i + 1]) {
                icont++;
            } else {
                icont = 1;
            }
            if (icont > 5) {
                printf("CPF invalido devido a digitos repetidos.\n");
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
            fprintf (arquivoAluno, "CPF: %s\n", listaAluno[qtdAluno].CPF);
        } else {
            printf("CPF invalido.\n");
        }
    }
    return 0;
}

int validarNomeAluno(Aluno listaAluno[], int qtdAluno) {

  int valido = 1;

  printf("Digite o nome completo: ");
  getchar();

  while (valido == 1) {

      fgets(listaAluno[qtdAluno].Nome, max_nome, stdin);

      char teste = listaAluno[qtdAluno].Nome[0];
      if ((teste >= 'A' && teste <= 'Z') || (teste >= 'a' && teste <= 'z')) {
        valido = 0;
      } else {
        printf("Digite um nome valido: ");

      }
  }
  string_captilize_Aluno (listaAluno, qtdAluno);

  fprintf(arquivoAluno, "Aluno: %s", listaAluno[qtdAluno].Nome);

  return 0;
}

void string_captilize_Aluno (Aluno listaAluno[], int qtdAluno) {

  for (int i = 0; listaAluno[qtdAluno].Nome[i] != '\0'; i++) {

    if ((listaAluno[qtdAluno].Nome[i] >= 'a' && listaAluno[qtdAluno].Nome[i] <= 'z')
         && listaAluno[qtdAluno].Nome[i] != ' ') {

      listaAluno[qtdAluno].Nome[i] = listaAluno[qtdAluno].Nome[i] - 32;
    }
  }
}

void char_captilize_Aluno (Aluno listaAluno[], int qtdAluno) {

  if (listaAluno[qtdAluno].Sexo >= 'a' && listaAluno[qtdAluno].Sexo <= 'z') {

    listaAluno[qtdAluno].Sexo = listaAluno[qtdAluno].Sexo - 32;
  }
}

void copiarAluno(Aluno listaAluno[], char sortedListAluno[][max_nome], int qtdAluno) {
  for (int i = 0; i < qtdAluno; i++) {
    strcpy(sortedListAluno[i], listaAluno[i].Nome);
  }
}

void copiarAlunoData(Aluno listaAluno[], ordenarData sortedListData[], int qtdAluno) {
  for (int i = 0; i < qtdAluno; i++) {
    strcpy(sortedListData[i].Nome, listaAluno[i].Nome);
    sortedListData[i].idade[0] = listaAluno[i].idade[0];
    sortedListData[i].idade[1] = listaAluno[i].idade[1];
    sortedListData[i].idade[2] = listaAluno[i].idade[2];
  }
}