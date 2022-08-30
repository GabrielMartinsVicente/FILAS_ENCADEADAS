#include <stdio.h>
#include <stdbool.h>   // p/ variavel bool
#include <stdlib.h>    // necessário p/ as funções rand() e srand()
#include <time.h>      //necessário p/ função time()
#include "mtwister.h"

struct Estrutura{

  int valor;
  struct Estrutura *next;
  struct Estrutura *back;

};

struct Estrutura *inicio =  (struct Estrutura *) NULL;
struct Estrutura *atual  =  (struct Estrutura *) NULL;
struct Estrutura *novo   =  (struct Estrutura *) NULL;
struct Estrutura *aux    =  (struct Estrutura *) NULL;

int valorAleatorio(){
  
  srand(time(NULL));
  MTRand r = seedRand(rand() % 100);
  return (int)(genRand(&r)*1000000)+1;
  
}

void insercao(){

  novo = (struct Estrutura *) malloc(sizeof(struct Estrutura));
  novo->valor = valorAleatorio();        /* ### ARRUMAR ALEATÓRIO ### */
  novo->next = NULL;
  
  if(inicio == (struct Estrutura *) NULL){
    inicio = atual = novo;

  }

  else{

    atual = inicio;
    
    while(atual->next != (struct Estrutura *) NULL){
      
      atual = atual->next;
      
    }

    atual->next = novo;
    novo->back = atual;

  }

}

void inverteTudo(){

  aux = inicio;
  novo = (struct Estrutura *) NULL;
  int laco = 1;
  
  while(aux->next != (struct Estrutura *) NULL){

    aux = aux->next;
    laco++;
    
  }

  inicio = aux;
  
  for(int i = 0; i < laco; i++){

    novo = aux->next;
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
      printf("Valor do item = %d\n",atual->valor);
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
    free(novo);
  
  }

  inicio =  (struct Estrutura *) NULL;
  atual  =  (struct Estrutura *) NULL;
  novo   =  (struct Estrutura *) NULL;
  aux    =  (struct Estrutura *) NULL;
  
}

int main() {

int tamanho, amostra;  //amostra é a variável de controle para a repetição das instruções
double populacao[50];  //populacao é apenas o total operações de cada tipo
clock_t tempo;
double soma = 0;

printf( "\nQual o tamanho de locacao da pilha? " );
scanf("%i",&tamanho);
  
//-------------------- 1°: Tempo de inserção ---------------------------

tempo = clock();

for(int i = 1;i<=tamanho;i++){
  
  insercao();
  
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