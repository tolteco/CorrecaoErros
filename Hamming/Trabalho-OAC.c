#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *ARQ;
FILE *ARQ2;
char arquivo[50], arquivo3[50];
char L, C1, C2;
char *arquivo2;
int P[13], X[13];

void AP() {
    int i;
    for (i = 0; i < 13; i++) {
        X[i] = 0;
        P[i] = 0;
    }
}

int doublecheck() {
    int A = 0;
    X[0] = 0;
    X[1] = 0;
    X[3] = 0;
    X[7] = 0;
    X[12] = 0;
    if ((X[2] ^ X[4] ^ X[6] ^ X[8] ^ X[10]) != 0) { //C1
        X[0] = 1;
    }
    if ((X[2] ^ X[5] ^ X[6] ^ X[9] ^ X[10]) != 0) { //C2
        X[1] = 1;
    }
    printf("C4 = %d\n", (X[4] ^ X[5] ^ X[6] ^ X[11]));
    if ((X[4] ^ X[5] ^ X[6] ^ X[11]) != 0) { //C4
        X[3] = 1;
    }
    printf("C8 = %d\n", (X[8] ^ X[9] ^ X[10] ^ X[11]));
    fflush(stdout);
    if ((X[8] ^ X[9] ^ X[10] ^ X[11]) != 0) { //C8
        X[7] = 1;
    }
    if ((X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //Bit G
        X[12] = 1;
    }
    if (!(X[0] == P[0] && X[1] == P[1] && X[3] == P[3] && X[7] == P[7] && X[12] == P[12])) {
        printf("Erro na correcao\n");
        return 1;
    }
    return 0;
}

int correcao() {
    int N, i, A;
    printf("Correcoes sao necessarias\n");
    printf("G  M8  M7  M6  M5  C8  M4  M3  M2  C4  M1  C2  C1\n");
    for (i = 12; i > 0; i--) {
        printf("%d - ", X[i]);
    }
    printf("%d\n", X[0]);
    for (i = 12; i > 0; i--) {
        printf("%d - ", P[i]);
    }
    printf("%d\n", P[0]);
    printf("Bits: %d %d %d %d\n", X[7], X[3], X[1], X[0]);
    N = X[0] + (X[1]*2) + (X[3]*4) + (X[7]*8);
    printf("Flipagem do bit: %d\n", N);
    if (X[N] == 0) {
        X[N] = 1;
    } else if (X[N] == 1) {
        X[N] = 0;
    }
    A = doublecheck();
    for (i = 12; i > 0; i--) {
        printf("%d - ", X[i]);
    }
    printf("%d\n", X[0]);
    if (A == 1) {
        return 1;
    }
    printf("%d\n", X[0]);
    return 0;
}

int leitura() {
    int K, i, A = 0;
    ARQ = fopen(arquivo, "r");
    if (ARQ == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }
    K = strlen(arquivo);
    for (i = 0; i < (K - 1); i++) {
        arquivo3[i] = arquivo[i];
    }
    arquivo3[K - 1] = '\0';
    ARQ2 = fopen(arquivo3, "w");
    printf("Escrito:\n");
    while (!feof(ARQ)) {
        AP();
        fscanf(ARQ, "%c", &C1);
        fscanf(ARQ, "%c", &C2);
        if ((1 & C2) > 0) {
            P[0] = 1;
        }
        if ((2 & C2) > 0) {
            P[1] = 1;
        }
        if ((4 & C2) > 0) {
            P[2] = 1;
        }
        printf("C2Lido = %d\n", (8 & C2));
        if ((8 & C2) > 0) {
            P[3] = 1;
        }
        if ((16 & C2) > 0) {
            P[4] = 1;
        }
        if ((32 & C2) > 0) {
            P[5] = 1;
        }
        if ((64 & C2) > 0) {
            P[6] = 1;
        }
        if ((128 & C2) > 0) {
            P[7] = 1;
        }
        if ((1 & C1) > 0) {
            P[8] = 1;
        }
        if ((2 & C1) > 0) {
            P[9] = 1;
        }
        if ((4 & C1) > 0) {
            P[10] = 1;
        }
        if ((8 & C1) > 0) {
            P[11] = 1;
        }
        if ((16 & C1) > 0) {
            P[12] = 1;
        }
        X[2] = P[2];
        X[4] = P[4];
        X[5] = P[5];
        X[6] = P[6];
        X[8] = P[8];
        X[9] = P[9];
        X[10] = P[10];
        X[11] = P[11];
        if ((X[2] ^ X[4] ^ X[6] ^ X[8] ^ X[10]) != 0) { //C1
            X[0] = 1;
        }
        if ((X[2] ^ X[5] ^ X[6] ^ X[9] ^ X[10]) != 0) { //C2
            X[1] = 1;
        }
        printf("C4 = %d\n", (X[4] ^ X[5] ^ X[6] ^ X[11]));
        if ((X[4] ^ X[5] ^ X[6] ^ X[11]) != 0) { //C4
            X[3] = 1;
        }
        printf("C8 = %d\n", (X[8] ^ X[9] ^ X[10] ^ X[11]));
        fflush(stdout);
        if ((X[8] ^ X[9] ^ X[10] ^ X[11]) != 0) { //C8
            X[7] = 1;
        }
        if ((X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //Bit G
            X[12] = 1;
        }
        if (!(X[0] == P[0] && X[1] == P[1] && X[3] == P[3] && X[7] == P[7] && X[12] == P[12])) {
            A = correcao();
        }
        if (A == 1) {
            return 1;
        }
        L = X[2] + (X[4]*2) + (X[5]*4) + (X[6]*8) + (X[8]*16) + (X[9]*32) + (X[10]*64) + (X[11]*128);
        fprintf(ARQ2, "%c", L);
        printf("[[%c]]", L);
    }
    return 0;
}

int escrita() {
    int i;
    ARQ = fopen(arquivo, "r");
    arquivo2 = strcat(arquivo, "1");
    ARQ2 = fopen(arquivo2, "w");
    if (ARQ == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }
    printf("Lido:\n");
    while (!feof(ARQ)) {
        fscanf(ARQ, "%c", &L);
        printf("%c", L);
        AP();
        if ((1 & L) > 0) { //M1
            X[2] = 1;
        }
        if ((2 & L) > 0) { //M2
            X[4] = 1;
        }
        if ((4 & L) > 0) { //M3
            X[5] = 1;
        }
        if ((8 & L) > 0) { //M4
            X[6] = 1;
        }
        if ((16 & L) > 0) { //M5
            X[8] = 1;
        }
        if ((32 & L) > 0) { //M6
            X[9] = 1;
        }
        if ((64 & L) > 0) { //M7
            X[10] = 1;
        }
        if ((128 & L) > 0) { //M8
            X[11] = 1;
        }
        if ((X[2] ^ X[4] ^ X[6] ^ X[8] ^ X[10]) > 0) { //C1
            X[0] = 1;
        }
        if ((X[2] ^ X[5] ^ X[6] ^ X[9] ^ X[10]) > 0) { //C2
            X[1] = 1;
        }
        if ((X[4] ^ X[5] ^ X[6] ^ X[11]) > 0) { //C4
            X[3] = 1;
        }
        if ((X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //C8
            X[7] = 1;
        }
        if ((X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //Bit G
            X[12] = 1;
        }
        printf(" - X escrito\n");
        printf("G  M8  M7  M6  M5  C8  M4  M3  M2  C4  M1  C2  C1\n");
        for (i = 12; i > 0; i--) {
            printf("%d - ", X[i]);
        }
        printf("%d\n", X[0]);
        C1 = X[0] + (X[1]*2) + (X[2]*4) + (X[3]*8) + (X[4]*16) + (X[5]*32) + (X[6]*64) + (X[7]*128);
        C2 = X[8] + (X[9]*2) + (X[10]*4) + (X[11]*8) + (X[12]*16);
        fprintf(ARQ2, "%c%c", C2, C1);
    }
    return 0;
}

int main(int argc, char *op[]) {
    int A = 0, i;
    if (argc == 3) {
        strcpy(arquivo, op[1]);
        if (strcmp(op[2], "-r") == 0) {
            A = leitura();
        } else if (strcmp(op[2], "-w") == 0) {
            A = escrita();
        } else {
            printf("Opcao invalida\n");
        }
    } else if (argc > 2) {
        printf("Argumentos demais.\n");
    } else {
        printf("Argumentos de menos.\n");
    }
    return A;
}
