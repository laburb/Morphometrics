#include <stdlib.h>

#include "Header/heap.h"

/**
 *  Cria heap.
 *
 *  @param funcao Funcao para compara os elementos no heap
 *
 *  @return Estrutura do heap
 *
 *  @retval ponteiro para o heap
 *
 */

Heap *Heap_criar(void *funcao) {
  Heap *heap=calloc(1, sizeof(Heap));
	heap->funcao=funcao;

  return heap;
}

static int compararHeap(Heap *heap, void *a, void *b) {
  if (heap->funcao == NULL)
    return (*((int *) a) < *((int *) b));
  else
    return heap->funcao(a, b);
}

/**
 *  Adiciona elemento no heap.
 *
 *  @param heap Estrutura do heap
 *  @param dado Dado a ser adicionado
 *
 */

void Heap_adicionar(Heap *heap, void *dado) {
  int i;
  void *tmp;

  heap->numElm++;

  if (heap->numElm > heap->tamanho) {
    heap->tamanho=20+heap->tamanho*2;

    heap->elm=realloc(heap->elm, heap->tamanho * sizeof(void *));
  }

  heap->elm[heap->numElm]=dado;

  for (i=heap->numElm; i!=1 ;i/=2) {
    if (compararHeap(heap, heap->elm[i], heap->elm[i/2])) {
      tmp=heap->elm[i/2];
      heap->elm[i/2]=heap->elm[i];
      heap->elm[i]=tmp;
    }
    else
      break;
  }
}

/**
 *  Remove elemento do heap e o retorna.
 *
 *  @param heap Estrutura do heap
 *
 *  @retval ponteiro para o dado
 *  @retval NULL Heap vazia
 *
 */

void *Heap_remover(Heap *heap) {
  int i=1,troca;
  void *valor;
  void *tmp;
 
  if (Heap_vazio(heap))
    return NULL;

  valor=heap->elm[1];
  heap->elm[1]=heap->elm[heap->numElm--];
  
  do {
    troca=0;

    if ((i*2 <= heap->numElm) && (compararHeap(heap, heap->elm[i*2], heap->elm[i])))
      troca=i*2;
    if ((i*2+1 <= heap->numElm) && (compararHeap(heap, heap->elm[i*2+1], heap->elm[i])))
      troca=i*2+1;

    if ((troca) && (compararHeap(heap, heap->elm[i*2], heap->elm[troca])))
      troca=i*2;

    if (troca) {
      tmp=heap->elm[troca];
      heap->elm[troca]=heap->elm[i];
      heap->elm[i]=tmp;

      i=troca;
    }
  } while(troca);

  return valor;
}

/**
 *  Atualiza elemento na heap.
 *
 *  @param heap Estrutura do heap
 *  @param posicao Posição que o dado esta na matriz do heap
 *
 */

void Heap_atualiza(Heap *heap, int posicao) {
  void *tmp;

  if ((posicao <= heap->numElm) && (posicao >= 1)) {
    for (; posicao != 1 ;posicao = posicao/2) {
      if (compararHeap(heap, heap->elm[posicao], heap->elm[posicao/2])) {
        tmp = heap->elm[posicao/2];
        heap->elm[posicao/2] = heap->elm[posicao];
        heap->elm[posicao] = tmp;
      }
      else
        break;
    }
  }
}

/**
 *  Verifica se heap esta vazia.
 *
 *  @param heap Estrutura do heap
 *
 *  @retval 1 Vazio
 *  @retval 0 Possui elementos
 *
 */

int Heap_vazio(Heap *heap) {
  return (heap->numElm == 0);
}
