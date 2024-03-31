#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disciplina.h"
#define max_nome 50
#define max_CPF 12
#define max_tam 5
#define data 3
#define max_semestre 7
#define CADASTRO_SUCESSO -1
#define CADASTRO_FALHOU -2
#define CADASTRO_ATUALIZADO -3
#define ATUALIZAR_FALHOU -4
#define CADASTRO_EXCLUIDO -5
#define EXCLUIR_FALHOU -6

int menuPrincipal();
void listarPessoas (Aluno listaAluno[], int qtdAluno, Professor listaProfessor[], int qtdProfessor);
void copiarAluno(Aluno listaAluno[], char sortedListAluno[][max_nome], int qtdAluno);
void copiarProfessor(Professor listaProfessor[], char sortedListProfessor[][max_nome], int qtdProfessor);
int Search_string (char string[], char substring[]);
void substring_captilize (char substring[]);

extern Aluno listaAluno[max_tam];
extern int qtdAluno;
extern Professor listaProfessor[max_tam];
extern int qtdProfessor;

int main(void) {

  int opcao;

  while(opcao!=0){

    opcao = menuPrincipal();

      switch (opcao)
      { 
        case 0:
        break;
        case 1:
          opcao = menuAluno();
        break;
        case 2:
            opcao = menuProfessor();
        break;
        case 3:
            opcao = menuDisciplina();
        break;
        case 4:
            listarPessoas (listaAluno, qtdAluno, listaProfessor, qtdProfessor);
        break;
        default:
          printf("Opção inválida");
        break;
      }
  }
  return 0;
}

int menuPrincipal() {

  int opcao; 

  printf("----------------------------------------\n");
  printf("|  Menu Principal:                     |\n");
  printf("----------------------------------------\n");
  printf("|  0 - Sair                            |\n");
  printf("|  1 - Aluno                           |\n");
  printf("|  2 - Professor                       |\n");
  printf("|  3 - Disciplina                      |\n");
  printf("|  4 - Buscar Pessoas                  |\n");
  printf("----------------------------------------\n");
  scanf("%d", &opcao);
  system("clear");


  return opcao;
}

void listarPessoas (Aluno listaAluno[], int qtdAluno, Professor listaProfessor[], int qtdProfessor) {

  if (qtdAluno == 0 && qtdProfessor == 0) {
    printf("Não há nenhuma pessoa cadastrada!\n");
  }else {
    
    char substring[max_nome];

    char listaTempAluno[max_tam][max_nome];
    char listaTempProfessor[max_tam][max_nome];

   copiarAluno(listaAluno, listaTempAluno, qtdAluno);
   copiarProfessor(listaProfessor, listaTempProfessor, qtdProfessor);

    printf("----------------------------------------\n");
    printf("|  Digite no mínimo 3 letras:          |\n");
    printf("----------------------------------------\n");
    
    getchar();
    printf("Nome: ");
    fgets(substring, max_nome, stdin);
    
    substring_captilize (substring);
    
    printf("----------------------------------------\n");
    printf("|  Lista de pessoas:                   | \n");
    printf("----------------------------------------\n");

    
    
    for (int i = 0; i < qtdAluno; i++) {
 
      if (Search_string (listaTempAluno[i], substring) == 1) {
         printf("Aluno: %s\n", listaTempAluno[i]);
      }
    }
    
    for (int i = 0; i < qtdProfessor; i++) {
    
      if (Search_string (listaTempProfessor[i], substring) == 1) {
        printf("Professor: %s\n", listaTempProfessor[i]);
      }
    }
  }
}

int Search_string (char string[], char substring[]) {

  int found = 0;
  int i;

for (i = 0; i < 3; i++) {
    if (string[i] == substring[i]) {
      found = 1;
    } else {
      found = 0;
    }
  }
  return found;
}

void substring_captilize (char substring[]) {

  for (int i = 0; substring[i] != '\0'; i++) {
    if ((substring[i] >= 'a' && substring[i] <= 'z') && substring[i] != ' ') {
      substring[i] = substring[i] - 32;
    }
  }
}