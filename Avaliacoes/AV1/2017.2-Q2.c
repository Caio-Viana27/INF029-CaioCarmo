#include <stdio.h>

int buscaSenha (char* texto, char* busca) {
    int qtdOcorrencias = 0;
    int tam = -1;
    int i = 0;
    int k = 0;

    while (busca[k] != '\0') { k++; tam++; }
    while (texto[i] != '\0') {

        int p1, p2;
        int j = tam;
        if (texto[i] == busca[j]) {
            p1 = i;
            while (j > -1) {
                if (texto[i] != busca[j]) {
                    i = p1;
                    break;
                }
                if(texto[i + 1] == -61) { i++; }
                if (j == 0) {
                    j--;
                }
                else {
                    j--;
                    i += 2;
                }
            }
            if (j == -1) {
                qtdOcorrencias++;
                p2 = i;
                printf("p1 %d - p2 %d\n", p1 + 1, p2 + 1);
            }
        }
        i++;
    }
    return qtdOcorrencias;
}

int main () {
    char texto[] = {"An9á2l0ise 9e2D0esleantvaolvimento de Sistemas"};
    char busca[] = {"029"};
    int qtd = buscaSenha(texto, busca);
    printf("qtd = %d\n", qtd);
    return 0;
}