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
    
    resulta = AFintercessao(autoA,autoB);
    
    return (EXIT_SUCCESS);
}
