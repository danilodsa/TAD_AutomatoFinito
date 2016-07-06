/* 
 * File:   main.c
 * Author: daniloalves
 *
 * Created on 14 de Junho de 2016, 01:33
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automato.h"

/*
 * 
 */

int func(char* funcao);
Bool identifica(char* valor);

int main(int argc, char** argv) {
   
    AF autoA,autoB;
    AF resulta;
    
    autoA = AFcarrega("af.txt");
    autoB = AFcarrega("af4.txt");
    
    resulta = AFconcatenacao(autoA,autoB);
    
    AFsalva(resulta,"taqui.txt");
    
    return (EXIT_SUCCESS);
}

int func(char* funcao)
{
    char buff[10];
    //gets(buff,10,stdin);
    
    if(strcmp(funcao,"AFcarrega")==0)
        return 1;
    if(strcmp(funcao,"AFchecaAFD")==0)
        return 2;
    if(strcmp(funcao,"AFchecaAFV")==0)
        return 3;
    if(strcmp(funcao,"AFcria")==0)
        return 4;
    if(strcmp(funcao,"AFcriaEstado")==0)
        return 5;
    if(strcmp(funcao,"AFcriaTransicao")==0)
        return 6;
    if(strcmp(funcao,"AFdestroi")==0)
        return 7;
    if(strcmp(funcao,"AFdestroiEstado")==0)
        return 8;
    if(strcmp(funcao,"AFdestroiTransicao")==0)
        return 9;
    if(strcmp(funcao,"AFequiv")==0)
        return 10;
    if(strcmp(funcao,"AFestadoFinal")==0)
        return 11;
    if(strcmp(funcao,"AFestadoInicial")==0)
        return 12;
    if(strcmp(funcao,"AFfechamento")==0)
        return 13;
    if(strcmp(funcao,"AFfecho")==0)
        return 14;
    if(strcmp(funcao,"AFminimiza")==0)
        return 15;
    if(strcmp(funcao,"AFmoveAFD")==0)
        return 16;
    if(strcmp(funcao,"AFnegacao")==0)
        return 17;
    if(strcmp(funcao,"AFrenumera")==0)
        return 18;
    if(strcmp(funcao,"AFsalva")==0)
        return 19;
    if(strcmp(funcao,"AFuniao")==0)
        return 20;
    
    /*sair de forma segura*/
    if(strcmp(funcao,"SAIR")==0)
        return 0;
}

Bool identifica(char* valor){
    if(strcmp(valor,"TRUE")==0)
        return TRUE;
    else
        FALSE;
}
