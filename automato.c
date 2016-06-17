#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

/*Funcao que retorna a posicao do simbolo dentro do vetor de simbolos*/
static int retorna_index(AF af, char s);



AF AFcria(char *alfabeto)
{
    AF aux = (AF) malloc(sizeof(AF));
    
    if(aux!=NULL)
    {
        /*define a quantidade de simbolos de acordo com o alfabeto informado*/
        aux->num_simbolos = strlen(alfabeto);
        
        /*define o numero de estados para zero, uma vez que nao possui
         nenhum estado*/
        aux->num_estados = 0;
        
        /*define o tamanho do vetor de alfabeto
         *de acordo com a quantidade de simbolos*/
        aux->alfabeto = (char*) malloc(aux->num_simbolos*sizeof(char));
        
        /*passa o alfabeto informado para a estrutura do Automato*/
        strcpy(aux->alfabeto,alfabeto);

        /*seta o automato como sem nenhum estados*/
        aux->estados = NULL;
        
        /*retorna a estrutura alocada*/
        return aux;
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
    int i;
    /*Aux recebe o primeiro estado da lista, para percorre-la*/
    aux = af->estados;
    
    while(aux->prox != NULL)
    {
        aux = aux->prox;
    }
    novo->inicial = inicial;
    novo->final = final;
    novo->numero = e;
    aux->prox = novo; 
    
    /*Alocacao da matriz de estados*/
    novo->move = (Lista*) malloc(af->num_simbolos * sizeof(Lista));
   
    af->num_estados++;
    /*VERIFICAR LANCE DE CRIACAO DA LISTA DE MOVIMENTOS*/
    
}

void AFdestroiEstado(AF af,int e)
{
    estado aux;
    estado anterior;
    
    anterior = af->estados;
    aux = anterior->prox;
    
    while(aux->prox != NULL)
    {
        if(aux->numero == e)
        {
            anterior->prox = aux->prox; 
            free(aux);
        }
        else
        {
            anterior = aux;
            aux = aux->prox;
        }
    }

}

void AFcriaTransicao(AF af,int e1,char s,int e2)
{
    int i, pos;
    estado aux;
    estado manipulado;
    /*Variavel transicao guarda a nova transicao*/
    Lista transicao;
    
    manipulado = (Lista) malloc (sizeof(Lista));
    
    aux = af->estados;
    
    
   /*Encontra o estado que sera manipulado*/ 
    while(aux->prox != NULL)
    {
        if(aux->numero == e1)
        {
           manipulado = aux; 
        }
        else
        {
            aux = aux->prox;
        }
    }  
    /*Pos será o identificador do simbolo referente ao vetor de simbolos*/
    pos = retorna_index(af, s);
    
    /*transicao*/
    transicao->prox = manipulado->move[pos]->prox;
    /*transicao será o primeiro elemento para qual o elemento->move[pos] irá apontar*/
    transicao->numero = e2;  
    manipulado->move[pos] = transicao;
    /*Escreve a transicao no vetor de transicoes*/
     
}

void AFdestroiTransicao(AF af,int e1,char s,int e2)
{
    int i, pos;
    estado aux;
    estado manipulado;
    
    Lista atual;
    Lista anterior;
    
    pos = retorna_index(af, s);
    
    aux->prox = af->estados;
    /*Encontra o estado que sera manipulado*/
    while(aux->prox != NULL)
    {
        if(aux->numero == e1)
        {
            manipulado = aux;
        }
        else
        {
            aux = aux->prox;
        }
    }
    /*Ao fim do laco, o estado a ser manipulado devera ter sido encontrado.*/
    
    atual = manipulado->move[pos];
    
    while(atual->numero != e2)
    {
        anterior = atual;
        atual = atual->prox;
    }
    /*Ao fim do while, já se obtem a posicao onde está a transicao*/
 
    anterior->prox = atual->prox;
    free(atual);
    
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
    int i, cont;
    
    estado aux;
    Lista transicao;
    Bool afd = TRUE;
    
    aux = af->estados;
    /*Laco que percorre os estados*/
    while(aux->prox != NULL)
    {
        /*Laco que percorre os simbolos*/
        for(i=0; i<af->num_simbolos; i++)
        {
            cont = 0;
            transicao = aux->move[i];
            /*Laco que percorre as transicoes*/
            while(transicao->prox != NULL)
            {
               /*Contador que incrementa a cada transicao de um mesmo simbolo*/
               cont++; 
            }
            /*Caso se tenha apenas uma transicao para cada simbolo em cada estado, é um afd*/
            /*Caso se tenha mais de uma transicao para o mesmo simbolo, não é afd*/
            if(cont > 1)
            {
                afd = FALSE;
            }
        }
        aux = aux->prox;
    }
    return afd;
    
    
}

Bool AFchecaAFv(AF af)
{
    int pos;
    
    estado aux;
    Bool afv = FALSE;
    
    aux = af->estados;
    /*Recupera a posicao do movimento vazio, geralmente a ultima do vetor de simbolos*/
    pos = retorna_index(af, '\0');
    
    /*Percorre todos os estados*/
    while(aux->prox != NULL)
    {
        /*Já com a posicao do vazio conhecida, verifica se essa posicao aponta para alguma transicao
         * ou seja, verifica se exite alguma transicao para o movimento vazio "\0"*/
        if(aux->move[pos]->prox != NULL)
        {
            afv = TRUE;
        }
        aux = aux->prox;
    } 
    return afv;
}

int AFmoveAFD(AF af,int e,char s)
{
    int i;
    estado aux;
    estado manipulado;
    Lista transicao;
    
    aux = af->estados;
    while(aux->prox != NULL)
    {
        if(aux->numero == e)
        {
            manipulado = aux;
        }
        else
        {
            aux = aux->prox;
        }
    }
    /*Ao fim do laco, ja se tem o estado e*/
    
    retorna_index(af, s);
    
    
    

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


static int retorna_index(AF af, char s)
{
    int i;
    
    for(i=0; i<af->num_simbolos; i++)
    {
        if(strcmp(af->alfabeto[i], s) == 0)
        {
            return i;
        }
    }
}