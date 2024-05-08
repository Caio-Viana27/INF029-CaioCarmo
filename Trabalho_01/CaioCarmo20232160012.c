// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Caio Viana Teixeira Carmo
//  email: Caio.vtc27@gmail.com
//  Matrícula: 20232160012
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "CaioCarmo20232160012.h" // Substitua pelo seu arquivo de header renomeado
#include <stdlib.h>
/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;

  for (i = x; i > 1; i--)
    fat = fat * i;

  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
  char sMes[3];
  char sAno[5];
  int i;

  for (i = 0; data[i] != '/'; i++){
    sDia[i] = data[i];	
  }
  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sDia[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }  


  int j = i + 1; //anda 1 cada para pular a barra
  i = 0;

  for (; data[j] != '/'; j++){
    sMes[i] = data[j];
    i++;
  }

  if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
    sMes[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }


  j = j + 1; //anda 1 cada para pular a barra
  i = 0;

  for(; data[j] != '\0'; j++){
    sAno[i] = data[j];
    i++;
  }

  if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
    sAno[i] = '\0';  // coloca o barra zero no final
  }else {
    dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno);

  dq.valido = 1;

  return dq;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int brake (char data[], char string[], int j) {
  int i;

  for (i = 0; data[j] != '/' && data[j] != '\0'; i++, j++) {
    string[i] = data[j];
    string[i + 1] = '\0';
  }
  return j;
}

int brakeDateRecursion (char data[], char string[], int j) {
  int index;
  if (data[j] != '\0') {
    index = brake (data, string, j);
  }
  return index;
}

void brakeDate (char data[], char dia[3], char mes[3], char ano[5]) {
  int j = 0;
  int indexJ;
  indexJ = brakeDateRecursion (data, dia, j);
  indexJ = brakeDateRecursion (data, mes, indexJ + 1);
  indexJ = brakeDateRecursion (data, ano, indexJ + 1);
}

int searchMonth (DataQuebrada dq, int array[]) {
  int found = 0;

  for (int i = 0; array[i] != -1; i++) {
    if (dq.iMes == array[i]) {
      found = 1;
      break;
    }
  }
  return found;
}

int dataValidation (DataQuebrada dq) {

  int Mes30[] = { 4, 6, 9, 11, -1};
  int Mes31[] = { 1, 3, 5, 7, 8, 10, 12, -1};

  if (dq.iAno < 100) dq.iAno += 2000;

  if (dq.iDia < 1 || dq.iMes < 1|| dq.iAno < 1) {
    dq.valido = 0;
    return 0;
  } else if ( (dq.iAno % 4 == 0 && dq.iAno % 100 != 0) 
               || (dq.iAno % 4 == 0 && dq.iAno % 100 == 0 && dq.iAno % 400 == 0) ) {

    if (dq.iMes == 2) {
      if (dq.iDia > 29) return 0;

    } else if (searchMonth(dq, Mes30)) {
      if (dq.iDia > 30) return 0;

    } else if (searchMonth(dq, Mes31)) {
      if (dq.iDia > 31) return 0;

    } else return 0;

  } else {
    if (dq.iMes == 2) {
      if (dq.iDia > 28) return 0;

    } else if (searchMonth(dq, Mes30)) {
      if (dq.iDia > 30) return 0;

    } else if (searchMonth(dq, Mes31)) {
      if (dq.iDia > 31) return 0;

    } else return 0;
  }
  return 1;
}    

int q1(char data[])
{
  DataQuebrada dq;
  int datavalida = 1;
  
  //quebrar a string data em strings sDia, sMes, sAno

  //DataQuebrada dataQuebrada = quebraData(data);
  //if (dataQuebrada.valido == 0) return 0;

  //printf("%s\n", data);

  char dia[3];
  char mes[3];
  char ano[5];

  brakeDate (data, dia, mes, ano);

  dq.iDia = atoi(dia);
  dq.iMes = atoi(mes);
  dq.iAno = atoi(ano);

  datavalida = dataValidation (dq);

  //printf("dia: %d\n", dq.iDia);
  //printf("mes: %d\n", dq.iMes);
  //printf("ano: %d\n", dq.iAno);
  //printf("validacao: %d\n", datavalida);

  if (datavalida)
      return 1;
  else
      return 0;
}

/* int i;
  for (i = 0; data[i] != '/'; i++) {
    dia[i] = data[i];
    if (data[i + 1] == '/') {
      dia[i + 1] = '\0';
    }
  }
  if (i == 0)
    return 0;
  

  int j = i + 1;
  i = 0;
  for (; data[j] != '/'; j++, i++) {
    mes[i] = data[j];
    if (data[j + 1] == '/') {
      mes[i + 1] = '\0';
    }
    //i++;
  }
  if (i == 0)
    return 0;
  

  j += 1;
  i = 0;
  for (; data[j] != '\0'; j++, i++) {
    ano[i] = data[j];
    if (data[j + 1] == '\0') {
      ano[i + 1] = '\0';
    }
    //i++;
  }
  if (i == 0)
    return 0; */

/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */

int anoBissexto (dateCompare dc) {

    int ano = dc.AnoInicial;

    if ( (ano % 4 == 0 && ano % 100 != 0) 
               || (ano % 4 == 0 && ano % 100 == 0 && ano % 400 == 0) ) {
        return 1;
    }
    return 0;
}

int searchMonth_dc (dateCompare dc, int array[]) {

  for (int i = 0; array[i] != -1; i++) {
    if (dc.MesesInicial == array[i]) {
      return 1;
    }
  }
  return 0;
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas três variáveis a seguir
    DiasMesesAnos dma;
    dateCompare dc;

    int Mes30[] = { 4, 6, 9, 11, -1};
    int Mes31[] = { 1, 3, 5, 7, 8, 10, 12, -1};

    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    } else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    } else {

      char dia[3];
      char mes[3];
      char ano[5];

      brakeDate (datainicial, dia, mes, ano);

      dc.DiaInicial = atoi(dia);
      dc.MesesInicial = atoi(mes);
      dc.AnoInicial = atoi(ano);

      brakeDate (datafinal, dia, mes, ano);
    
      dc.DiaFinal = atoi(dia);
      dc.MesesFinal = atoi(mes);
      dc.AnoFinal = atoi(ano);

      if (dc.AnoFinal < dc.AnoInicial) {
        dma.retorno = 4;
        return dma;
      } else if (dc.AnoFinal == dc.AnoInicial) {
          if (dc.MesesFinal < dc.MesesInicial) {
            dma.retorno = 4;
            return dma;
          } else if (dc.MesesFinal == dc.MesesInicial) {
              if (dc.DiaFinal < dc.DiaInicial) {
                dma.retorno = 4;
                return dma;
              }
          }
      }

      int totalDias = 0;

      while (100) {

        int Bissexto;
        if (dc.MesesInicial == 1 && dc.AnoInicial < dc.AnoFinal) {
            Bissexto = anoBissexto (dc);

            if (Bissexto) {
              totalDias += 366;
              dc.DiaInicial = 1;
              dc.AnoInicial++;
            } else {
              totalDias += 365;
              dc.DiaInicial = 1;
              dc.AnoInicial++;
            }
        } else if (dc.AnoInicial < dc.AnoFinal) {
          int controle = 1;

          while (controle) {

            if (dc.MesesInicial == 2) {
              Bissexto = anoBissexto (dc);
              if (Bissexto) totalDias += 28;
              else totalDias += 29;
            } else if (searchMonth_dc(dc, Mes30)) {
                totalDias += 30;
            } else if (searchMonth_dc(dc, Mes31)) {
                totalDias += 31;
            }
            dc.MesesInicial++;
            if (dc.MesesInicial == 12) {
              totalDias += 31 - dc.DiaInicial;
              dc.DiaInicial = 1;
              dc.MesesInicial = 1;
              dc.AnoInicial++;
              break;
            }
          }
        } else if (dc.MesesInicial == dc.MesesFinal && dc.AnoInicial == dc.AnoFinal) {
            totalDias += dc.DiaFinal - dc.DiaInicial;
            break;
        } else if (dc.AnoInicial == dc.AnoFinal) {
          int controle = 1;

          while (controle) {

            if (dc.MesesInicial == 2) {
              Bissexto = anoBissexto (dc);
              if (Bissexto) totalDias += 28;
              else totalDias += 29;
            } else if (searchMonth_dc(dc, Mes30)) {
                totalDias += 30 - dc.DiaInicial;
            } else if (searchMonth_dc(dc, Mes31)) {
                totalDias += 31 - dc.DiaInicial;
            }
            dc.DiaInicial = 0;
            dc.MesesInicial++;
            if (dc.MesesInicial == dc.MesesFinal) {
              totalDias += dc.DiaFinal;
              break;
            }
          }
          break;
        }
      }

      //printf("total de dias %d ", totalDias);

      dma.qtdAnos = totalDias / 365;
      totalDias %= 365;
      dma.qtdMeses = totalDias / 30;
      dma.qtdDias = totalDias % 30;

      //printf("qtdDias %d ", dma.qtdDias);
      //printf("qtdMeses %d ", dma.qtdMeses);
      //printf("qtdAnos %d\n", dma.qtdAnos);

      //verifique se a data final não é menor que a data inicial

      //calcule a distancia entre as datas

      //se tudo der certo
      dma.retorno = 1;
      return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */

int searchChar (char texto[], char c, int isCaseSensitive) {
    int quantity = 0;

    if (isCaseSensitive == 1) {
      for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == c) quantity++;
      }
    } else if (isCaseSensitive == 0) {
      for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == c || texto[i] == c - 32 || texto[i] == c + 32) quantity++;
      }
    }
    return quantity;
}
    
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = -1;

    qtdOcorrencias = searchChar (texto, c, isCaseSensitive);

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */

int searchString (char *strTexto, char *strBusca, int posicoes[30]) {
  int inicial = 0;
  int final = 1;
  int acento = 0;
  int contador = 0;
    int temacento=0;

  for (int i = 0; strTexto[i] != '\0'; i++) {

    if (strTexto[i] == -61)
     acento++; // -61 é o codigo de acento

    if (strTexto[i] == strBusca[0]) {
      int posicaoI = i;
      int found = 1;
      int j = 1;
      for (; strBusca[j] != '\0'; j++) {

        if (strTexto[i+j] != strBusca[j]) {
          found = 0;
          break;
        }
      }
      if (found) {
        posicoes[inicial] = (posicaoI + 1) - acento;
        posicoes[final] = (i + j) - acento;
        contador++;
        i = i + j - 1;
        inicial += 2;
        final += 2;
      }
    }
  }
  return contador;
}

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = searchString (strTexto, strBusca, posicoes);

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int resto = 0;
    int numInverso = 0;
    
    while (num != 0) {
      resto = num % 10;
      num = num / 10;
      numInverso += resto;
      if (num > 0)
        numInverso *= 10;
    }
    return numInverso;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */
void decompor (int num, int vetor[]) {
    for (int i = 0; num != 0; i++) {
      vetor [i] = num % 10;
      num = num / 10;
    }
    int size = 0;
    for (int i = 0; vetor[i] != -1; i++) size++;

    for (int i = 0, j = size - 1; i < j; i++, j--) {
      int temp = vetor[i];
      vetor[i] = vetor[j];
      vetor[j] = temp;
    }
}

void init_Vetor (int vetor[]) {
    for (int i = 0; i < 15; i++)
      vetor[i] = -1;
}

int search_Num (int vetorBase[], int vetorBusca[]) {
  int contador = 0;

  int i = 0;
  while (vetorBase[i] != -1) {

    if (vetorBase[i] == vetorBusca[0]) {
      int found = 1;
      int j = 1;
      if (vetorBusca[1] == -1) { contador++; found = 0; }
      while (vetorBusca[j] != -1) {

        if (vetorBase[i+j] != vetorBusca[j]) {
          found = 0;
          break;
        }
        j++;
      }
      if (found) {
        contador++;
        i += 2;
      } else i++;
    } else i++;
  }
  return contador;
}

int q6(int numerobase, int numerobusca)
{
    int vetorBase[15];
    int vetorBusca[15];

    init_Vetor (vetorBase);
    init_Vetor (vetorBusca);

    decompor (numerobase, vetorBase);
    decompor (numerobusca, vetorBusca);

    int qtdOcorrencias = search_Num (vetorBase, vetorBusca);

    return qtdOcorrencias;
}

/*     int qtdOcorrencias = 0;

    while (numerobase != 0) {
    int resto = numerobase % 10;
    int restoBusca = numerobusca % 10;
    int found;

      if (resto == restoBusca) {
        found = 1;
        while (restoBusca != 0) {
          resto = numerobase % 10;
          resto = numerobusca % 10;
          if (resto != restoBusca) {
            found = 0;
            break;
          }
          if (found) qtdOcorrencias++;
          numerobase /= 10;
          restoBusca /= 10;
        }
      }
      numerobase /= 10;
    }

    printf("qtdOcorrencias %d\n", qtdOcorrencias); */


 /* for (int i = 0; vetorBase[i] != -1; i++)
      printf("%d", vetorBase[i]);
    printf("\n");
    for (int i = 0; vetorBusca[i] != -1; i++)
      printf("%d", vetorBusca[i]);
    printf("\n"); */