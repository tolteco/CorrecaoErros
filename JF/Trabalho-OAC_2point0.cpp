#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

FILE *ARQ;
FILE *ARQ2;
char arquivo[50], arquivo3[50];
char L, C1, C2;
char *arquivo2;
int P[13], X[13];

//http://stackoverflow.com/questions/117844/converting-string-of-1s-and-0s-into-binary-value
//Maybe useful

///Função para transformar um char em uma string representando-o em forma binária.
///param: zeroSignificativo - Verdadeiro para incluir zeros mais siginificativos.
///Ex.: 01111111
string getStringBinary (unsigned char byte, bool zeroSignificativo){
    char output[9];
    itoa(byte, output, 2);

    if (!zeroSignificativo) return string(output);

    string ret = string(output);
    string zero="";
    while (ret.length()+zero.length() != 8)
        zero += '0';

    ret = zero + ret;

    //printf("%s\n", output);

    return ret;
}

///Overload para sempre mostrar os zeros mais significativos, caso existam
string getStringBinary (unsigned char byte){ //Com zeros mais significativos
   return getStringBinary (byte,true);
}

///Retorna posição baseada em quatro valores que "emulam binário"
int binGetPos (int x0, int x1, int x3, int x7){
    int ret = 0;
    if (x0==1) ret += 1;
    if (x1==1) ret += 2;
    if (x3==1) ret += 4;
    if (x7==1) ret += 8;
    return ret;
}

void AP() { ///Zera os vetores
    int i;
    for (i = 0; i < 13; i++) {
        X[i] = 0;
        P[i] = 0;
    }
}

int doublecheck() { ///Checa dois erros
    /*int A = 0;
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
    }*/
    int parityAnt = P[0] ^ P[1] ^ P[2] ^ P[3] ^ P[4] ^ P[5] ^ P[6] ^ P[7] ^ P[8] ^ P[9] ^ P[10] ^ P[11];
    int parityAtu = X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11];

    if (parityAnt != parityAtu){
        printf ("Paridade do bit G invalida!");
        return 1;
    }

    return 0;
}

int correcao() { ///Corrige (tenta) um erro
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

    printf("Bits de paridade: %d %d %d %d\n", X[7], X[3], X[1], X[0]);

    N = X[0] + (X[1]*2) + (X[3]*4) + (X[7]*8); //binGetPos(X[0], X[1], X[3], X[7])

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

int leitura() { ///Lê arquivo "corrigido"
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

        //Para prevalecer em ordem
        string data = getStringBinary(C2) + getStringBinary(C1);

        //printf("C2Lido = %d\n", (8 & C2));

        for (int i=0; i<13; i++)
            P[i] = data.at(i) - '0'; //Pegar todos os bits, menos os "de desperdício"

        X[2] = P[2];
        X[4] = P[4];
        X[5] = P[5];
        X[6] = P[6];
        X[8] = P[8];
        X[9] = P[9];
        X[10] = P[10];
        X[11] = P[11];
        //Copy data bits

        if ((X[2] ^ X[4] ^ X[6] ^ X[8] ^ X[10]) != 0) { //C1
            X[0] = 1;
        }
        if ((X[2] ^ X[5] ^ X[6] ^ X[9] ^ X[10]) != 0) { //C2
            X[1] = 1;
        }
        if ((X[4] ^ X[5] ^ X[6] ^ X[11]) != 0) { //C4
            X[3] = 1;
        }
        if ((X[8] ^ X[9] ^ X[10] ^ X[11]) != 0) { //C8
            X[7] = 1;
        }
        if ((X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //Bit G
            X[12] = 1; //But why? Não tem que tentar flip primeiro e depois comparar G?
        }
        //Get new correction bits

        if (X[0]!=0 || X[1]!=0 || X[3]!=0 || X[7]!=0) { //Qualquer posição com 1, indica erro
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

int escrita() { ///Escreve arquivo protegido por Hamming
    int i;
    int abst = 1; //Abstração de posição

    ARQ = fopen(arquivo, "r");
    arquivo2 = strcat(arquivo, "1");
    ARQ2 = fopen(arquivo2, "w");
    if (ARQ == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 1;
    }

    printf("Lido:\n"); //Lê um char, efetua ops. e salva dois chars
    while (!feof(ARQ)) {
        fscanf(ARQ, "%c", &L);
        printf("%c", L); //L é o char lido
        AP(); //1 2 4 8 são bits de correção
              //3 5 6 7 9 10 11 12 são dados
        int ham[12];
        string data = getStringBinary(L);

        X[3-abst]  = data.at(0) - '0';
        X[5-abst]  = data.at(1) - '0'; //Para cast para int
        X[6-abst]  = data.at(2) - '0';
        X[7-abst]  = data.at(3) - '0';
        X[9-abst]  = data.at(4) - '0';
        X[10-abst] = data.at(5) - '0';
        X[11-abst] = data.at(6) - '0';
        X[21-abst] = data.at(7) - '0';
        //End data bits

        if ((X[3-abst] ^ X[5-abst] ^ X[7-abst] ^ X[9-abst] ^ X[11-abst]) > 0) { //C1
            X[1-abst] = 1;
        }
        if ((X[3-abst] ^ X[6-abst] ^ X[7-abst] ^ X[10-abst] ^ X[11-abst]) > 0) { //C2
            X[2-abst] = 1;
        }
        if ((X[5-abst] ^ X[6-abst] ^ X[7-abst] ^ X[12-abst]) > 0) { //C4
            X[4-abst] = 1;
        }
        if ((X[9-abst] ^ X[10-abst] ^ X[11-abst] ^ X[12-abst]) > 0) { //C8
            X[8-abst] = 1;
        }
        if ((X[0] ^ X[1] ^ X[2] ^ X[3] ^ X[4] ^ X[5] ^ X[6] ^ X[7] ^ X[8] ^ X[9] ^ X[10] ^ X[11]) > 0) { //Bit G
            X[13-abst] = 1;
        }
        //End correction bits

        printf(" - X escrito\n");
        printf("G  M8  M7  M6  M5  C8  M4  M3  M2  C4  M1  C2  C1\n");
        for (i = 12; i > 0; i--) {
            printf("%d - ", X[i]);
        }
        printf("%d\n", X[0]);
        //End informação para o usuário

        C1 = X[0] + (X[1]*2) + (X[2]*4) + (X[3]*8) + (X[4]*16) + (X[5]*32) + (X[6]*64) + (X[7]*128); //Transformação em char
        C2 = X[8] + (X[9]*2) + (X[10]*4) + (X[11]*8) + (X[12]*16); //Transformação em char
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
