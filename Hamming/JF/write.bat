@ECHO OFF
SET /p fullprint=Mostrar todos os dados [y/n]?: 

if %fullprint% EQU y goto FullPrint

Trabalho-OAC_2point0.exe A.txt -w
goto exit

:FullPrint
Trabalho-OAC_2point0_PrintToUser.exe A.txt -w

:exit
pause