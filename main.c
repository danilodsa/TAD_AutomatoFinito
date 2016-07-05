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
    AF automatoA,automatoB,automatoTemp;
    int op,p1,p2;
    char parametros[100],pA[256],pB[20],pC;
    Bool A,B;
    
    automatoA = NULL;
    automatoB = NULL;
    automatoTemp = NULL;
    
    do
    {
        printf("1 - AFcarrega\n");
        printf("2 - AFchecaAFD\n");
        printf("3 - AFchecaAFV\n");
        printf("4 - AFcria\n");
        printf("5 - AFcriaEstado\n");
        printf("6 - AFcriaTransicao\n");
        printf("7 - AFdestroi\n");
        printf("8 - AFdestroiEstado\n");
        printf("9 - AFdestroiTransicao\n");
        printf("10 - AFequiv\n");
        printf("11 - AFestadoFinal\n");
        printf("12 - AFestadoInicial\n");
        printf("13 - AFfechamento\n");
        printf("14 - AFfecho\n");
        printf("15 - AFminimiza\n");
        printf("16 - AFmoveAFD\n");
        printf("17 - AFnegacao\n");
        printf("18 - AFrenumera\n");
        printf("19 - AFsalva\n");
        printf("20 - AFuniao\n");
        printf("0 - Sair\n");
        scanf("%i",&op);
        fgets(parametros,100,stdin);
        switch(op)
        {
            /*AFcarrega*/
            case 1:
                sscanf(parametros,"%s",pA);
                automatoA = AFcarrega(pA);
                if(automatoA!=NULL)
                    printf(">>automato criado<<\n");
                break;
            /*AFchecaAFD*/
            case 2:
                if(AFchecaAFD(automatoA)==TRUE)
                    printf(">>TRUE<<\n");
                else
                    printf(">>FALSE<<\n");
                break;
            /*AFchecaAFV*/
            case 3:
                if(AFchecaAFv(automatoA)==TRUE)
                    printf(">>TRUE<<\n");
                else
                    printf(">>FALSE<<\n");
                break;
            /*AFcria cria automato (apenas estrutura automato)*/
            case 4:
                AFdestroi(automatoA);
                sscanf(parametros," %s",pA);
                automatoA = AFcria(pA);
                if(automatoA!=NULL)
                    printf(">>cabecalho de automato criado. Caso um automato foi carregado de um arquivo ele foi destruido<<\n");
                break;
            /*AFcriaestado*/
            case 5:
                sscanf(parametros," %i %s %s",&p1,pA,pB);
                A = identifica(pA);
                B = identifica(pB);
                AFcriaEstado(automatoA,p1,A,B);
                printf(">>estado criado<<\n");
                break;
            /*AFcriaTransicao*/
            case 6:
                sscanf(parametros," %i %c %i",&p1,&pC,&p2);
                AFcriaTransicao(automatoA,p1,pC,p2);
                printf(">>transicao criada<<\n");
                break;
            /*AFdestroi destroi o automato*/
            case 7:
                AFdestroi(automatoA);
                printf(">>automato principal destruido<<\n");
                break;
            /*AFdestroiEstado*/
            case 8:
                sscanf(parametros," %i",&p1);
                AFdestroiEstado(automatoA,p1);
                printf(">>estado %i destruido<<",p1);
                break;
            /*AFdestroiTransicao*/
            case 9:
                sscanf(parametros," %i %c %i",&p1,&pC,&p2);
                AFdestroiTransicao(automatoA,p1,parametros[3],p2);
                printf(">>transicao %i \"%c\" %i destruida<<\n",p1,pC,p2);
                break;
            /*AFequiv verifica a equivalencia entre automatos*/
            case 10:
                printf(">>Automato B(nome de arquivo)<<\n ");
                scanf("%s",pA);
                automatoB = AFcarrega(pA);
                if(automatoB!=NULL)
                {
                    if(AFequiv(automatoA,automatoB)==TRUE)
                        printf(">>TRUE<<\n");
                    else
                        printf(">>FALSE<<\n");
                }
                break;
            /*AFestadoFinal final verifica se e um estado final*/
            case 11:
                sscanf(parametros," %i",&p1);
                if(AFestadoFinal(automatoA,p1)==TRUE)
                    printf(">>TRUE<<\n");
                else
                    printf(">>FALSE<<\n");
                break;
            /*AFestadoInicial*/
            case 12:
                sscanf(parametros,"%i",&p1);
                if(AFestadoInicial(automatoA,p1)==TRUE)
                    printf(">>TRUE<<\n");
                else
                    printf(">>FALSE<<\n");
                break;
            /*AFfechamento*/
            case 13:
                AFfechamento(automatoA);
                printf(">>fechamento executado<<\n");
                break;
            /*AFfecho*/
            case 14:
                break;
            /*AFminimiza*/
            case 15:
                automatoTemp = AFminimiza(automatoA);
                if(automatoTemp!=NULL)                
                {
                    AFsalva(automatoTemp,"minimizado.txt");
                    printf(">>minimizacao executada, arquivo minimizado.txt criado<<\n");
                    printf(">>O automato original nao foi modificado<<\n");
                    AFdestroi(automatoTemp);
                }
                break;
            /*AFmoveAFD*/
            case 16:
                sscanf(parametros,"%i %c",&p1,&pC);
                printf(">>estado destino %i<<\n",AFmoveAFD(automatoA,p1,pC));
                break;
            /*AFnegacao*/
            case 17:
                automatoTemp = AFnegacao(automatoA);
                if(automatoTemp!=NULL)                
                {
                    automatoTemp;
                    AFsalva(automatoTemp,"negado.txt");
                    printf(">>negacao executada, arquivo negado.txt criado<<\n");
                    printf(">>O automato original nao foi modificado<<\n");
                    AFdestroi(automatoTemp);
                }
                break;
            /*AFrenumera*/
            case 18:
                automatoTemp = AFrenumera(automatoA);
                if(automatoTemp!=NULL)                
                {
                    automatoTemp;
                    AFsalva(automatoTemp,"renumerado.txt");
                    printf(">>renumeracao executada, arquivo renumerado.txt criado<<\n");
                    printf(">>O automato original nao foi modificado<<\n");
                    AFdestroi(automatoTemp);
                }
                break;
            /*AFsalva*/
            case 19:
                sscanf(parametros," %s",pA);
                AFsalva(automatoA,pA);
                printf(">>automato salvo, confira se o arquivo de saida existe<<\n");
                break;
            /**/
            case 20:
                printf(">>Automato B(nome de arquivo)<< ");
                scanf("%s",pA);
                automatoB = AFcarrega(pA);
                automatoTemp = AFuniao(automatoA,automatoB);
                AFsalva(automatoTemp,"uniao.txt");
                printf(">>uniao de automatos executada, arquivo uniao.txt salvo <<\n");
                break;
            case 0:
                AFdestroi(automatoA);
                AFdestroi(automatoB);
                AFdestroi(automatoTemp);
                exit(0);
                break;
        }
    }while(1);
    
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
