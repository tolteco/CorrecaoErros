#include <stdio.h>
#include <stdlib.h>

FILE *ARQ;
char arquivo[50];

void tab_base(){///       8  4  2  1      8  4  2  1
    int base[12][4] = { { 0, 0, 0, 1 }, { 0, 0, 1, 0 },
                        { 0, 0, 1, 1 }, { 0, 1, 0, 0 },
                        { 0, 1, 0, 1 }, { 0, 1, 1, 0 },
                        { 0, 1, 1, 1 }, { 1, 0, 0, 0 },
                        { 1, 0, 0, 1 }, { 1, 0, 1, 0 },
                        { 1, 0, 1, 1 }, { 1, 1, 0, 0 } };

}

int leitura(){
    int N;
    printf("Entrei em leitura = arquivo %s\n", arquivo);
    ARQ = fopen(arquivo,"r");
    fscanf (ARQ, "%i\n", &N);
    printf("---%i\n", N);
    return 0;
}

int escrita(){
    printf("Entrei em escrita\n");
    return 0;
}

int main( int argc, char *op[])  {
    int A = 0;
    if(argc == 3) {
        printf("arquivo = %s, opcao = %s\n", op[1], op[2]);
        strcpy(arquivo, op[1]);
        if (strcmp(op[2], "-r")==0){
            A = leitura();
        } else if (strcmp(op[2], "-w")==0){
            A = escrita();
        } else {
            printf("Opcao invalida\n");
        }
    }
    else if(argc > 2) {
        printf("Argumentos demais.\n");
    }
    else {
        printf("Argumentos de menos.\n");
    }
    return A;
}
