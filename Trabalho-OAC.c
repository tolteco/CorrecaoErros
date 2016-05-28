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

int testeC(){//Separar os testes C1, C2, C4, C8 todos nesta função "testeC", ou em funções separadas?
    int i, T1[12], G; //T é a tabela com as 12 variáveis
    int V;//Passar em uma variável 8 bits (Pode mudar a variavel V e seu tipo se preciso)

    for(i=0;i<12;i++){
        if (//Se T1[0], T1[1], T1[3], T1[7], fazer o xor (deixar em branco essas posições) ){

        }
        else{//Se não forem as posições do if colocar a variavel lida V.

        }
    }
    //Verificar estes xor
    T1[0]=T1[2]^T1[4]^T1[6]^T1[8]^T1[10];//Acredito q o xor é assim e que deve ser feito o xor entre essas posições
    T1[1]=T1[2]^T1[5]^T1[6]^T1[9]^T1[10];
    T1[3]=T1[4]^T1[5]^T1[6]^T1[11];
    //T1[7]=T1[2]^T1[4]^T1[6]^T1[8]^T1[10]; Entre quem sera feito estes xor?

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
