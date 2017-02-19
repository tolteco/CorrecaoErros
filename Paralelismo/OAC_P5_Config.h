#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

///'##::::'##:'####::'######::::::'######::'##::::'##:'##::: ##:'########:
/// ##:::: ##:. ##::'##... ##::::'##... ##: ##:::: ##: ###:: ##:... ##..::
/// ##:::: ##:: ##:: ##:::..::::: ##:::..:: ##:::: ##: ####: ##:::: ##::::
/// #########:: ##:: ##::::::::::. ######:: ##:::: ##: ## ## ##:::: ##::::
/// ##.... ##:: ##:: ##:::::::::::..... ##:. ##:: ##:: ##. ####:::: ##::::
/// ##:::: ##:: ##:: ##::: ##::::'##::: ##::. ## ##::: ##:. ###:::: ##::::
/// ##:::: ##:'####:. ######:::::. ######::::. ###:::: ##::. ##:::: ##::::
///..:::::..::....:::......:::::::......::::::...:::::..::::..:::::..:::::
///'########::'########:::::'###:::::'######:::'#######::'##::: ##:'########::'######::
/// ##.... ##: ##.... ##:::'## ##:::'##... ##:'##.... ##: ###:: ##: ##.....::'##... ##:
/// ##:::: ##: ##:::: ##::'##:. ##:: ##:::..:: ##:::: ##: ####: ##: ##::::::: ##:::..::
/// ##:::: ##: ########::'##:::. ##: ##::::::: ##:::: ##: ## ## ##: ######:::. ######::
/// ##:::: ##: ##.. ##::: #########: ##::::::: ##:::: ##: ##. ####: ##...:::::..... ##:
/// ##:::: ##: ##::. ##:: ##.... ##: ##::: ##: ##:::: ##: ##:. ###: ##:::::::'##::: ##:
/// ########:: ##:::. ##: ##:::: ##:. ######::. #######:: ##::. ##: ########:. ######::

//(HIC SVNT DRACONES) ^^^^

#ifndef OAC_P5_CONFIG_H
#define OAC_P5_CONFIG_H

#ifdef WIN32 //Win

double** getData(int noLines, int noColumns){
    srand (time(NULL));
    static double value = 20;
    value -= rand() % 3 + 1;

    int i,j;
    double **matrix = (double **) malloc(noLines * sizeof(double*));
	for(i = 0; i < noLines; i++){
		matrix[i] = (double *) malloc(noColumns * sizeof(double));
	}

    #pragma omp parallel shared(i, matrix) private(j)
	{
		#pragma omp for
		for(i = 0; i < noLines; i++)
			for(j = 0; j < noColumns; j++)
				matrix[i][j] = value;
	}
	return matrix;
}

#else //Unix

double** getData(int noLines, int noColumns){
    int i,j;
    double **matrix = (double **) malloc(noLines * sizeof(double*));
	for(i = 0; i < noLines; i++){
		matrix[i] = (double *) malloc(noColumns * sizeof(double));
	}

    #pragma omp parallel shared(i, matrix1, matrix2) private(j)
	{
	    #pragma omp for
        for(i = 0; i < noLines; i++)
            for(j = 0; j < noColumns; j++)
                matrix1[i][j] = rand_r(&threadId) % 100;
	}
}
#endif

#endif
