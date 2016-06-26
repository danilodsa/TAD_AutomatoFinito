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
    char comando,comando2;
    char Aux1[20],buff[10];
    estado aux;
    Lista pAux;
    int auxX,i,a,b;
    
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
                fgets(buff,10,stdin);
                printf("A - Checa AFD:\n");
                printf("B - Checa AFv:\n");
                printf("C - Checa Equivalência:\n");
                printf("D - Checa estado inicial\n");
                printf("E - Checa estado final:\n");
                printf("F - Minimiza Automato: \n");
                printf("G - Destroi Estado: \n");
                printf("H - Destroi Transicao: \n");
                scanf("%c",&comando);
                switch(comando)
                {
                    case 'A':
                        fgets(buff,10,stdin);
                        printf("A - automato A\n");
                        printf("B - automato A\n");
                        scanf("%c",&comando);
                        switch(comando)
                        {
                            case 'A':
                                if(AFchecaAFD(automatoA))
                                    printf("TRUE\n");
                                else
                                    printf("FALSE\n");
                                break;
                            case 'B':
                                if(AFchecaAFD(automatoB))
                                    printf("TRUE\n");
                                else
                                    printf("FALSE\n");
                                break;
                        }
                        fgets(buff,10,stdin);
                        break;
                    case 'B':
                        break;
                    case 'C':
                        break;
                    case 'D':
                        break;
                    case 'E':
                        break;
                    case 'F':
                        break;
                    case 'G':
                        fgets(buff,10,stdin);
                        printf("A - automato A\n");
                        printf("B - automato A\n");
                        scanf("%c",&comando);
                        switch(comando)
                        {
                            case 'A':
                                printf("Deletar estado (indique o numero):\n");
                                for(aux=automatoA->estados;aux!=NULL;aux=aux->prox)
                                {
                                    printf("%i\n",aux->numero);
                                }
                                printf("estado: ");
                                scanf("%i",&auxX);
                                AFdestroiEstado(automatoA,auxX);
                                break;
                            case 'B':
                                printf("Deletar estado (indique o numero):\n");
                                for(aux=automatoB->estados;aux!=NULL;aux=aux->prox)
                                {
                                    printf("%i\n",aux->numero);
                                }
                                printf("estado: ");
                                scanf("%i",&auxX);
                                AFdestroiEstado(automatoA,auxX);
                                break;
                        }
                        fgets(buff,10,stdin);
                        break;
                    case 'H':
                        fgets(buff,10,stdin);
                        printf("A - automato A\n");
                        printf("B - automato A\n");
                        scanf("%c",&comando);
                        switch(comando)
                        {
                            case 'A':
                                for(aux=automatoA->estados;aux!=NULL;aux=aux->prox)
                                {
                                    for(i=0;i<automatoA->num_simbolos;i++)
                                    {
                                        pAux = aux->move[i];
                                        while(pAux!=NULL)
                                        {
                                            printf("%i %c %i\n",aux->numero,automatoA->alfabeto[i],pAux->numero);
                                            pAux = pAux->prox;
                                        }
                                    }
                                }
                                fgets(buff,10,stdin);
                                scanf("%i %c %i",&a,&comando2,&b);
                                AFdestroiTransicao(automatoA,a,comando2,b);
                                break;
                            case 'B':
                                break;
                        }
                        break;
                }
            break;
            default:
                ;
        }
    }while(comando!='Q');

    
    return (EXIT_SUCCESS);
}