#include <stdio.h>
#include <stdlib.h>

#include "Header/grafo.h"

/**
 *  Inciar o grafo.
 *
 *  @param n Numero de vertices
 *
 *  @return Estrutura do grafo
 *
 */

Grafo *Grafo_iniciar(int n) {
  int i;
  Grafo *grafo=calloc(1, sizeof(Grafo));

  grafo->tamanho=n;
  grafo->nodos=calloc(n, sizeof(Nodo));

  for (i=1; i<=n ;i++)
    grafo->nodos[i-1].valor=i;

  return grafo;
}

/**
 *  Libera grafo da memória.
 *
 *  @param grafo Ponteiro para estrutura do grafo
 *
 *  @retval ponteiro para o grafo
 *
 */

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

/**
 *  Adiciona aresta entre o vertice 'a' e o 'b'.
 *
 *  @param grafo Estrutura do grafo
 *  @param a Id do vertice de origem
 *  @param b Id do vertice de destino
 *  @param tipo DIRECIONADA ou BIDIRECIONADA
 *  @param valor Valor da aresta
 *
 */

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

/**
 *  Remove aresta entre 'a' e 'b' se for BIDIRECIONADA remove tambem de 'b' para 'a'.
 *
 *  @param grafo Estrutura do grafo
 *  @param a Id do vertice de origem
 *  @param b Id do vertice de destino
 *
 */

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

/**
 *  Verifica se o vertice 'a' é adjacente ao 'b'.
 *
 *  @param grafo Estrutura do grafo
 *  @param a Id do vertice de origem
 *  @param b Id do vertice de destino
 *
 *  @retval 1 É adjacente
 *  @retval 0 Não é adjacente
 *
 */

int Grafo_isAdjacente(Grafo *grafo, int a, int b) {
  return (Grafo_getAresta(grafo,a,b) != NULL);
}

/**
 *  Retorna o vertice de 'a' para 'b'.
 *
 *  @param grafo Estrutura do grafo
 *  @param a Id do vertice de origem
 *  @param b Id do vertice de destino
 *
 *  @return Estrutura do vertice
 *
 *  @retval ponteiro para aresta
 *  @retval NULL Vertice não existe
 *
 */

Arestas *Grafo_getAresta(Grafo *grafo, int a, int b) {
  if ((a > grafo->tamanho) || (b > grafo->tamanho))
    return NULL;

  Arestas *perc=grafo->nodos[a-1].arestas;

  while (perc != NULL) {
    if (perc->nodo->valor == b)
      return perc;

    perc=perc->prox;
  }

  return NULL;
}

/**
 *  Retorna o vertice.
 *
 *  @param grafo Estrutura do grafo
 *  @param nodo Id do vertice de origem
 *
 *  @return Estrutura do vertice
 *
 *  @retval ponteiro para o nodo
 *  @retval NULL Nodo não existe
 *
 */

Nodo *Grafo_getNodo(Grafo *grafo, int nodo) {
  if (nodo > grafo->tamanho)
    return NULL;

  return &grafo->nodos[nodo-1];
}

/**
 *  Seta o valor da variavel aux de todos os vertices.
 *
 *  @param grafo Estrutura do grafo
 *  @param valor Valor
 *
 */

void Grafo_setNodosAux(Grafo *grafo, int valor) {
  int i;

  for (i=0; i<grafo->tamanho ;i++)
    grafo->nodos[i].aux=valor;
}

/**
 *  Seta o valor de todas as arestas.
 *
 *  @param grafo Estrutura do grafo
 *  @param valor Valor
 *
 */

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

/**
 *  Duplica o grafo.
 *
 *  @param base Estrutura do grafo a que ira ser dublicado
 *
 *  @return Estrutura do grafo
 *
 *  @retval ponteiro para o grafo dublicado
 *
 */

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
