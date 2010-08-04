#include <stdio.h>
#include <stdlib.h>

#include "Header/grafo.h"

Grafo *Grafo_iniciar(int n) {
  int i;
  Grafo *grafo=calloc(1, sizeof(Grafo));

  grafo->tamanho=n;
  grafo->nodos=calloc(n, sizeof(Nodo));

  for (i=1; i<=n ;i++)
    grafo->nodos[i-1].valor=i;

  return grafo;
}

void Grafo_deletar(Grafo **grafo) {
  int i;

  Arestas *perc,*ant;

  for (i=0; i<(*grafo)->tamanho ;i++) {
    perc=(*grafo)->nodos[i].arestas;

    while (perc != NULL) {
      ant=perc;
      perc=perc->prox;
      free(ant);
    }
  }

  free((*grafo)->nodos);
  free(*grafo);

  *grafo=NULL;
}

void Grafo_adicionarAresta(Grafo *grafo, int a, int b, enum ArestaTipo tipo, int valor) {
  if ((a > grafo->tamanho) || (b > grafo->tamanho) || (Grafo_isAdjacente(grafo, a, b)))
    return;

  Arestas *aresta=calloc(1, sizeof(Arestas));
  aresta->valor=valor;
  aresta->nodo=&grafo->nodos[b-1];
  aresta->nodoBase=&grafo->nodos[a-1];
  aresta->tipo=tipo;

  Arestas *perc=grafo->nodos[a-1].arestas;
  if (perc == NULL)
    grafo->nodos[a-1].arestas=aresta;
  else {
    while (perc->prox != NULL)
      perc=perc->prox;

    perc->prox=aresta;
  }

  if (tipo == BIDIRECIONADA)
    Grafo_adicionarAresta(grafo, b, a, BIDIRECIONADA, valor);
}

void Grafo_removerAresta(Grafo *grafo, int a, int b) {
  if ((a > grafo->tamanho) || (b > grafo->tamanho) || (!Grafo_isAdjacente(grafo, a, b)))
    return;

  enum ArestaTipo tipo=DIRECIONADA;

  Arestas *perc=grafo->nodos[a-1].arestas;
  Arestas *ant=NULL;

  while (perc != NULL) {
    if (perc->nodo->valor == b) {
      if (ant == NULL)
        grafo->nodos[a-1].arestas=perc->prox;
      else
        ant->prox=perc->prox;

      tipo=perc->tipo;
      free(perc);
      break;
    }
    ant=perc;
    perc=perc->prox;
  }

  if (tipo == BIDIRECIONADA)
    Grafo_removerAresta(grafo, b, a);
}

int Grafo_isAdjacente(Grafo *grafo, int a, int b) {
  return (Grafo_getAresta(grafo,a,b) != NULL);
}

Arestas *Grafo_getAresta(Grafo *grafo, int a, int b) {
  if ((a > grafo->tamanho) || (b > grafo->tamanho))
    return 0;

  Arestas *perc=grafo->nodos[a-1].arestas;

  while (perc != NULL) {
    if (perc->nodo->valor == b)
      return perc;

    perc=perc->prox;
  }

  return NULL;
}

Nodo *Grafo_getNodo(Grafo *grafo, int nodo) {
  if (nodo > grafo->tamanho)
    return NULL;

  return &grafo->nodos[nodo-1];
}

void Grafo_setNodosAux(Grafo *grafo, int valor) {
  int i;

  for (i=0; i<grafo->tamanho ;i++)
    grafo->nodos[i].aux=valor;
}

void Grafo_setArestasValor(Grafo *grafo, int valor) {
  Arestas *perc;
  int i;

  for (i=0; i<grafo->tamanho ;i++) {
    perc=grafo->nodos[i].arestas;

    while (perc != NULL) {
      perc->valor=valor;
      perc=perc->prox;
    }
  }
}

Grafo *Grafo_duplicar(Grafo *base) {
  int i;
  Grafo *clone=Grafo_iniciar(base->tamanho);
  Arestas *perc;

  for (i=0; i<base->tamanho ;i++) {
    perc=base->nodos[i].arestas;

    while (perc != NULL) {
      Grafo_adicionarAresta(clone, i+1, perc->nodo->valor, DIRECIONADA, perc->valor);
      perc=perc->prox;
    }
  }

  return clone;
}
