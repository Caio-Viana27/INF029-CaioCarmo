#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "Disciplina.h"
#define max_nome 50
#define max_CPF 12
#define max_tam 5
#define max_semestre 7
#define CADASTRO_SUCESSO -1
#define CADASTRO_FALHOU -2
#define CADASTRO_ATUALIZADO -3
#define ATUALIZAR_FALHOU -4
#define CADASTRO_EXCLUIDO -5
#define EXCLUIR_FALHOU -6
#define MATRICULA_DISCIPLINA_SUCESSO -7
#define MATRICULA_DISCIPLINA_FALHOU -8
#define DESMATRICULAR_SUCESSO -9
#define DESMATRICULAR_FALHOU -10
#define true 1

int menuDisciplina();
int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
int atualizarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina, Professor listaProfessor[], int qtdProfessor);
int matricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno);
int desmatricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno);
int matricularProfessor(Disciplina listaDisciplina[], Professor listaProfessor[], int qtdDisciplina, int qtdProfessor);
int ExcluirDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
int validarCodigoDisciplina( Disciplina listaDisciplina[], int qtdDisciplina);
int validarNomeDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);

Disciplina listaDisciplina[max_tam];
int qtdDisciplina = 0;
extern Aluno listaAluno[max_tam];
extern int qtdAluno;
extern Professor listaProfessor[max_tam];
extern int qtdProfessor;

FILE *arquivoDisciplina;

int menuDisciplina() {

  arquivoDisciplina = fopen("Disciplina.txt", "w");
  if (arquivoDisciplina == NULL) {
    printf("Falha ao abrir o arquivo!\n");
  }

  int opcao;

  printf("----------------------------------------\n");
  printf("|  Menu Disciplina:                    |\n");
  printf("|  Disciplina(s) cadastrada(s): %d      |\n", qtdDisciplina);
  printf("----------------------------------------\n");
  printf("|  0 - Voltar                          |\n");
  printf("|  1 - Cadastrar Disciplina            |\n");
  printf("|  2 - Atualizar Disciplina            |\n");
  printf("|  3 - Matricular Aluno                |\n");
  printf("|  4 - Desmatricular Aluno             |\n");
  printf("|  5 - Matricular Professor            |\n");
  printf("|  6 - Excluir Disciplina              |\n");
  printf("|  7 - Listar                          |\n");
  printf("----------------------------------------\n");
  scanf("%d", &opcao);
  system("clear");

  switch (opcao) { 
    case 0:
        opcao = main();
        system("clear");
        break;

    case 1:
        opcao = cadastrarDisciplina(listaDisciplina, qtdDisciplina);
        if (opcao == CADASTRO_SUCESSO) {
              qtdDisciplina += 1;
          printf("Disciplina cadastrada com sucesso\n");
        }else if (opcao == CADASTRO_FALHOU) {
          printf("Não foi possível cadastrar a Disciplina\n");
        }         
        if(opcao == CADASTRO_SUCESSO || opcao == CADASTRO_FALHOU)
        opcao = menuDisciplina(qtdDisciplina);
        fclose(arquivoDisciplina);
        break;

    case 2:
        opcao = atualizarDisciplina(listaDisciplina, qtdDisciplina, listaProfessor, qtdProfessor);
        if (opcao == CADASTRO_ATUALIZADO) {
          printf("Disciplina Atualizada com sucesso!\n");
        }else if (opcao == ATUALIZAR_FALHOU) {
          printf("Não foi possível Atualizar o Disciplina!\n");
        }
        if(opcao == CADASTRO_ATUALIZADO || opcao == ATUALIZAR_FALHOU)
        opcao = menuDisciplina(qtdDisciplina);
    break;

    case 3:
        opcao = matricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
        if (opcao == MATRICULA_DISCIPLINA_SUCESSO) {
          printf("Aluno matriculado com sucesso!\n");
        }else if (opcao == MATRICULA_DISCIPLINA_FALHOU) {
          printf("Não foi possível matricular o aluno!\n");
        }         
        if(opcao == MATRICULA_DISCIPLINA_SUCESSO || opcao == MATRICULA_DISCIPLINA_FALHOU)
        opcao = menuDisciplina(qtdDisciplina);
    break;

    case 4:
        opcao = desmatricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
        if (opcao == DESMATRICULAR_SUCESSO) {
        printf("Aluno desmatriculado com sucesso!\n");
        }else if (opcao == DESMATRICULAR_SUCESSO) {
        printf("Não foi possível desmatricular o aluno!\n");
        }         
        if(opcao == DESMATRICULAR_SUCESSO || opcao == DESMATRICULAR_SUCESSO)
        opcao = menuDisciplina(qtdDisciplina);
    break;

    case 5:
        opcao = matricularProfessor(listaDisciplina, listaProfessor, qtdDisciplina, qtdProfessor);
        if (opcao == MATRICULA_DISCIPLINA_SUCESSO) {
        printf("Professor matriculado com sucesso\n");
        }else if (opcao == MATRICULA_DISCIPLINA_FALHOU) {
        printf("Não foi possível matricular o Professor\n");
        }         
        if(opcao == MATRICULA_DISCIPLINA_SUCESSO || opcao == MATRICULA_DISCIPLINA_FALHOU)
        opcao = menuDisciplina(qtdDisciplina);
    break;

    case 6:
        opcao = ExcluirDisciplina(listaDisciplina, qtdDisciplina);
        if (opcao == CADASTRO_EXCLUIDO) {
            qtdDisciplina--;
        printf("Discilina excluida com sucesso\n");
        }else if (opcao == EXCLUIR_FALHOU) {
        printf("Não foi possível excluir a Disciplina\n");
        }         
        if(opcao == CADASTRO_EXCLUIDO || opcao == EXCLUIR_FALHOU)
        opcao = menuDisciplina(qtdDisciplina);
    break;

    case 7:
        listarDisciplina(listaDisciplina, qtdDisciplina);
        opcao = menuDisciplina(qtdDisciplina);
    break;
    default:
      printf("Opção inválida");
    break;
  }
  return opcao;
}

int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {

int sair = 1;

  if (qtdDisciplina < max_tam) {

    while(sair != 0) {

    validarCodigoDisciplina(listaDisciplina, qtdDisciplina);
    validarNomeDisciplina(listaDisciplina, qtdDisciplina);

    printf("Digite o semestre da disciplina: ");
    scanf("%d", &listaDisciplina[qtdDisciplina].Semestre);
    getchar();

    fprintf (arquivoDisciplina, "Semestre: %d\n", listaDisciplina[qtdDisciplina].Semestre);

    int vagas;

    printf("Digite o número de vagas da disciplina: ");
    scanf("%d", &listaDisciplina[qtdDisciplina].vagas);
    getchar();

    fprintf (arquivoDisciplina, "Vagas: %d\n", listaDisciplina[qtdDisciplina].vagas);

    listaDisciplina[qtdDisciplina].AlunosMatriculados = 0;
    listaDisciplina[qtdDisciplina].ProfessorMatriculado = 0;

    sair = 0;
    }
    return CADASTRO_SUCESSO;
  }else {
    printf("Lista de disciplinas cheia\n");
    return CADASTRO_FALHOU;
  }
}

void listarDisciplina(Disciplina istaDisciplina[], int qtdDisciplina) {

   if (qtdDisciplina == 0) {
    printf("Não há Disciplinas cadastradas!\n");
  }else {

   int selecionar;

   printf("----------------------------------------\n");
   printf("| Lista Disciplina:                    |\n");
   printf("| %d Disciplina(s) cadastrada(s)        |\n", qtdDisciplina);
   printf("----------------------------------------\n");
   printf("|  0 - listar Disciplinas              |\n");
   printf("|  1 - listar Disciplinas com alunos   |\n");
   printf("|  2 - listar Disciplinas +40 vagas    |\n");
   printf("----------------------------------------\n");

   scanf("%d", &selecionar);
   getchar();

   if (selecionar > 2 || selecionar < 0) {
     printf("Opção inválida\n");
     return;
   }

   switch (selecionar) {
     case 0:
        printf("----------------------------------------\n");
        printf("| Lista de Disciplina(s):              |\n");
        printf("| %d Disciplina(s) cadastrada(s)        |\n", qtdDisciplina);
        printf("----------------------------------------\n");

        for(int i = 0; i < qtdDisciplina; i++) {

          printf("Nome: %s",                  listaDisciplina[i].NomeDisciplina);
          printf("Codigo: %d\n",              listaDisciplina[i].Codigo);
          printf("Semestre: %d\n",            listaDisciplina[i].Semestre);
          printf("Vagas: %d\n",               listaDisciplina[i].vagas);
          printf("Professor: %s\n",           listaDisciplina[i].MatriculaProfessor);
          printf("Alunos matriculados: %d\n", listaDisciplina[i].AlunosMatriculados);
        }
     break;
     
     case 1:
        printf("----------------------------------------\n");
        printf("| Lista de Disciplina(s):              |\n");
        printf("| %d Disciplina(s) cadastrada(s)        |\n", qtdDisciplina);
        printf("----------------------------------------\n");

        for(int i = 0; i < qtdDisciplina; i++) {

          printf("Nome: %s",                  listaDisciplina[i].NomeDisciplina);
          printf("Codigo: %d\n",              listaDisciplina[i].Codigo);
          printf("Semestre: %d\n",            listaDisciplina[i].Semestre);
          printf("Vagas: %d\n",               listaDisciplina[i].vagas);
          printf("Professor: %s\n",           listaDisciplina[i].MatriculaProfessor);
          printf("Alunos matriculados: %d\n", listaDisciplina[i].AlunosMatriculados);

          for (int j = 0; j < listaDisciplina[i].AlunosMatriculados; j++) {
            printf("%s", listaDisciplina[i].Alunos[j]);
          }
          printf("----------------------------------------\n");
        }
     break;
     
     case 2:
        for (int i = 0; i < qtdDisciplina; i++) {
          if (listaDisciplina[i].vagas > 40) {
            printf("Nome: %s",  listaDisciplina[i].NomeDisciplina);
            printf("Vagas: %d\n", listaDisciplina[i].vagas);
          }
        }
     break;
    }
  }
}

int ExcluirDisciplina(Disciplina listaDisciplina[], int qtdDisciplina) {

  int excluir;

  if (qtdDisciplina == 0) {
    printf("Não há disciplina(s) cadastrada(s)\n");
    return EXCLUIR_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Excluir Disciplina:                  |\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < qtdDisciplina; i++) {
      printf("Digite %d para excluir: %s", i, listaDisciplina[i].NomeDisciplina);
    }
    scanf("%d", &excluir);
    getchar();
    while (excluir < qtdDisciplina) {
          listaDisciplina[excluir] = listaDisciplina[excluir+1];
      excluir++;
    }
    return CADASTRO_EXCLUIDO;
  }
}

int atualizarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina
                       ,Professor listaProfessor[], int qtdProfessor) {

  int atualizar;
  int selecionar;

  if (qtdDisciplina == 0) {
    printf("Não há Disciplinas cadastradas!\n");
    return ATUALIZAR_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Atualizar Disciplina:                |\n");
    printf("----------------------------------------\n");
    for(int i = 0; i < qtdDisciplina; i++) {
      printf("Digite %d para Atualizar: %s", i, listaDisciplina[i].NomeDisciplina);
    }
    scanf("%d", &atualizar);
    getchar();

    printf("----------------------------------------\n");
    printf("Atualizar Disciplina: %s\n", listaDisciplina[atualizar].NomeDisciplina);
    printf("Digite 0 para Atualizar o Nome da Matricula\n");
    printf("Digite 1 para Atualizar o Codigo\n");
    printf("Digite 2 para Atualizar o Semestre\n");
    printf("Digite 3 para Atualizar o Professor\n");

    scanf("%d", &selecionar);
    getchar();

    switch (selecionar) {
      case 0:
          printf("Digite o novo Nome da Disciplina: ");
          fgets(listaDisciplina[atualizar].NomeDisciplina, max_nome, stdin);
      break;
      case 1:
          printf("Digite o novo Codigo: ");
          scanf("%d", &listaDisciplina[atualizar].Codigo);
          getchar();
      break;
      case 2:
         validarCodigoDisciplina(listaDisciplina, qtdDisciplina);
      break;
      case 3:
        printf("----------------------------------------\n");
          printf("| Selecione o Professor:             |\n");
        printf("----------------------------------------\n");
          int selecionarProfessor;
          int j;
          for(j = 0; j < qtdProfessor; j++) {

            if (strcmp (listaProfessor[j].Nome, listaDisciplina[atualizar].MatriculaProfessor)) {
              printf("Digite %d para selecionar: %s", j, listaProfessor[j].Nome);
            }else
              continue;
          }
          scanf("%d", &selecionarProfessor);
          getchar();

          if (selecionarProfessor > j || selecionarProfessor < 0) {
            printf("Numero invalido!\n");
            matricularProfessor(listaDisciplina, listaProfessor, qtdDisciplina, qtdProfessor);
          }else {
            strcpy(listaDisciplina[atualizar].MatriculaProfessor, listaProfessor[selecionarProfessor].Nome);
          }
      break;
      default:
        printf("Opção inválida");
      break;
    }
    return CADASTRO_ATUALIZADO;
  }
}

int matricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno) {

  int selecionarAluno;
  int selecionarDisciplina;

  if (qtdDisciplina == 0) {
    printf("Não há Disciplinas cadastradas!\n");
    return MATRICULA_DISCIPLINA_FALHOU;
  }else if(qtdAluno == 0) {
    printf("Não há Aluno(s) cadastrado(s)!\n");
    return MATRICULA_DISCIPLINA_FALHOU;
  }else {

    printf("----------------------------------------\n");
    printf("| Selecione a Disciplina:              |\n");
    printf("----------------------------------------\n");
    int i;
    for(int i = 0; i < qtdDisciplina; i++) {
      printf("Digite %d para selecionar: %s", i, listaDisciplina[i].NomeDisciplina);
    }
    scanf("%d", &selecionarDisciplina);
    getchar();

    if (selecionarDisciplina > i || selecionarDisciplina < 0) {
      printf("Numero invalido!\n");
      matricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
    }

    int qtdAlunosMatriculados = listaDisciplina[selecionarDisciplina].AlunosMatriculados;

    if (qtdAlunosMatriculados < listaDisciplina[selecionarDisciplina].vagas) {

      printf("----------------------------------------\n");
      printf("| Selecione o Aluno:                   |\n");
      printf("----------------------------------------\n");
      int j;
      for(j = 0; j < qtdAluno; j++) {
        printf("Digite %d para selecionar: %s", j, listaAluno[j].Nome);
      }
      scanf("%d", &selecionarAluno);
      getchar();
      if (selecionarAluno > j || selecionarAluno < 0) {
        printf("Numero invalido!\n");
        matricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
      }else {
        strcpy (listaDisciplina[selecionarDisciplina].Alunos[qtdAlunosMatriculados],
                listaAluno[selecionarAluno].Nome);

        listaDisciplina[selecionarDisciplina].AlunosMatriculados++;
        listaAluno[selecionarAluno].qtdMaterias++;
      }
      return MATRICULA_DISCIPLINA_SUCESSO;
    }else {
      printf("Não há vagas disponiveis!\n");
      return MATRICULA_DISCIPLINA_FALHOU;
    }
  }
}

int desmatricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno) {

  int selecionarAluno;
  int selecionarDisciplina;

  if (qtdDisciplina == 0) {
    printf("Não há Disciplinas cadastradas!\n");
    return DESMATRICULAR_FALHOU;
  }else if(qtdAluno == 0) {
    printf("Não há Aluno(s) cadastrado(s)!\n");
    return DESMATRICULAR_FALHOU;
  }else {

    printf("----------------------------------------\n");
    printf("| Selecione a Disciplina:              |\n");
    printf("----------------------------------------\n");
    int i;
    for(i = 0; i < qtdDisciplina; i++) {
      printf("Digite %d para selecionar: %s", i, listaDisciplina[i].NomeDisciplina);
    }
    scanf("%d", &selecionarDisciplina);
    getchar();

    if (selecionarDisciplina > i || selecionarDisciplina < 0) {
      printf("Numero invalido!\n");
      matricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
    }

    /* int qtdAlunosMatriculados = listaDisciplina[selecionarDisciplina].AlunosMatriculados; */

    printf("----------------------------------------\n");
    printf("| Selecione o Aluno:                   |\n");
    printf("----------------------------------------\n");

    int j;
    for (j = 0; j < listaDisciplina[selecionarDisciplina].AlunosMatriculados; j++) {
      printf("Digite %d para selecionar: %s", j, listaDisciplina[selecionarDisciplina].Alunos[j]);
    }
    scanf("%d", &selecionarAluno);
    getchar();

    if (selecionarAluno > j || selecionarAluno < 0) {
      printf("Numero invalido!\n");
      matricularAluno(listaDisciplina, listaAluno, qtdDisciplina, qtdAluno);
    }else {
      while (selecionarAluno < listaDisciplina[selecionarDisciplina].AlunosMatriculados) {
        strcpy (listaDisciplina[selecionarDisciplina].Alunos[selecionarAluno],
                listaDisciplina[selecionarDisciplina].Alunos[selecionarAluno+1]);
        selecionarAluno++;
      }
      listaDisciplina[selecionarDisciplina].AlunosMatriculados--;
      listaAluno[selecionarAluno].qtdMaterias--;
    }
    return DESMATRICULAR_SUCESSO;
  }
}

int matricularProfessor(Disciplina listaDisciplina[], Professor listaProfessor[]
                       ,int qtdDisciplina, int qtdProfessor) {

  int selecionarProfessor;
  int selecionarDisciplina;

  if (qtdDisciplina == 0) {
    printf("Não há Disciplinas cadastradas!\n");
    return MATRICULA_DISCIPLINA_FALHOU;
  }else if(qtdProfessor == 0) {
    printf("Não há professor(es) cadastrado(s)!\n");
    return MATRICULA_DISCIPLINA_FALHOU;
  }else {
    printf("----------------------------------------\n");
    printf("| Selecione a Disciplina:              |\n");
    printf("----------------------------------------\n");

    int i;
    for(i = 0; i < qtdDisciplina; i++) {
      printf("Digite %d para selecionar: %s", i, listaDisciplina[i].NomeDisciplina);
    }
    scanf("%d", &selecionarDisciplina);
    getchar();

    if (selecionarDisciplina > i || selecionarDisciplina < 0) {
      printf("Numero invalido!\n");
      matricularProfessor(listaDisciplina, listaProfessor, qtdDisciplina, qtdProfessor);
    }else if (listaDisciplina[selecionarDisciplina].ProfessorMatriculado > 0) {
      printf("Disciplina já possui professor!\n");
      return MATRICULA_DISCIPLINA_FALHOU;
    }
    printf("----------------------------------------\n");
    printf("| Selecione o Professor:               |\n");
    printf("----------------------------------------\n");

    int j;
    for(j = 0; j < qtdProfessor; j++) {
      printf("Digite %d para selecionar: %s", j, listaProfessor[j].Nome);
    }
    scanf("%d", &selecionarProfessor);
    getchar();

    if (selecionarProfessor > j || selecionarProfessor < 0) {
      printf("Numero invalido!\n");
      matricularProfessor(listaDisciplina, listaProfessor, qtdDisciplina, qtdProfessor);
    }else {
      strcpy (listaDisciplina[selecionarDisciplina].MatriculaProfessor
             ,listaProfessor[selecionarProfessor].Nome);
    }
    listaDisciplina[selecionarDisciplina].ProfessorMatriculado++;
    return MATRICULA_DISCIPLINA_SUCESSO;
  }
}

int validarCodigoDisciplina( Disciplina listaDisciplina[], int qtdDisciplina) {
    int valido = 1;

    while (valido == 1) {
        printf("\nDigite o numero do código: ");
        if (scanf("%d", &listaDisciplina[qtdDisciplina].Codigo) != true) {
          printf("Digite um válido!\n");
          while (getchar() != '\n'); 
          continue;
      }
      if (listaDisciplina[qtdDisciplina].Codigo <= 0 || listaDisciplina[qtdDisciplina].Codigo > 9999999) {
          printf("Digite um código válido!\n");
      } else {
          int codigoExistente = 0;
          for (int i = 0; i < qtdDisciplina; i++) {
              if (listaDisciplina[i].Codigo == listaDisciplina[qtdDisciplina].Codigo) {
                  codigoExistente = true;
                  break;
              }
          }
          if (codigoExistente) {
            printf("Este código ja esta sendo utilizado!\n");
          } else {
            valido = 0;
            fprintf(arquivoDisciplina, "Codigo: %d\n", listaDisciplina[qtdDisciplina].Codigo);
          }
      }
  }
  return 0;
}

int validarNomeDisciplina(Disciplina listaDisciplina[], int qtdDisciplina){
    int valido = 1;

    printf("Digite o nome da disciplina: ");
    getchar();

    while (valido == 1) {

        fgets(listaDisciplina[qtdDisciplina].NomeDisciplina, max_nome, stdin);

        char teste = listaDisciplina[qtdDisciplina].NomeDisciplina[0];

        if ((teste >= 'A' && teste <= 'Z') || (teste >= 'a' && teste <= 'z')) {
            valido = 0;
        } else {
            printf("Digite um nome válido para a disciplina: ");
        }
    }
    fprintf(arquivoDisciplina, "Disciplina: %s", listaDisciplina[qtdDisciplina].NomeDisciplina);
    return 0;
}