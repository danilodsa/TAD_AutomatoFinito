#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

/*Funcao que retorna a posicao do simbolo dentro do vetor de simbolos*/
static int retorna_index(AF af, char s);
static AF AFrenumeraPlus(AF af, int n);
static char* concatenaAlfabetos(char* alfabeto1, char* alfabeto2);

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
/*(af->num_simbolos+1)*/
void AFcriaEstado(AF af,int e,Bool inicial,Bool final)
{
    int i;
    estado novo;
    /*aloca estrutura para o novo automato*/
    novo = (estado) malloc(sizeof(struct Testado));
    novo->move = (Lista*) malloc(sizeof(Lista));
    
    for(i=0; i<(af->num_simbolos+1); i++)
    {
        novo->move[i] = (Lista) malloc(sizeof (struct Tnodolista));
        novo->move[i].prox = NULL;
    }
    
    novo->numero = e;
    novo->inicial = inicial;
    novo->final = final;
    
    
    novo->prox = af->estados;
    af->estados = novo;
    /*aponta para o novo nodo criado*/
    
    
    
    /*incremento da quantidade de estados*/
    af->num_estados++;
    
}

void AFdestroiEstado(AF af,int e)
{
    estado aux;
    
    aux = af->estados;
    
    if(aux->numero == e)
    {
        af->estados = aux->prox;
        free(aux);
        aux = NULL;
    }
    else
    {
        estado anterior;
        anterior = aux;
        while(aux!=NULL)
        {
            if(aux->numero == e)
            {
                anterior->prox = aux->prox;
                free(aux);
                aux = NULL;
            }
            else
            {
                anterior = aux;
                aux = aux->prox;
            }
        }
    }
    af->num_estados--;
}

void AFcriaTransicao(AF af,int e1,char s,int e2)
{
    int i, pos;
    estado aux;
    estado manipulado;
    /*Variavel transicao guarda a nova transicao*/
    Lista nova_transicao;
    
    nova_transicao = (Lista) malloc(sizeof(Lista));
    
    nova_transicao->numero = e2;
    
    aux = af->estados;
    
   /*Encontra o estado que sera manipulado*/ 
    while(aux != NULL)
    {
        if(aux->numero == e1)
        {
            /*Pos será o identificador do simbolo referente ao vetor de simbolos*/
            pos = retorna_index(af, s);

            /*transicao*/
            nova_transicao->prox = aux->move[pos];
            /*transicao será o primeiro elemento para qual o elemento->move[pos] irá apontar*/


            aux->move[pos] = nova_transicao;
            /*Escreve a transicao no vetor de transicoes*/        
        }
        aux = aux->prox;
    }
     
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
    int pos;
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
    
    pos = retorna_index(af, s);
    
    transicao = manipulado->move[pos];
    if(transicao->prox != NULL)
    {
        return transicao->prox->numero;
    }
    
}

Lista AFfecho(AF af,Lista e,char s)
{
    Lista retorno;
    Lista aux;
    
    retorno = (Lista) malloc(sizeof(Lista));
    
    aux = e;
    
    while(aux != NULL)
    {
        retorno->numero = AFmoveAFD(af,aux->numero,s);
        retorno = retorno->prox;
        aux = aux->prox;
    }
    return retorno;
       
}

static int retorna_index(AF af,char s)
{
    int i;
    char* ptr;
    int posi;
        
    i = (int*) s;
    
    ptr = strchr(af->alfabeto,i);
    
    posi = ptr - af->alfabeto;
    
    return posi;
}


/******************************************************************************/

AF AFnegacao(AF af)
{
    estado aux;
    
    aux = af->estados;
    
    while(aux->prox != NULL)
    {
        if(aux->final == TRUE)
        {
            aux->final = FALSE;
        }
        else
        {
            aux->final = TRUE;
        }
    }
}

AF AFuniao(AF af1, AF af2)
{
    int pos;
    AF af3;
    estado auxf3;
    estado aux;    

    /*Juncao dos alfabetos do af1 e af2*/
    char* alfabeto3;
    
    /*Renumera os estados do primeiro automato a partir de 10*/
    AFrenumeraPlus(af1, 10);
    
    /*Renumera os estados do segundo automato a partir de 20*/
    AFrenumeraPlus(af2, 20);
    
    
    /*funcao de juncao dos alfabetos*/
    strcpy(alfabeto3, concatenaAlfabetos(af1->alfabeto, af2->alfabeto));    
    
    /*cria o novo automato*/
    af3 = AFcria(alfabeto3);
    
    /*cria o novo estado inicial, que tem a transiação 'vazio' para os estados iniciais dos outros dois automatos*/
    AFcriaEstado(af3, 1, TRUE, FALSE);
    
    /*cria o novo estado final, que recebe a transicao 'vazio' dos estados finais dos outros dois automatos*/
    AFcriaEstado(af3, 2, FALSE, TRUE);
    
    auxf3 = af3->estados;
    aux = af1->estados;
    
    
    while(aux != NULL)
    {
        auxf3 = aux;
        
        if(auxf3->inicial == TRUE)
        {
            AFcriaTransicao(af3, 1, '\0', auxf3->numero);
            auxf3->inicial == FALSE;
        }
        if(auxf3->final == TRUE)
        {
            AFcriaTransicao(af3, auxf3->numero, '\0', 2);
            auxf3->final = FALSE;
        }
        aux = aux->prox;
        auxf3 = auxf3->prox;   
    }
    
    
    aux = af2->estados;
    
    while(aux != NULL)
    {
        auxf3 = aux;
        
        if(auxf3->inicial == TRUE)
        {
            AFcriaTransicao(af3, 1, '\0', auxf3->numero);
            auxf3->inicial == FALSE;
        }
        if(auxf3->final == TRUE)
        {
            AFcriaTransicao(af3, auxf3->numero, '\0', 2);
            auxf3->final = FALSE;
        }
        aux = aux->prox;
        auxf3 = auxf3->prox;   
    }
    
    af3->num_estados = af1->num_estados + af2->num_estados + 2;
    af3->num_simbolos = strlen(alfabeto3);
    
    return af3;
    
}

AF AFrenumera(AF af)
{
    estado aux;
    int i = 1;
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        aux->numero = i;
        i++;
        aux = aux->prox;    
    }
}

static char* concatenaAlfabetos(char* alfabeto1, char* alfabeto2)
{
    int i;
    int j;

    char aux;
    
    strcat(alfabeto1,alfabeto2);
    
    i = 0;
    
    for(i=0;i<strlen(alfabeto1);i++)
    {
        for(j=i;j<strlen(alfabeto1);j++)
        {
            if(alfabeto1[i]==alfabeto1[j+1])
            {
                aux = alfabeto1[strlen(alfabeto1)-1];
                alfabeto1[strlen(alfabeto1)-1] = alfabeto1[j+1];
                alfabeto1[j+1] = aux;
                alfabeto1[strlen(alfabeto1)-1] = '\0';
            }
        }
    }
    
    return alfabeto1;
}

/*Renumera o automato a partir de um numero informado*/
static AF AFrenumeraPlus(AF af, int n)
{
        estado aux;
    int i = 1;
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        aux->numero = n;
        n++;
        aux = aux->prox;    
    }
}

AF AFminimiza(AF af)
{
    int i,j;
    int tam = af->num_estados + 1;
    int matriz[tam][tam];
    
    estado aux;
    estado auxfixo;
    
    
    AFrenumera(af);

    /*atribui -1 a todas as posicoes da matriz*/
    for(i=0; i<tam; i++)
    {
        for(j=0; j<tam; j++)
        {
            matriz[i][j] = -1;
        }
    }
    
    
    auxfixo = af->estados;
    aux = af->estados;
    
  /****************************************************************************/
  /******************Criacao da matriz de equivalencias************************/ 
  /****************************************************************************/  
    while(auxfixo != NULL)
    {
        while(aux != NULL)
        {
            /*Verifica se os estados em questao não sao o mesmo estado*/
            if(aux != auxfixo)
            {
                /*Verifica se um e estado final e outro nao. Quando isso acontece, automaticamente não sao equivalentes*/
                if(auxfixo->final != aux->final)
                {
                    matriz[auxfixo->numero][aux->numero] = 1;
                }
                /*Verificacao de equivalencia dos movimentos*/
                for(i=0; i<af->num_simbolos; i++)
                {
                    /*caso os movimentos em questao (de estados diferentes) sejam iguais
                     * por exemplo: {(4 "x" 5), (4 "y" 3)} e {(5 "x" 5), (5 "y" 3)}.*/
                    if(aux->move[i]->numero == auxfixo->move[i]->numero)
                    {
                        /*Se a posicao referente na matriz estiver guardando um -1
                         * significa que é a primeira transicao a ser verificada,
                         * entao atribui-se o numero de simbolos -1.*/
                        if(matriz[auxfixo->numero][aux->numero] == -1)
                        {
                            matriz[auxfixo->numero][aux->numero] = af->num_simbolos-1;
                        }
                        /*Caso nao seja a primeira transicao a ser verificada, e a 
                         * transicao que esta sendo verificada seja esquivalente, 
                         * entao o numero que está guardado na matris de equivalencias é decrementado. 
                         * Se os fim do processo esse numero for ZERO, significa que todos as transicoes 
                         * são equivalentes e, consequentemente os estados sao equivalentes ( 0 )*/
                        else
                        {
                            matriz[auxfixo->numero][aux->numero]--;
                        }               
                    }
                    /*Caso os estados sejam equivalentes, a posicao subsequente recebe 
                     * o tamanho do alfabeto -1, para que ele possa ser decrementado caso existam mais estados equivalentes*/
                    else if((matriz[auxfixo->move[i]->numero][aux->move[i]->numero] ==1) && (matriz[auxfixo->numero][aux->numero] == -1))
                    {
                        matriz[auxfixo->numero][aux->numero] = af->num_simbolos-1;                        
                    }
                    /*Caso nao seja a primeira transicao a ser verificada e os estados dessa transicao sejam equivalentes 
                     * o numero contido na posicao da matriz e decrementado. 
                     * Se ao fim da iteracao esse numero for ZERO, significa que todos os estados 
                     * referentes as transicoes dos dois estados susequentes sao equivalentes*/
                    else if((matriz[auxfixo->move[i]->numero][aux->move[i]->numero] ==1) && (matriz[auxfixo->numero][aux->numero] != -1))
                    {
                        matriz[auxfixo->numero][aux->numero]--;
                    }

                }
                
            }
            aux = aux->prox;
        }
        auxfixo = auxfixo->prox;
    }
    
    
 
  /****************************************************************************/
  /**********************Minimizacao do automato*******************************/ 
  /****************************************************************************/     
    
    for(i=0; i<af->num_estados; i++)
    {
        for(j=0; j<af->num_estados; j++)
        {
            if(i != j)
            {
                /*Encontrando estados EQ*/
                /*O estado com o maior indice será removido (Decisao de Projeto)*/
                if(matriz[i][j] == 0)
                {
                    if(i > j)
                    {
                        estado anterior;
                        
                        aux = af->estados;
                        anterior = af->estados;
                        /*Percorre os estados do AF ate que se encontre o estado I*/
                        while(aux != NULL)
                        {
                            /*Caso encontre, o estado I é removido*/
                            if(aux->numero == i)
                            {
                                anterior = aux->prox;
                                free(aux);
                            }
                            
                            int k;
                            /*Percorre o vetor de transicoes de todos os estados 
                             * e faz com que todas as transicoes que anteriormente 
                             * apontavam para I apontem agora para J, pois I e J 
                             * são equivalentes e I foi removido*/
                            for(k=0; k<af->num_estados; k++)
                            {
                                if(aux->move[k]->numero == i)
                                {
                                    aux->move[k]->numero = j;
                                }
                            }
                            anterior = aux;
                            aux = aux->prox;
                        }
                    }
                    else
                    {
                        /*Remove o estado J*/
                        estado anterior;
                        
                        aux = af->estados;
                        anterior = af->estados;
                        /*Percorre os estados do AF ate que se encontre o estado I*/
                        while(aux != NULL)
                        {
                            /*Caso encontre, o estado I é removido*/
                            if(aux->numero == j)
                            {
                                anterior = aux->prox;
                                free(aux);
                            }
                            
                            int k;
                            /*Percorre o vetor de transicoes de todos os estados 
                             * e faz com que todas as transicoes que anteriormente 
                             * apontavam para I apontem agora para J, pois I e J 
                             * são equivalentes e I foi removido*/
                            for(k=0; k<af->num_estados; k++)
                            {
                                if(aux->move[k]->numero == j)
                                {
                                    aux->move[k]->numero = i;
                                }
                            }
                            anterior = aux;
                            aux = aux->prox;
                        }
                    }
                }
            }
        }
    }
    return af;
}

Bool AFequiv(AF af1, AF af2)
{
    /*Ja supondo que af1 e af2 são AFD's*/
    int i, j, cont_trans, cont_est = 0;
    
    AF af1_min;
    AF af2_min;
    
    estado aux1;
    estado aux2;
    
    /*Minimiza abos os automatos*/
    af1_min = AFminimiza(af1);
    af2_min = AFminimiza(af2);
    
    /*Renumera amos os automatos*/
    af1_min = AFrenumera(af1_min);
    af2_min = AFrenumera(af2_min);
    
    aux1 = af1_min->estados;
    aux2 = af2_min->estados;
    
    if(af1_min->num_estados != af2_min->num_estados)
    {
        return FALSE;
    }
    
    while(aux1 != NULL)
    {
        while(aux2 != NULL)
        {
            for(i=0; i<af1->num_simbolos; i++)
            {
                for(j=0; j<af2->num_simbolos; j++)
                {
                    if(aux1->move[i]->numero == aux2->move[j]->numero)
                    {
                        cont_trans++;
                    }
                }
            }
            if((cont_trans == af1_min->num_simbolos) && (cont_trans == af2_min->num_simbolos))
            {
                cont_est++;
            }
            
            aux2 = aux2->prox;
        }
        
        aux1 = aux1->prox;
    }
    if((cont_est == af1_min->num_estados) && (cont_est == af2_min->num_estados))
    {
        return TRUE;
    }
}

AF AFfechamento(AF af)
{
    estado aux;
    int inicial;
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        if(aux->inicial == TRUE)
        {
            inicial = aux->numero;
        }
    }
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        if(aux->final == TRUE)
        {
            int pos;

            pos = retorna_index(af, '\0');
            
            aux->move[pos]->numero = inicial;

        }
    }
    
}