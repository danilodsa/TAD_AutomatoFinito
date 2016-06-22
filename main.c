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
        
    AF automato;
    
    automato = AFcarrega("af3.txt");
    AFsalva(automato,"saida3.txt");
    
    AFdestroi(automato);
    
    
    return (EXIT_SUCCESS);
}