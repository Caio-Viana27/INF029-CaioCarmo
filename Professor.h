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
} Professor;

int main(void);
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