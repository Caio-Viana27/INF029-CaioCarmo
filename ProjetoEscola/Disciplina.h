#include "Aluno.h"
#include "Professor.h"
#define max_tam 5
#define max_vagas 5
#define max_semestre 7
#define max_nome 50

typedef struct {
  int Codigo;
  char NomeDisciplina[max_nome];
  int Semestre;
  char MatriculaProfessor[max_nome];
  char Alunos[max_vagas][max_nome];
  int vagas;
  int AlunosMatriculados;
  int ProfessorMatriculado;
} Disciplina;

int main(void);
int menuDisciplina();
int cadastrarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
int atualizarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina, Professor listaProfessor[], int qtdProfessor);
int matricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno);
int desmatricularAluno(Disciplina listaDisciplina[], Aluno listaAluno[], int qtdDisciplina, int qtdAluno);
int matricularProfessor(Disciplina listaDisciplina[], Professor listaProfessor[], int qtdDisciplina, int qtdProfessor);
int ExcluirDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);
void listarDisciplina(Disciplina listaDisciplina[], int qtdDisciplina);