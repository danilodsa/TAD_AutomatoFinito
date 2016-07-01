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

AF AFdestroi(AF af) {
    Lista del;
    Lista aux;
    estado pDel;
    estado pAux;
    int i;

    pAux = af->estados;

    while (pAux != NULL) 
    {
        for (i = 0; i < af->num_simbolos; i++)
        {
            aux = pAux->move[i];
            while (aux != NULL) 
            {
                del = aux;
                aux = aux->prox;
                free(del);
            }
        }
        pDel = pAux;
        pAux = pAux->prox;
        free(pDel);
    }
    af = NULL;
    free(af);
    return af;
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
        novo->move[i] = NULL;
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
    estado anterior;
    
    aux = af->estados;
    
    /*Destruicao do ESTADO*/
    
    
    if(aux != NULL)
    {
        /*Caso seja o primeiro da lista*/
        if(aux->numero == e)
        {
            af->estados = aux->prox;
            free(aux);
            aux = NULL;
        }
        else
        {
            anterior = aux;
            aux = aux->prox;
            while(aux != NULL)
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
    }

    /*Decrementa o total de estados do automato*/
    af->num_estados--;
    

    /*Destruicao das TRANSICOES*/
    if(aux == NULL) /*Significa que o estado foi excluido com sucesso*/
    {
        /*aux recebe o inicio da lista de estados*/
        aux = af->estados;
        /*Percorre os estados*/
        while(aux != NULL)
        {
      //      Lista transicao;
        //    Lista transicao_anterior;
            int i;
            /*Percorre as transicoes*/
            for(i=0; i<af->num_simbolos; i++)
            {                
                AFdestroiTransicao(af, aux->numero, af->alfabeto[i], e);   
            }
            aux = aux->prox;
        }
    }

}

void AFcriaTransicao(AF af,int e1,char s,int e2)
{
    int pos;
    estado aux;
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
    int pos;
    estado aux;
    estado manipulado = NULL;
    
    Lista atual;
    Lista anterior;
    
    pos = retorna_index(af,s);
    
    aux = af->estados;
    /*Encontra o estado que sera manipulado*/
    while(aux != NULL && manipulado == NULL)
    {
        if(aux->numero == e1)
        {
            manipulado = aux;
        }
        aux = aux->prox;
    }
    /*Ao fim do laco, o estado a ser manipulado devera ter sido encontrado.*/
    
    atual = manipulado->move[pos];
    
    /*Verifica se exitem movimentos para esse simbolo*/
    if(atual != NULL)
    {
        /*caso a pilha tenha q apontar para o novo elemento*/
        if(atual->numero==e2)
        {
            manipulado->move[pos] = atual->prox;
            free(atual);
            atual = NULL;
        }
        else
        {
            anterior = atual;
            atual = atual->prox;
            while(atual!=NULL)
            {
                if(atual->numero==e2)
                {
                    anterior->prox = atual->prox;
                    free(atual);
                    atual = NULL;
                }
                else
                {
                    anterior = atual;
                    atual = atual->prox;
                }
            }
            /*Ao fim do while, já se obtem a posicao onde está a transicao*/
        }
    }
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
    return FALSE;
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
    return FALSE;
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
            while(transicao != NULL)
            {
               /*Contador que incrementa a cada transicao de um mesmo simbolo*/
               cont++;
               transicao = transicao->prox;
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
    while(aux != NULL)
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
    if(transicao != NULL)
    {
        return transicao->prox->numero;
    }
    return 0;
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

void AFsalva(AF af,char *nomeArquivo){
  FILE *arq;
  Lista aux;
  estado pAux;
  
  arq = fopen(nomeArquivo,"w");
  
  if(arq!=NULL)
  {
      int i;
      
      /*imprimi o cabecalho do arquivo
       "alfabeto" numero de estados*/
      pAux = af->estados;
      fprintf(arq,"\"%s\" %i\n",af->alfabeto,af->num_estados);
      
      /*perocorre todos os estados disponiveis e imprimi suas informacoes*/
      for(i=0;i<af->num_estados;i++)
      {
          fprintf(arq,"%i",pAux->numero);
          /*caso o estado for inicial imprime i*/
          if(pAux->inicial==TRUE)
          {
              fprintf(arq," i");
          }
          /*caso o estado for final imprime f*/
          if(pAux->final==TRUE)
          {
              fprintf(arq," f");
          }
          /*quebra de linha apos o impressao das info do estado*/
          fprintf(arq,"\n");
          pAux = pAux->prox;
      }
      
      pAux = af->estados;
      
      /*percorre a pilha de transicoes de todos os estados*/
      while(pAux!=NULL)
      {
          /*imprime a pilha de transicao por simbolo do alfabeto*/
          for(i=0;i<af->num_simbolos;i++)
          {
              aux = pAux->move[i];
              while(aux!=NULL)
              {
                fprintf(arq,"%i \"%c\" %i\n",pAux->numero,af->alfabeto[i],aux->numero);
                aux = aux->prox;
              }
          }
          pAux = pAux->prox;
      }
      
      fclose(arq);
      
  }
}

AF AFcarrega(char* nomeArquivo) {
    FILE *arq = NULL;
    AF automato;
    /*decisão de projeto*/
    char alfabeto[256];
    char temp[256];
    char auxA[20];
    char x,y;
    char buff;
    int QuantEstados;
    int auxX,auxY;
    
    arq = fopen(nomeArquivo,"rt");
    
    if(arq!=NULL)
    {        
        int i;
        int max = 0; 
        
        buff = ' ';
        
        while(buff != EOF)
        {
            buff=fgetc(arq);
            
            if(buff=='\n')
            {
                max++;
            }
        }
        fclose(arq);
        
        arq = fopen(nomeArquivo,"rt");
        
        fscanf(arq,"%s %i",temp,&QuantEstados);
        
        auxX = strlen(temp);
        auxX = auxX-2;
        
        for(i=0;i<auxX;i++)
        {
            alfabeto[i] = temp[i+1];
        }
        alfabeto[auxX] = '\0';
        
        /*aloca a memoria necessaria para o automato*/
        automato = AFcria(alfabeto);
        
        if(automato!=NULL)
        {
            int i;
            
            /*ponta pe incial*/
            fgets(auxA,20,arq);
            
            for(i=0;i<QuantEstados;i++)
            {
                fgets(auxA,20,arq);
                
                x = '\0';
                y = '\0';
                sscanf(auxA,"%i %c %c",&auxX,&x,&y);

                switch(x)
                {
                    case 'i':
                        if(y=='f')
                        {
                            AFcriaEstado(automato,auxX,TRUE,TRUE);
                        }
                        else
                        {
                            AFcriaEstado(automato,auxX,TRUE,FALSE);
                        }
                        break;
                    case 'f':
                        if(y=='i')
                        {
                            AFcriaEstado(automato,auxX,TRUE,TRUE);
                        }
                        else
                        {
                            AFcriaEstado(automato,auxX,FALSE,TRUE);
                        }
                        break;
                    default:
                        AFcriaEstado(automato,auxX,FALSE,FALSE);
                        ;
                }
            }
            
            max = max - QuantEstados - 1;
            
            for(i=0;i<max;i++)
            {
                fscanf(arq,"%i %s %i",&auxX,auxA,&auxY);                
                AFcriaTransicao(automato,auxX,auxA[1],auxY);
            }
        }
        return automato;
        
        /*fecha o arquivo*/
        fclose(arq);
    }
    /*retonar nulo caso não encontre o arquivo*/
    return NULL;
}



static int retorna_index(AF af,char s)
{
    int i;
    char* ptr;
    int posi;
        
    i = s;
    
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
    return af;
}

AF AFuniao(AF af1, AF af2)
{
    AF af3;
    estado auxf3;
    estado aux;    

    /*Juncao dos alfabetos do af1 e af2*/
    char* alfabeto3;
    char* temp;
    
    /*Renumera os estados do primeiro automato a partir de 10*/
    AFrenumeraPlus(af1, 10);
    
    /*Renumera os estados do segundo automato a partir de 20*/
    AFrenumeraPlus(af2, 20);
    
    temp = concatenaAlfabetos(af1->alfabeto, af2->alfabeto);
    alfabeto3 = (char*) malloc(strlen(temp)*sizeof(char));
    
    /*funcao de juncao dos alfabetos*/
    strcpy(alfabeto3,temp);
    
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
            auxf3->inicial = FALSE;
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
            auxf3->inicial = FALSE;
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
    int** matrizR;
    int cont =0;
    int i, j, k;
    estado aux;
    estado auxfixo;
    Lista transicao;
    
    matrizR = malloc (af->num_estados * sizeof (int *));
    
       for (i = 0; i < af->num_estados; ++i)
          matrizR[i] = malloc (2 * sizeof (int));
    
    aux = af->estados;
    
    /*Cria tabela de referencias*/
    while(aux != NULL)
    {
        matrizR[cont][0] = aux->numero;
        aux = aux->prox;
        cont++;
        
        printf("%d ", matrizR[cont][0]);
    }
    
    for(i=0; i<af->num_estados; i++)
    {
        matrizR[i][1] = i+1;  
    }
    
    /*********************************/
    
    
    /*Renumeracao das transicoes*/
    auxfixo = af->estados;
    
    while(auxfixo != NULL)
    {
        for(i=0; i<af->num_simbolos; i++)
        {
            transicao = auxfixo->move[i];
            
            while(transicao != NULL)
            {
                for(j=0; j<af->num_estados; j++)
                {
                   if(matrizR[j][1] == transicao->numero) 
                   {
                       transicao->numero = matrizR[j][1];
                   }
                }
                transicao = transicao->prox;
            }
        }
        auxfixo = auxfixo->prox;
    }
    
    /*Renumeracao dos estados*/
    
    
    
    
    return af;
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
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        aux->numero = n;
        n++;
        aux = aux->prox;    
    }
    return NULL;
}

AF AFminimiza(AF af)
{
    int i,j;
    int tam = af->num_estados + 1;
    int matriz[tam][tam];/*Matriz que informa se os estados sao ou EQ*/
    int pendencias[tam][tam]; /*matriz que armazena as pendencias*/
    
    estado aux;
    estado auxfixo;
    
    Lista transicaofixo;
    Lista transicao;    
    
    AFrenumera(af);

    /*atribui o numero de simolos a todas as posicoes da matriz*/
    for(i=0; i<tam; i++)
    {
        for(j=0; j<tam; j++)
        {
            matriz[i][j] = af->num_simbolos;
        }
    }
    
    for(i=0; i<tam; i++)
    {
        for(j=0; j<tam; j++)
        {
            pendencias[i][j] = 0;
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
            if(aux->numero != auxfixo->numero)
            {
                /*Verifica se um e estado final e outro nao. Quando isso acontece, automaticamente não sao equivalentes*/
                if(auxfixo->final != aux->final)
                {
                    matriz[auxfixo->numero][aux->numero] = -1; /*-1 = Não equivalente*/
                }
                else
                {
                    /*Percorre as transicoes verificando se são iguais*/
                    for(i=0; i<af->num_simbolos; i++)
                    {
                        transicaofixo = auxfixo->move[i];
                        transicao = aux->move[i];

                        if(transicaofixo->numero == transicao->numero)/*Quando as transicoes sao identicas, oviamente são equivalentes*/
                        {
                            matriz[auxfixo->numero][aux->numero]--;/*Quando as transicoes forem equivalentes, o numero guardado na posicao referente a elas é decrementado*/
                        }/*Caso esse numero seja decrementado até que seja atigido o ZERO, o estado é equivalente*/
                        else
                        {
                            if(matriz[transicaofixo->numero][transicao->numero] == 0)
                            {
                                matriz[auxfixo->numero][aux->numero]--;
                            }
                            else
                            {
                                pendencias[auxfixo->numero][aux->numero] = 1;
                            }
                        }
                    }
                }
                
            }
            aux = aux->prox;
        }
        auxfixo = auxfixo->prox;
    }
    /*TRATAMENTO DE PENDENCIAS*/
    int cont;
    int k;
    for(cont=0; cont<10; cont++)
    {
        for(i=0; i<tam ;i++)
        {
            for(j=0; j<tam; j++)
            {
                if(pendencias[i][j] == 1)/*Caso exista uma pendencia*/
                {
                    matriz[i][j] = af->num_simbolos;
                    auxfixo = af->estados;
                    aux = af->estados;
                    /*encontrar o auxfixo*/
                    while(auxfixo != NULL)
                    {
                        if(auxfixo->numero == i)
                        {
                            while(aux != NULL)
                            {
                                if(aux->numero == j)
                                {
                                    /*Neste ponto já se tem os estados I e J*/
                                    for(k=0; k<af->num_simbolos; k++)
                                    {
                                       transicaofixo = auxfixo->move[k];
                                       transicao = aux->move[k];
                                       /*Compara as transicoes*/
                                       if(matriz[transicaofixo->numero][transicao->numero] == 0)
                                       {
                                           matriz[i][j]--;
                                           if(matriz[i][j] == 0)
                                           {
                                               pendencias[i][j] = 0;
                                           }
                                       }
                                    }
                                }
                                aux = aux->prox;
                            }
                        }
                        auxfixo = auxfixo->prox;
                    }
                }
            }
        }
    }
    
    
 
  /****************************************************************************/
  /**********************Minimizacao do automato*******************************/ 
  /****************************************************************************/     
    
    for(i=0; i<tam; i++)
    {
        for(j=0; j<tam; j++)
        {
            if(i != j)
            {
                /*Encontrando estados EQ*/
                /*O estado com o maior indice será removido (Decisao de Projeto)*/
                if(matriz[i][j] == 0)
                {
                    if(i > j)
                    {
                        /*Remove o estado I*/
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
                                aux = NULL;
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
                                aux = NULL;
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
    return FALSE;
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
    return NULL;
}

