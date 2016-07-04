#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automato.h"

/*Funcao que retorna a posicao do simbolo dentro do vetor de simbolos*/
static int retorna_index(AF af, char s);
static AF AFrenumeraPlus(AF af, int n);
static char* concatenaAlfabetos(char* alfabeto1, char* alfabeto2);
static estado retornaEstado(AF af, int n);

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

    if(af!=NULL)
    {
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
    }
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
      while(pAux != NULL)
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
          for(i=0;i<af->num_simbolos+1;i++)
          {
              aux = pAux->move[i];
              while(aux!=NULL)
              {
                  if(af->alfabeto[i]!='\0')
                  {
                      fprintf(arq,"%i \"%c\" %i\n",pAux->numero,af->alfabeto[i],aux->numero);
                  }
                  else
                  {
                      fprintf(arq,"%i \"E\" %i\n",pAux->numero,aux->numero);
                  }
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
    
    while(aux != NULL)
    {
        if(aux->final == TRUE)
        {
            aux->final = FALSE;
        }
        else
        {
            aux->final = TRUE;
        }
        aux = aux->prox;
    }
    return af;
}

AF AFuniao(AF af1, AF af2)
{
    AF af3;
    estado auxf3;
    estado aux;    

    int i;
    
    
    Lista auxtransicao;
    
    
    /*Juncao dos alfabetos do af1 e af2*/
    char* alfabeto3;
    char* temp;
    
    /*Renumera os estados do primeiro automato a partir de 10*/
    AFrenumeraPlus(af1, 3);
    
    /*Renumera os estados do segundo automato a partir de 20*/
    AFrenumeraPlus(af2, af1->num_estados+3);
    
    alfabeto3 = concatenaAlfabetos(af1->alfabeto, af2->alfabeto);
    
    /*cria o novo automato*/
    af3 = AFcria(alfabeto3);
    
    /*cria o novo estado inicial, que tem a transiação 'vazio' para os estados iniciais dos outros dois automatos*/
    AFcriaEstado(af3, 1, TRUE, FALSE);
    
    /*cria o novo estado final, que recebe a transicao 'vazio' dos estados finais dos outros dois automatos*/
    AFcriaEstado(af3, 2, FALSE, TRUE);
       
    /*Copia todos os estados do AF1 para o AF3*/
    aux = af1->estados;
    while(aux != NULL)
    {
        AFcriaEstado(af3, aux->numero, aux->inicial, aux->final);
        aux = aux->prox;
    }
    
    /*Copia todas as transicoes do AF1 para o AF3*/
    aux = af1->estados;
    while(aux != NULL)
    {
        for(i=0; i<af1->num_simbolos; i++)
        {
            auxtransicao = aux->move[i];
            while(auxtransicao != NULL)
            {
                /*Quando fiz este trecho de código, apenas eu e Deus sabiamos o que eu estava fazendo. Agora apenas Deus sabe.*/
                AFcriaTransicao(af3, aux->numero, af1->alfabeto[i], auxtransicao->numero);
                auxtransicao = auxtransicao->prox;
            }
        }        
        aux = aux->prox;
    }   
    
    /*Copia todos os estados do AF2 para o AF3*/
    aux = af2->estados;
    while(aux != NULL)
    {
        AFcriaEstado(af3, aux->numero, aux->inicial, aux->final);
        aux = aux->prox;
    }
    
    /*Copia todas as transicoes do AF2 para o AF3*/
    aux = af2->estados;
    while(aux != NULL)
    {
        for(i=0; i<af2->num_simbolos; i++)
        {
            auxtransicao = aux->move[i];
            while(auxtransicao != NULL)
            {
                /*Quando fiz este trecho de código, apenas eu e Deus sabiamos o que eu estava fazendo. Agora apenas Deus sabe.*/
                AFcriaTransicao(af3, aux->numero, af2->alfabeto[i], auxtransicao->numero);
                auxtransicao = auxtransicao->prox;
            }
        }        
        aux = aux->prox;
    }
    /*Uniao efetiva dos automatos*/
    aux = af3->estados;
    while(aux != NULL)
    {
        /*Verifica se os automatos em questao não sao o 1(inicial) e o 2(final)*/
        if((aux->numero != 1) && (aux->numero != 2))
        {
            /*Verifica se o estado em questao é INICIAL*/
            if(aux->inicial == TRUE)
            {
                /*Caso seja inicial, cria-se uma transicao do 1 para o estado, utilizano o simbolo vazio*/
                /*E o estado deixa de ser inicial*/
                aux->inicial = FALSE;
                AFcriaTransicao(af3, 1, '\0', aux->numero); 
            }
            /*Verifica se o estado em questao é FINAL*/
            if(aux->final == TRUE)
            {
                /*Caso seja final, cria-se uma transicao do estado em questao para o estado 2, utilizano o simbolo vazio*/
                /*E o estado deixa de ser inicial*/                
                aux->final = FALSE;
                AFcriaTransicao(af3, aux->numero, '\0', 2);
            }
        }
        aux = aux->prox;
    }
    
    /*Define o numero de estados sendo a soma do numero de estados dos dois automatos integrantes da UNIAO*/
    af3->num_estados = af1->num_estados + af2->num_estados + 2;
    /*Define o numero de simbolos sendo o tamanho do alfabeto resultante da concatenacao dos alfabetos dos dois automatos ingrantes da UNIAO*/
    af3->num_simbolos = strlen(alfabeto3);

    return af3;
    
}

AF AFrenumera(AF af)
{
    int** matrizR;
    int i, j, k;
    estado aux;
    estado auxfixo;
    Lista transicao;
    
    matrizR = malloc (af->num_estados * sizeof (int *));
    
       for (i = 0; i < af->num_estados; ++i)
          matrizR[i] = malloc (2 * sizeof (int));
    
    aux = af->estados;
    
    /*Cria tabela de referencias*/
    for(i=0; i<af->num_estados; i++)
    {
        matrizR[i][0] = aux->numero;
        aux = aux->prox;
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
                   if(transicao->numero == matrizR[j][0]) 
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
    
    aux = af->estados;
    for(i=0; i<af->num_estados; i++)
    {
        aux->numero = matrizR[i][1];
        aux = aux->prox;
    }
    
    
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
    int** matrizR;
    int i, j, k;
    estado aux;
    estado auxfixo;
    Lista transicao;
    
    matrizR = malloc (af->num_estados * sizeof (int *));
    
       for (i = 0; i < af->num_estados; ++i)
          matrizR[i] = malloc (2 * sizeof (int));
    
    aux = af->estados;
    
    /*Cria tabela de referencias*/
    for(i=0; i<af->num_estados; i++)
    {
        matrizR[i][0] = aux->numero;
        aux = aux->prox;
    }
    
    for(i=0; i<af->num_estados; i++)
    {
        matrizR[i][1] = n;
        n++;
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
                   if(transicao->numero == matrizR[j][0]) 
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
    
    aux = af->estados;
    for(i=0; i<af->num_estados; i++)
    {
        aux->numero = matrizR[i][1];
        aux = aux->prox;
    }
    
    
    return af;
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
    
    af = AFrenumera(af);

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
    estado aux2;
    int inicial;
    int pos;
    
    aux = af->estados;
    aux2 = af->estados;
    
    pos = retorna_index(af, '\0');
    
    while(aux != NULL)
    {
        if(aux->inicial == TRUE)
        {
            inicial = aux->numero;
            
            while(aux2 != NULL)
            {
                if(aux2->final == TRUE)
                {
                    AFcriaTransicao(af, inicial, af->alfabeto[pos], aux2->numero);
                }
                aux2 = aux2->prox;
            }
        }
    }
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        if(aux->final == TRUE)
        {   
            AFcriaTransicao(af, aux->numero, af->alfabeto[pos], inicial);
        }
    }
    return af;
}

AF AFafv2afn(AF afv)
{
    AF afn;
    estado auxestadoAFV;
    estado auxestadoAFN;
    Lista auxtransicaoAFV;
    int pos;
    int i;
    int cont = 0;
    
    /*Cria o automato que ao fim será a conversao de AFV para AFN*/
    afn = AFcria(afv->alfabeto);
    
    /*Retorna em qual posicao do alfabeto esta o VAZIO*/
    pos = retorna_index(afv, '\0');
    
    auxestadoAFN = afn->estados;
    auxestadoAFV = afv->estados;

    /*Conta quantos estados possuem transicoes com o movimento vazio e os cria no AFN*/
    while(auxestadoAFV != NULL)
    {
        auxtransicaoAFV = auxestadoAFV->move[pos];
        if(auxtransicaoAFV != NULL)
        {
            AFcriaEstado(afn, auxestadoAFV->numero, auxestadoAFV->inicial, auxestadoAFV->final);
        }
        auxestadoAFV = auxestadoAFV->prox;
    }
    
    auxestadoAFN = afn->estados;
    auxestadoAFV = afv->estados;
    
    estado intermediario;
    estado futuro;
    Lista  transicao_intermediario;
                
    /*Remove o movimento vazio das transicoes*/
    while(auxestadoAFV != NULL)
    {
        auxtransicaoAFV = auxestadoAFV->move[pos];
        while(auxtransicaoAFV != NULL)
        {
            intermediario = retornaEstado(afv, auxtransicaoAFV->numero);
            /*Verifica se o estado move com o vazio para um estado final, se sim, ele se torna estado final*/
            if(intermediario->final == TRUE)
            {
                /*O estado que aponta para  deve ser final*/
                AFcriaEstado(afn, auxestadoAFV->numero, auxestadoAFV->inicial, TRUE);
                for(i=0; i<afv->num_simbolos; i++)
                {
                    transicao_intermediario = auxestadoAFV->move[i];
                    while(transicao_intermediario != NULL)
                    {
                        AFcriaTransicao(afn, auxestadoAFV->numero, afv->alfabeto[i], transicao_intermediario->numero);
                        transicao_intermediario = transicao_intermediario->prox;
                    }
                }
            }
            else
            {
                for(i=0; i<afv->num_simbolos; i++)
                {
                    transicao_intermediario = intermediario->move[i];
                    while(transicao_intermediario != NULL)
                    {
                        AFcriaTransicao(afn, auxestadoAFV->numero, afv->alfabeto[i], transicao_intermediario->numero);
                        transicao_intermediario = transicao_intermediario->prox;
                    }
                }
            }
            auxtransicaoAFV = auxtransicaoAFV->prox;
        }
        return afn;
    }
    
    
    
    /*Copia os outros estados para o novo automato*/

    auxestadoAFN = afn->estados;
    auxestadoAFV = afv->estados;

    while(auxestadoAFN != NULL)
    {
        while(auxestadoAFV != NULL)
        {
            /*Verifica se o estado atual já não havia sido inserido*/
            if(auxestadoAFN->numero != auxestadoAFV->numero)
            {
                AFcriaEstado(afn, auxestadoAFV->numero, auxestadoAFV->inicial, auxestadoAFV->final);
                /*Percorre o vetor de transicoes e as cria no novo automato*/
                for(i=0; i<afv->num_simbolos; i++)
                {
                    auxtransicaoAFV = auxestadoAFV->move[i];
                    while(auxtransicaoAFV != NULL)
                    {
                        AFcriaTransicao(afn, auxestadoAFV->numero, afv->alfabeto[i], auxtransicaoAFV->numero);
                    }
                }    
            }
        }
    }
    
}

AF AFafn2afd(AF afv)
{
    
}

/*Dado um numero, retorna o estado dele*/
static estado retornaEstado(AF af, int n)
{
    estado aux;
    
    aux = af->estados;
    
    while(aux != NULL)
    {
        if(aux->numero == n)
        {
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}