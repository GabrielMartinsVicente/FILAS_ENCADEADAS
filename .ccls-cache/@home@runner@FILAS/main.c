#include <stdio.h>
#include <stdbool.h>   // p/ variavel bool
#include <stdlib.h>    // necessário p/ as funções rand() e srand()
#include <time.h>      //necessário p/ função time()
#include "mtwister.h"

struct Estrutura{

  double valor;            /* O valor da estrutura é double por conta do 
                            retorno da variável aleatória ser double */
  struct Estrutura *next;  //Ponteiro que aponta para o próximo item
  struct Estrutura *back;  //Ponteiro que aponta para o item anterior

};

double valorAleatorio(MTRand r){

  return genRand(&r)*1000000;  /* Retorna valor aleatório.
                            
        OBS: A biblioteca utilizada para gerar valores aleatórios pela metodologia
            twister de Mersenne infelizmente não funciona como deveria ter
            sido aplicado nesse programa. Mas utilizando um gerador de variavel
            aleatória do próprio C como rand(), funciona perfeitamente.
                                                        */

}

struct Estrutura *inicio =  (struct Estrutura *) NULL;   // Referência do começo das Filas encadeadas
struct Estrutura *atual  =  (struct Estrutura *) NULL;   /* Sendo minha estrutura que faz interação 
                                                              para a inserção de uma nova estrutura */
struct Estrutura *novo   =  (struct Estrutura *) NULL;   /* Estrutura para a criação de uma nova estrutura
                                                          e tambem como apoio para a inversão da das Filas                                                                    encadeadas  */
struct Estrutura *aux    =  (struct Estrutura *) NULL;  //Estrutura de apoio para fazer as operações

void insercao(MTRand r){

  novo = (struct Estrutura *) malloc(sizeof(struct Estrutura));  // Cria espaço na memória da nova estrutura
  novo->valor = valorAleatorio(r);        
  novo->next = NULL;
  
  if(inicio == (struct Estrutura *) NULL){    //1° Situação quando a fila esta vazia
    inicio = atual = novo;
    
  }

  else{

    atual = inicio;
    
    while(atual->next != (struct Estrutura *) NULL){  // Interação que verifica se o próximo valor é Null
      
      atual = atual->next;
      
    }

    atual->next = novo;    // Ponteiro da última estrutura aponta para o novo item criado
    novo->back = atual;    // Ponteiro da nova estrutura aponta para a estrutura anterior

  }

}

void inverteTudo(){

  aux = inicio;
  novo = (struct Estrutura *) NULL;
  int laco = 1;

  while(aux->next != (struct Estrutura *) NULL){

    aux = aux->next;
    laco++;      // Interação para saber quantos itens conectados existem nessas filas encadeadas

  }

  inicio = aux;

  for(int i = 0; i < laco; i++){

    novo = aux->next;          /* 'novo' é o ponteiro de apoio para fazer a lógica de inversão */
    aux->next = aux->back;
    aux->back = novo; 

    if(aux != (struct Estrutura *) NULL ){
      aux = aux->next;
    }

  }

}

void imprimirValores(){

  atual = inicio;

  if(atual == (struct Estrutura *) NULL){
    printf("Valor do item = NULL\n");
  }

  else{

    while(atual != (struct Estrutura *) NULL){
      printf("Valor do item = %lf\n",atual->valor);
      atual = atual->next;
    }
    
  }
  
}

int buscaValor(int posicao){

  aux = inicio;
  bool cheia = false;
  int laco = 1;
  
  while(aux->next != (struct Estrutura *) NULL){

    aux = aux->next;
    laco++;
    
  }

  if(laco < posicao){
    cheia = true;
  }

  else{
    aux = inicio;
    for(int i = 1; i < posicao; i++){
      aux = aux->next;
    }
  }

  if(cheia == true){

    printf("A Fila não tem esse tamanho de posicao\n");
    return 0;
    
  }

  else{

    if(laco % 2 == 0){ 
      return aux->valor;
    }
    else{
      if(posicao == 1){
        printf("VALOR NA POSICAO = NULL\n");
        return 0;
      }
      else{  
        return aux->back->valor;
      }

    }

  }
  
}

void apagarTudo(){

  aux=inicio;
  
  while(aux != (struct Estrutura *) NULL){

    novo = aux;
    aux = aux->next;
    free(novo);    //libera o espaço de memória que foi previamente alocado
  
  }

  inicio =  (struct Estrutura *) NULL;    //Reseta todas as estruturas de apoio
  atual  =  (struct Estrutura *) NULL;
  novo   =  (struct Estrutura *) NULL;
  aux    =  (struct Estrutura *) NULL;
  
}

int main() {

MTRand r = seedRand(1337);
int tamanho;          
clock_t tempo;
double soma = 0;

printf( "\nQual o tamanho de locacao da pilha? " );
scanf("%i",&tamanho);

printf("\nOBS: Em média o tempo de inserção esta entre 30s\n\n");

//-------------------- 1°: Tempo de inserção ---------------------------

tempo = clock();

for(int i = 1;i<=tamanho;i++){

  insercao(r);

}

tempo = clock() - tempo;

printf("\nTempo para inserir: %fs\n\n",((double)tempo)/CLOCKS_PER_SEC);

//------------------- 2°: Tempo de reverter ----------------------------

tempo = clock();

inverteTudo();

tempo = clock() - tempo;

printf("\nTempo para reverter: %fs\n\n",((double)tempo)/CLOCKS_PER_SEC);

//--------------- 3°: Tempo de Encontrar item do meio ------------------
  
tempo = clock();

buscaValor(tamanho/2);
  
tempo = clock() - tempo;

printf("\nTempo para encontrar item no meio: %fs\n\n",((double)tempo)/CLOCKS_PER_SEC);

//--------------- 4°: Tempo de Apagar todos os itens  -----------------

tempo = clock();

apagarTudo();
  
tempo = clock() - tempo;

printf("\nTempo para apagar todos os itens : %fs\n\n",((double)tempo)/CLOCKS_PER_SEC);


return 0;

}