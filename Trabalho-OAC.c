#include <stdio.h>
#include <stdlib.h>

void tab_base(){///       8  4  2  1      8  4  2  1
    int base[12][4] = { { 0, 0, 0, 1 }, { 0, 0, 1, 0 },
                        { 0, 0, 1, 1 }, { 0, 1, 0, 0 },
                        { 0, 1, 0, 1 }, { 0, 1, 1, 0 },
                        { 0, 1, 1, 1 }, { 1, 0, 0, 0 },
                        { 1, 0, 0, 1 }, { 1, 0, 1, 0 },
                        { 1, 0, 1, 1 }, { 1, 1, 0, 0 } };

}

int main( int argc, char *op[])  {

   if( argc == 3 ) {
      printf("arquivo = %s, opcao = %s\n", op[1], op[2]);
   }
   else if( argc > 2 ) {
      printf("Argumentos demais.\n");
   }
   else {
      printf("Argumentos de menos.\n");
   }
}
