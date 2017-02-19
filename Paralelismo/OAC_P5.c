#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <omp.h>
#include "OAC_P5_Config.h"

/* PARAMETERS */
#define LARGURA 16384 // 2^14 = 16384
#define STD_THREADS 4
#define MAX_THREADS 4
#define NO_TESTS 6

void printR     (double *v, double **m, double *r);
void printMatrix(double** matrix, int noLines, int noColumns);

int      p_main          (double** matrix1, double** matrix2, int noLines, int noColumns);
void     matrixPow2      (double** matrix, int noLines, int noColumns); //Quadrado de todos elementos
double** matrixSub       (double** matrix1, double** matrix2, int noLines, int noColumns); //Subtrai elemento a elemento e retorna outra
double   matrixAccumulate(double** matrix, int noLines, int noColumns); //Acumula todos os valores em um e retorna

int main(int argc, char *argv[]){
	int numThreads=-1;
	setlocale(LC_NUMERIC, "");//?

	if (argc > 1) {
		numThreads = atoi(argv[1]);
		if (numThreads > MAX_THREADS){
            numThreads = MAX_THREADS;
            printf("Limite excedido. Trocando para numero max de threads (%d).\n", MAX_THREADS);
		}
	}else{
		numThreads = STD_THREADS;
	}

	omp_set_num_threads(numThreads);
	printf("Threads = %d.\n\n", numThreads );

	int i;
	for (i=0; i<NO_TESTS; i++){
        double** matrix1 = getData(LARGURA, LARGURA);
        double** matrix2 = getData(LARGURA, LARGURA);
        p_main(matrix1, matrix2, LARGURA, LARGURA);
	}

	return 0;
}

int p_main(double** matrix1, double** matrix2, int noLines, int noColumns){
    double start_time, run_time;
    start_time = omp_get_wtime();

	matrixPow2(matrix1, noLines, noColumns);
	matrixPow2(matrix2, noLines, noColumns);
    double** resultSubtract = matrixSub(matrix1, matrix2, noLines, noColumns);
	double accumulate = matrixAccumulate(resultSubtract, noLines, noColumns);

	run_time = omp_get_wtime() - start_time;
	printf("Tempo de processamento total:        %lf s\n", run_time);
	printf("Resultado final acumulado:           %.1lf.\n\n", accumulate);


	int i=0;
	for (i=0; i<noLines; i++){
        free(matrix1[i]);
        free(matrix2[i]);
        free(resultSubtract[i]);
	}
	free(matrix1);
    free(matrix2);
    free(resultSubtract);

    return 0;
}

/**
* PARALELO
* Faz o quadrado de todos os elementos da matriz.
*/
void matrixPow2(double** matrix, int noLines, int noColumns){
    double start_time, run_time;
    start_time = omp_get_wtime();

    int i,j;
    #pragma omp parallel for private(j) shared(i, matrix)
	for(i = 0; i < noLines; i++)
		for(j = 0; j < noColumns; j++)
			matrix[i][j] *= matrix[i][j];

    run_time = omp_get_wtime() - start_time;
	printf("Tempo para elevar ao quadrado:       %lf s\n", run_time);
}

/**
* PARALELO
* Subtrai elemento a elemento (Matrix1 - Matrix2) e retorna o resultado
* em uma terceira matriz.
*/
double** matrixSub(double** matrix1, double** matrix2, int noLines, int noColumns){
    double start_time, run_time;
    start_time = omp_get_wtime();

    int i,j;
    double **newMatrix = (double **) malloc(noLines * sizeof(double*));
    #pragma omp parallel for shared(i, newMatrix)
	for(i = 0; i < noLines; i++){
		newMatrix[i] = (double *) malloc(noColumns * sizeof(double));
	}

    #pragma omp parallel for private(j) shared(i, matrix1, matrix2, newMatrix)
	for(i = 0; i < noLines; i++)
		for(j = 0; j < noColumns; j++)
			newMatrix[i][j] = matrix1[i][j] - matrix2[i][j];

    run_time = omp_get_wtime() - start_time;
	printf("Tempo para alocar matriz e subtrair: %lf s\n", run_time);

	return newMatrix;
}

/**
* PARALELO
* Acumula (Soma) todos os valores da matriz em um double.
*/
double matrixAccumulate(double** matrix, int noLines, int noColumns){
    double start_time, run_time;
    start_time = omp_get_wtime();

    double acc=0.0;

    int i,j;
    #pragma omp parallel for private(j) shared(i, matrix) reduction(+:acc)
	for(i = 0; i < noLines; i++)
		for(j = 0; j < noColumns; j++)
			acc += matrix[i][j];

    run_time = omp_get_wtime() - start_time;
	printf("Tempo para acumular:                 %lf s\n", run_time);

	return acc;
}

// Imprime vV x mM = vR no formato SSV (semicolon separated value)
void printR(double *v, double **m, double *r){
	int i, j;
	for(i = 0; i < LARGURA; i++){
		printf("%lf; ;", v[i]);
		for(j = 0; j < LARGURA; j++){
			printf("%lf;", m[i][j]);
		}
		printf(" ;%lf\n", r[i]);
	}
	return;
}

void printMatrix(double** matrix, int noLines, int noColumns){
    int i,j;
    for(i = 0; i < LARGURA; i++){
        printf("|");
        for(j = 0; j < LARGURA; j++)
				printf(" %6.1lf ", matrix[i][j]);
        printf("|\n");
    }
}


