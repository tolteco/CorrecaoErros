@ECHO OFF

ECHO Iniciando teste serial
OAC_P5.exe 1 > OAC_P5_OUT.txt

ECHO Iniciando teste paralelo com 2 threads
OAC_P5.exe 2 >> OAC_P5_OUT.txt

ECHO Iniciando teste paralelo com 4 threads
OAC_P5.exe 4 >> OAC_P5_OUT.txt

ECHO Finalizando...