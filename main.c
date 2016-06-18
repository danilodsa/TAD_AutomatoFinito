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
int main(int argc, char** argv) {

    char alfabeto[] = "ab";
    
    AF automato;
    estado aux;
    
    automato = AFcria(alfabeto);
    
    AFcriaEstado(automato,0,TRUE,FALSE);
    AFcriaEstado(automato,1,FALSE,FALSE);
    AFcriaEstado(automato,2,FALSE,FALSE);
    AFcriaEstado(automato,3,FALSE,FALSE);
    AFcriaEstado(automato,4,FALSE,TRUE);
    
    AFcriaTransicao(automato,0,'a',1);
    AFcriaTransicao(automato,0,'b',2);
    AFcriaTransicao(automato,1,'a',1);
    AFcriaTransicao(automato,1,'b',3);
    AFcriaTransicao(automato,2,'a',1);
    AFcriaTransicao(automato,2,'a',2);
    AFcriaTransicao(automato,3,'a',1);
    AFcriaTransicao(automato,3,'b',4);
    AFcriaTransicao(automato,4,'a',1);
    AFcriaTransicao(automato,4,'b',2);
        
    /*
    AFcriaTransicao(automato,1,'a',2);
    AFcriaTransicao(automato,1,'b',3);
    AFcriaTransicao(automato,2,'a',2);
    AFcriaTransicao(automato,2,'b',4);
    AFcriaTransicao(automato,3,'a',2);
    AFcriaTransicao(automato,3,'b',3);
    AFcriaTransicao(automato,4,'a',2);
    AFcriaTransicao(automato,4,'b',5);
    AFcriaTransicao(automato,5,'a',2);
    AFcriaTransicao(automato,5,'b',3);
    */    
    
    return (EXIT_SUCCESS);
}