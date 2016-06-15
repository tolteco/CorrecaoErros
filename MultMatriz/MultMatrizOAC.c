#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float tempo, tempo2;
FILE *OUT;
clock_t inicio, fim;
//inicio=clock();
//procedimento();
//fim=clock();

//tempo=(float) (((fim-inicio)+0.0)/CLOCKS_PER_SEC);//Retorna o valor em seguntos
///Aloca Matriz
double **alocaMatriz(int l, int c){
  int i;
  double **A;
  A=(double **) calloc(l, sizeof(double));
  for(i=0;i<l;i++){
    A[i]=(double *) calloc(c, sizeof(double));
  }
  return A;
}

///Gera matriz
void geraMatriz(double **M, int l, int c){
  int i, j;
  srand((unsigned)time(NULL)); //seed
  for(i=0;i<l;i++){
    for(j=0;j<c;j++){
      M[i][j]=(double)(rand()%1000+l)/100;
    }
  }
}

///Multiplica Matriz
void MulM1M2(double **M1, double **M2, double **R, int l, int c){
  int i, j, k;
  inicio = clock();
  for(i=0;i<l;i++){
    for(j=0;j<l;j++){
      for(k=0;k<c;k++){
        R[i][j]=R[i][j]+(M1[i][k]*M2[k][j]);
      }
    }
  }
  fim = clock();
  tempo = (float) (((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
}

///Transposicao da matriz
void transpostaM(double **M, int l, int c){
  int i, j;
  double aux;
  inicio = clock();
  for(i=0;i<l;i++){
    for(j=0;j<c;j++){
      if(j!=i){
        aux=M[i][j];
        M[i][j]=M[j][i];
        M[j][i]=aux;
      }
    }
  }
  fim = clock();
  tempo = (float) (((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
}

///Multiplica Matriz Transposta
void MulM1M2T(double **M1, double **M2T, double **R, int l, int c){
  int i, j, k;
  inicio = clock();
  for(i=0;i<l;i++){
    for(j=0;j<l;j++){
      for(k=0;k<c;k++){
        R[i][j]=R[i][j]+(M1[i][k]*M2T[j][k]);
      }
    }
  }
  fim = clock();
tempo2 = (float) (((fim - inicio) + 0.0) / CLOCKS_PER_SEC);
}

/*void imprimeR(double **R, int l, int c){
  int i, j;
  OUT = fopen("Log.txt", "a");
  for(i=0;i<l;i++){
    for(j=0;j<c;j++){
      fprintf(OUT, "%lf ", R[i][j]);
    }
    fprintf(OUT, "\n");
  }
}*/

void imprimelog(int A){
  OUT = fopen("Log.txt", "a");
  if (A == 1){
    fprintf(OUT, "%f\n", tempo);
  } else if (A == 2){
    fprintf(OUT, "%f\n", tempo);
    fprintf(OUT, "%f\n", tempo2);
  }
  fclose(OUT);
}

int main (int argc, char *op[]){
  int l, c;
  double **R, **M1, **M2;
  const char *errstr;
  l = (int)strtol(op[1], (char **)NULL, 10);
  c = (int)strtol(op[1], (char **)NULL, 10);
  if (argc == 4){
    if (strcmp(op[3], "o") == 0) {
      R = alocaMatriz(l, c);
      M1 = alocaMatriz(l, c);
      M2 = alocaMatriz(l, c);
      geraMatriz(M1, l, c);
      geraMatriz(M2, l, c);
      MulM1M2(M1, M2, R, l, c);
      //imprimeR(R, l, c);
      //imprimeR(M1, l, c);
      //imprimeR(M2, l, c);
      imprimelog(1);
    } else if (strcmp(op[3], "t") == 0) {
      R = alocaMatriz(l, c);
      M1 = alocaMatriz(l, c);
      M2 = alocaMatriz(l, c);
      geraMatriz(M1, l, c);
      geraMatriz(M2, l, c);
      transpostaM(M2, l, c);
      MulM1M2T(M1, M2, R, l, c);
      //imprimeR(R, l, c);
      //imprimeR(M1, l, c);
      //imprimeR(M2, l, c);
      imprimelog(2);
    } else {
      printf("Opcao invalida\n");
    }
  } else if (argc > 4) {
    printf("Argumentos demais.\n");
  } else {
    printf("Argumentos de menos.\n");
  }
  return 0;
}
