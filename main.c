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
        
    AF automatoA,automatoB;
    char comando;
    char Aux1[20],buff[10];
    
    do
    {
        printf("C - Carregar automato A\n");
        printf("V - Carregar automato B\n");
        printf("M - Manipular automato A\n");
        printf("N - Manipular automato B\n");
        printf("S - Salvar automato em um arquivo\n");
        printf("X - Menu de funções\n");
        printf("Q - Sair\n");
        
        scanf("%c",&comando);
        
        system("clear");
        
        switch(comando)
        {
            case 'C':
                fgets(buff,10,stdin);
                printf("Nome do arquivo: ");
                scanf("%s",Aux1);
                automatoA = AFcarrega(Aux1);
            break;
            case 'V':
                fgets(buff,10,stdin);
                printf("Nome do arquivo: ");
                scanf("%s",Aux1);
                automatoB = AFcarrega(Aux1);
            break;
            case 'M':
            break;
            case 'N':
            break;
            case 'S':
                fgets(buff,10,stdin);
                printf("A - automato A\nB - automato B\n");
                scanf("%c",&comando);
                printf("Nome do arquivo: ");
                scanf("%s",Aux1);
                switch(comando)
                {
                    case 'A' :
                        AFsalva(automatoA,Aux1);
                        break;
                    case 'B' :
                        AFsalva(automatoB,Aux1);
                        break;
                }
            break;
            case 'X':
                printf("Checa AFD:\n");
                printf("Checa AFv:\n");
                printf("Checa Equivalência:\n");
                printf("Checa estado inicial\n");
                printf("Checa estado final:\n");
                printf("Minimiza Automato: \n");
            break;
            default:
                ;
        }
    }while(comando!='Q');
    
    
    return (EXIT_SUCCESS);
}