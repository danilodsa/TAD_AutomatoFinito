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
    char comando,comando2,p1,p2;
    char Aux1[30],parametros[100],pA[256],pB[20],pC;
    estado aux;
    Lista pAux;
    int auxX,i,a,b;
    Bool A,B;
    
/*
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
                        printf("B - automato B\n");
                        scanf("%c",&comando);
                        switch(comando)
                        {
                            case 'A':
                                if(AFchecaAFD(automatoA)==TRUE)
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
                        fgets(buff,10,stdin);
                        printf("A - automato A\n");
                        printf("B - automato A\n");
                        scanf("%c",&comando);
                        switch(comando)
                        {
                            case 'A':
                                automatoA = AFminimiza(automatoA);
                                break;
                            case 'B':
                                automatoB = AFminimiza(automatoB);
                                break;
                        }
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
*/
    
    automatoA = NULL;
    automatoB = NULL;
    automatoTemp = NULL;
    
    do
    {
        scanf("%s",Aux1);
        fgets(parametros,100,stdin);
        switch(func(Aux1))
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
                sscanf(parametros,"% i %s %s",&p1,pA,pB);
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
                    automatoTemp;
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
            case 20:
                printf(">>Automato B(nome de arquivo)<< ");
                scanf("%s",pA);
                automatoB = AFcarrega(pA);
                automatoTemp = AFuniao(automatoA,automatoB);
                break;
            case -1:
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
        return -1;
}

Bool identifica(char* valor){
    if(strcmp(valor,"TRUE")==0)
        return TRUE;
    else
        FALSE;
}
