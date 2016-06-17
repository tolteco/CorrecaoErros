#include <stdio.h>
#include <stdlib.h>

FILE *IN;
FILE *OUT;
FILE *OUTCSV;
double TM[5], TT[5];
double MM, MT, MM2, MO;

int main(){
  int l, c, E, A=0;
  IN = fopen("Log.txt","r");
  if (IN == NULL){
    printf("Erro na abertura do arquivo de leitura\n");
    return 1;
  }
  OUT = fopen("Results.txt","w");
  if (OUT == NULL){
    printf("Erro na abertura do arquivo de escrita de relatorio\n");
    return 1;
  }
  OUTCSV = fopen("Results.csv","w");
  if (OUTCSV == NULL){
    printf("Erro na abertura do arquivo csv\n");
    return 1;
  }
  fprintf(OUTCSV, ",MultConvencional,MultTransposta,ConvTransposta,TotalTransposta,Dif(Percent)\n");
  while (!feof(IN))
  {
    fscanf (IN, "%i\n", &l);
    fscanf (IN, "%i\n", &c);
    fscanf (IN, "%lf\n", &TM[0]);
    fscanf (IN, "%lf\n", &TM[1]);
    fscanf (IN, "%lf\n", &TM[2]);
    fscanf (IN, "%lf\n", &TM[3]);
    fscanf (IN, "%lf\n", &TM[4]);
    MM = (TM[0]+TM[1]+TM[2]+TM[3]+TM[4])/5;
    fflush(stdout);
    fscanf (IN, "%lf\n", &TT[0]);
    fscanf (IN, "%lf\n", &TM[0]);
    fscanf (IN, "%lf\n", &TT[1]);
    fscanf (IN, "%lf\n", &TM[1]);
    fscanf (IN, "%lf\n", &TT[2]);
    fscanf (IN, "%lf\n", &TM[2]);
    fscanf (IN, "%lf\n", &TT[3]);
    fscanf (IN, "%lf\n", &TM[3]);
    fscanf (IN, "%lf\n", &TT[4]);
    fscanf (IN, "%lf\n", &TM[4]);
    MT = (TT[0]+TT[1]+TT[2]+TT[3]+TT[4])/5;
    MM2 = (TM[0]+TM[1]+TM[2]+TM[3]+TM[4])/5;
    MO = MT+MM2;
    fprintf(OUT, "Para %ix%i\n", l, c);
    fprintf(OUTCSV, "250x250,");
    fprintf(OUT, "Tempo de execucao da multipicacao convencional %lf\n", MM);
    fprintf(OUTCSV, "%lf,", MM);
    fprintf(OUT, "Tempo de execucao da multipicacao transposta %lf\n", MM2);
    fprintf(OUTCSV, "%lf,", MM2);
    fprintf(OUT, "Tempo de execucao da conversao para transposta %lf\n", MT);
    fprintf(OUTCSV, "%lf,", MT);
    fprintf(OUT, "Tempo de execucao da execucao total da transposta %lf\n", MO);
    fprintf(OUTCSV, "%lf,", MO);
    fprintf(OUT, "O tempo da multiplicacao via transposta corresponde a %lf%% do tempo da multipicacao convencional\n", ((MO/MM)*100));
    fprintf(OUTCSV, "%lf\n", ((MO/MM)*100));
  }
}
