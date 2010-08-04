#ifndef _HEAP_H_
#define _HEAP_H_

  typedef struct {
    int numElm;
    int tamanho;
    void **elm;

    int (*funcao)(void *, void *);
  } Heap;


  Heap *Heap_criar(void *funcao);
  void Heap_adicionar(Heap *heap, void *dado);
  void *Heap_remover(Heap *heap);
  int Heap_vazio(Heap *heap);
  void Heap_atualiza(Heap *heap, int posicao);

#endif
