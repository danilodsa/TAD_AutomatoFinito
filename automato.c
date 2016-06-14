#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"



AF AFcria(char *alfabeto)
{
    AF aux = (AF) malloc(sizeof(AF));
    
    if(aux!=NULL)
    {
        /*define a quantidade de simbolos de acordo com o alfabeto informado*/
        aux->num_simbolos = strlen(alfabeto);
        
        /*define o tamanho da string de acordo com o alfabeto informado*/
        aux->alfabeto = (char*) malloc(aux->num_simbolos*sizeof(char));
        
        /*passa o alfabeto informado para a estrutura alocada*/
        strcpy(aux->alfabeto,alfabeto);
        
        /*define o numero de estados para zero, uma vez que nao possui
         nenhum estado*/
        aux->num_estados = 0;
        
        aux->estados = NULL;
    }
    return NULL;
}

AF AFdestroi(AF af)
{
    
    
    
    
    
    
    
}

void AFcriaEstado(AF af,int e,Bool inicial,Bool final)
{
    
}

void AFdestroiEstado(AF af,int e)
{
    
}

void AFcriaTransicao(AF af,int e1,char s,int e2)
{
    
}

void AFdestroiTransicao(AF af,int e1,char s,int e2)
{
    
}

Bool AFestadoInicial(AF af,int e)
{
    
}

Bool AFestadoFinal(AF af,int e)
{
    
}

Bool AFchecaAFD(AF af)
{
    /*******************/
}

Bool AFchecaAFv(AF af)
{
    
}

int AFmoveAFD(AF af,int e,char s)
{
    
}

Lista AFfecho(AF af,Lista e,char s)
{
    
}

void AFsalva(AF af,char *nomeArquivo)
{
    
}

AF AFcarrega(char *nomeArquivo)
{
    /*eita eita eita*/
}