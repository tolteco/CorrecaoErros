#include <stdio.h>
#include <stdlib.h>

FILE *IN;
FILE *OUT;
FILE *OUTCSV;
int TM[5], TT[5];
double MM, MT, MM2, MO;

int main(){
  int O, E, A=0;
  IN = fopen("Log.txt","r");
  OUT = fopen("Results.txt","w");
  OUTCSV = fopen("Results.csv","w");
  fprintf(OUTCSV, ",MultConvencional,MultTransposta,ConvTransposta,TotalTransposta,Dif(Percent)\n");
  while (!feof(IN))
  {
    fscanf (IN, "%i\n", &O);
    fscanf (IN, "%i\n", TM[0]);
    fscanf (IN, "%i\n", TM[1]);
    fscanf (IN, "%i\n", TM[2]);
    fscanf (IN, "%i\n", TM[3]);
    fscanf (IN, "%i\n", TM[4]);
    MM = (TM[0]+TM[1]+TM[2]+TM[3]+TM[4])/5;
    fscanf (IN, "%i\n", TT[0]);
    fscanf (IN, "%i\n", TT[1]);
    fscanf (IN, "%i\n", TT[2]);
    fscanf (IN, "%i\n", TT[3]);
    fscanf (IN, "%i\n", TT[4]);
    fscanf (IN, "%i\n", TM[0]);
    fscanf (IN, "%i\n", TM[1]);
    fscanf (IN, "%i\n", TM[2]);
    fscanf (IN, "%i\n", TM[3]);
    fscanf (IN, "%i\n", TM[4]);
    MT = (TT[0]+TT[1]+TT[2]+TT[3]+TT[4])/5;
    MM2 = (TM[0]+TM[1]+TM[2]+TM[3]+TM[4])/5;
    MO = MT+MM2;
    fprintf(OUT, "Para %ix%i\n", O, O);
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
