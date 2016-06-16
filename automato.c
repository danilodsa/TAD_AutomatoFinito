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
        
        /*define o tamanho do vetor de alfabeto
         *de acordo com a quantidade de simbolos*/
        aux->alfabeto = (char*) malloc(aux->num_simbolos*sizeof(char));
        
        /*passa o alfabeto informado para a estrutura do Automato*/
        strcpy(aux->alfabeto,alfabeto);
        
        /*define o numero de estados para zero, uma vez que nao possui
         nenhum estado*/
        aux->num_estados = 0;
        
        /*Nao sei o q eu fiz aqui*/
        aux->estados->inicial = FALSE;
        
        /*Nao sei o q eu fiz aqui*/
        aux->estados->final = FALSE;
        
        /*seta o ponteiro para NULL ja que incialmente nao possui nehum
         estado*/
        aux->estados->move = NULL;
        
        /*numero de estados total*/
        aux->estados->numero = 0;
        
    }
    return NULL;
}

AF AFdestroi(AF af)
{
    if(af!=NULL){
        /*controle de laco*/
        int i;
        
        /*libera a string de alfabeto*/
        free(af->alfabeto);
        
        /*libera a lista de estados*/
        for(i=0;i<af->num_estados;i++)
        {
            /*destroi o estado */
            AFdestroiEstado(af,i);
        }
        
        /*libera a estrutura primaria*/
        free(af);
    }
}

void AFcriaEstado(AF af,int e,Bool inicial,Bool final)
{
    estado aux;
    estado novo;
    /*Aux recee o primeiro estado da lista, para percorre-la*/
    aux = af->estados;
    
    while(aux->prox != NULL)
    {
        aux = aux->prox;
    }
    novo->inicial = inicial;
    novo->final = final;
    novo->numero = e;
    aux->prox = novo;
    
    /*VERIFICAR LANCE DE CRIACAO DA LISTA DE MOVIMENTOS*/
    
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
    estado aux;
    
    /*aux recebe o primeiro estado da lista de estados*/
    aux = af->estados;
    /*Laco para percorrer a lista de estados*/
    while(aux->prox != NULL)
    {
        /*Busca o estado*/
        if(aux->numero == e)
        {
            /*Apos encontrar o estado, informa se ele e inicial*/
            return aux->inicial;
        }
        aux = aux->prox;
    }
    
}

Bool AFestadoFinal(AF af,int e)
{
    estado aux;   
    /*aux recebe o primeiro estado da lista de estados*/
    aux = af->estados;
    /*Laco para percorrer a lista de estados*/
    while(aux->prox != NULL)
    {
        /*Busca o estado*/
        if(aux->numero == e)
        {
            /*Apos encontrar o estado, informa se ele e final*/
            return aux->final;
        }
        aux = aux->prox;
    }
}

Bool AFchecaAFD(AF af)
{

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

}