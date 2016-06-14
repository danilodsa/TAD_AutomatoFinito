/* 
 * File:   automato.h
 * Author: daniloalves
 *
 * Created on 14 de Junho de 2016, 01:49
 */

#ifndef AUTOMATO_H
#define	AUTOMATO_H


typedef enum _bool Bool;
typedef struct Taf *AF;
typedef struct Tnodolista *Lista;
typedef struct Testado *estado;

enum _bool 
{
   FALSE = 0,
   TRUE = 1
};

struct Tnodolista
{
    int numero;
    struct Tnodolista *prox;
};

struct Taf 
{
    int num_simbolos;   /*Tamanho do alfabeto sem lambda*/
    char* alfabeto;     /*String com simbolos do alfabeto*/
    int num_estados;    /*Numero de estados do AF*/
    struct Testado *estados; /*Lista de estados do AF*/           
};

struct Testado
{
    int numero;     /*numero identificador do estado*/
    Bool inicial;   /*Informa se o estado e inicial*/
    Bool final;     /*Informa se o estado e final*/
    Lista move[];   /*vetordelistas , mapeia : Símbolo −−> Estado+*/
};

/*Cria um automato*/
AF AFcria(char* alfabeto);

/*Destroi automato*/
AF AFdestroi(AF af);

/*Cria o estado 'e' no AF*/
void AFcriaEstado(AF af, int e, Bool inicial, Bool final);

/*Destroi o estado 'e' no AF*/
void AFdestroiEstado(AF af, int e);

/*cria a transição (e1,s) –> e2 no AF*/
void AFcriaTransicao(AF af, int e1, char s, int e2);

/*destroi a transição (e1,s) –> e2 no AF*/
void AFdestroiTransicao(AF af, int e1, char s, int e2);

/*o estado e um estado inicial?*/
Bool AFestadoInicial(AF af, int e);

/*o estado e um estado final?*/
Bool AFestadoFinal(AF af, int e);

/*Verifica se o automato é deterministico*/
Bool AFchecaAFD(AF af);

/*Verifica se o automato possui movimentos vazios*/
Bool AFchecaAFv(AF af);

/*Retorna o estado destino*/
int AFmoveAFD(AF af, int e, char s);

/*Retorna os possiveis destinos*/
Lista AFfecho(AF af, Lista e, char s);

/*salva o automato em um arquivo txt*/
void AFsalva(AF af, char* nomedoarquivo);

/*Carrega o automato de um arquivo txt*/
AF AFcarrega(char* nomedoarquivo);

#endif	/* AUTOMATO_H */

