#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "automato.h"

AF AFcria(char *alfabeto){
    
}

AF AFdestroi(AF af){
    
}

void AFcriaEstado(AF af,int e,Bool inicial,Bool final){
    
}

void AFdestroiEstado(AF af,int e){
    
}

void AFcriaTransicao(AF af,int e1,char s,int e2){
    
}

void AFdestroiTransicao(AF af,int e1,char s,int e2){
    
}

Bool AFestadoInicial(AF af,int e){
    return af->estados[e].inicial;
}

Bool AFestadoFinal(AF af,int e){
    return af->estados[e].final;
}

Bool AFchecaAFD(AF af){
    
}

Bool AFchecaAFv(AF af){
    
}

int AFmoveAFD(AF af,int e,char s){
    
}

Lista AFfecho(AF af,Lista e,char s){
    
}

void AFsalva(AF af,char *nomeArquivo){
    
}

AF AFcarrega(char *nomeArquivo){
    
}

