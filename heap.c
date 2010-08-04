#include <stdlib.h>

#include "Header/heap.h"

//recebe por paremetro uma funcao para compara os elementos na heap
Heap *Heap_criar(void *funcao) {
  Heap *heap=calloc(1, sizeof(Heap));
	heap->funcao=funcao;

  return heap;
}

int compararHeap(Heap *heap, void *a, void *b) {
  if (heap->funcao == NULL)
    return (*((int *) a) < *((int *) b));
  else
    return heap->funcao(a, b);
}

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

void *Heap_remover(Heap *heap) {
  int i=1,troca;
  void *valor;
  void *tmp;
 
  if (!heap->numElm)
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

int Heap_vazio(Heap *heap) {
  return (heap->numElm == 0);
}
