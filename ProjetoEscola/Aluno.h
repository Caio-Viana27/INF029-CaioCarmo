#define max_nome 50
#define max_CPF 12
#define max_tam 5
#define data 3

typedef struct {
  int Matricula;
  char Nome[max_nome];
  char Sexo;
  char CPF[max_CPF];
  int idade[data];
  int qtdMaterias;
} Aluno;

int main(void);
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int ExcluirAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);