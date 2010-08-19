#include <stdio.h>
#include <stdlib.h>

#include "Header/util.h"
#include "Header/grafo.h"

Nodo *nodoAtual;

static int Grafo_nodoAcao(Grafo *grafo, int id,char acao) {
  static int opcao=NAO_MUDAR_ID|ADD_CERTO;
  Lista **primNodo=&grafo->nodos;

  if (acao=='n') {
    nodoAtual=(Nodo *) Lista_acao('n',primNodo,id,opcao,sizeof(Nodo));
    grafo->tamanho++;
  }
  else if (acao=='d') {
    nodoAtual=(Nodo *) Lista_acao('d',primNodo,id,opcao,0);
    if (nodoAtual) grafo->tamanho--;
  }
  else if (acao=='z') {
    while (*primNodo != NULL) {
      Nodo *nodo=(Nodo *) (*primNodo)->d;
      free(nodo->d);

      Grafo_nodoAcao(grafo,(*primNodo)->id,'d');
    }

    grafo->tamanho=0;
  }
  else if (acao=='s') {
    nodoAtual=(Nodo *) Lista_acao('s',primNodo,id,opcao,0);
    return (!nodoAtual)?0:1;
  }

  return 1;
}

/**
 *  Inciar o grafo.
 *
 *  @return Estrutura do grafo
 *
 */

Grafo *Grafo_iniciar() {
  Grafo *grafo=calloc(1, sizeof(Grafo));

  grafo->tamanho=0;
  grafo->nodos=NULL;

  return grafo;
}

/**
 *  Adiciona vertice ao grafo
 *
 *  @param grafo Estrutura do grafo
 *
 *  @return Nodo criado
 *
 */

Nodo *Grafo_adicionarNodo(Grafo *grafo, enum EntidadeTipo tipo) {
  Grafo_nodoAcao(grafo, grafo->tamanho+1, 'n');
  nodoAtual->id=grafo->tamanho;
  nodoAtual->impedancia=1.0;
  nodoAtual->tipo=tipo;

  if (tipo == ENTIDADE_LINE)
    nodoAtual->d=calloc(1, sizeof(Line));
  else if (tipo == ENTIDADE_ARC)
    nodoAtual->d=calloc(1, sizeof(Arc));

  return nodoAtual;
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
  Arestas *perc,*ant;

  forList(Nodo *, nodoPerc, (*grafo)->nodos) {
    perc=nodoPerc->arestas;

    while (perc != NULL) {
      ant=perc;
      perc=perc->prox;
      free(ant);
    }
  }

  Grafo_nodoAcao(*grafo,0,'z');
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

void Grafo_adicionarAresta(Grafo *grafo, Nodo *a, Nodo *b, enum ArestaTipo tipo, int valor) {
  if ((a == NULL) || (b == NULL) || (Grafo_isAdjacente(grafo, a, b)))
    return;

  Arestas *aresta=calloc(1, sizeof(Arestas));
  aresta->valor=valor;
  aresta->nodo=b;
  aresta->nodoBase=a;
  aresta->tipo=tipo;

  Arestas *perc=a->arestas;
  if (perc == NULL)
    a->arestas=aresta;
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

void Grafo_removerAresta(Grafo *grafo, Nodo *a, Nodo *b) {
  if ((a == NULL) || (b == NULL) || (!Grafo_isAdjacente(grafo, a, b)))
    return;

  enum ArestaTipo tipo=DIRECIONADA;

  Arestas *perc=a->arestas;
  Arestas *ant=NULL;

  while (perc != NULL) {
    if (perc->nodo->id == b->id) {
      if (ant == NULL)
        a->arestas=perc->prox;
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

int Grafo_isAdjacente(Grafo *grafo, Nodo *a, Nodo *b) {
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

Arestas *Grafo_getAresta(Grafo *grafo, Nodo *a, Nodo *b) {
  if ((a == NULL) || (b == NULL))
    return NULL;

  Arestas *perc=a->arestas;

  while (perc != NULL) {
    if (perc->nodo->id == b->id)
      return perc;

    perc=perc->prox;
  }

  return NULL;
}

/**
 *  Retorna o nodo.
 *
 *  @param grafo Estrutura do grafo
 *  @param valor Id do vertice
 *
 *  @return Estrutura do vertice
 *
 *  @retval ponteiro para o nodo
 *  @retval NULL Nodo não existe
 *
 */

Nodo *Grafo_getNodo(Grafo *grafo, int id) {
  forList(Nodo *, nodoPerc, grafo->nodos) {
    if (nodoPerc->id == id)
      return nodoPerc;
  }

  return NULL;
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

  forList(Nodo *, nodoPerc, grafo->nodos) {
    perc=nodoPerc->arestas;

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
  Grafo *clone=Grafo_iniciar(base->tamanho);
  Arestas *perc;

  forList(Nodo *, nodoPerc, base->nodos) {
    perc=nodoPerc->arestas;

    while (perc != NULL) {
      Grafo_adicionarAresta(clone, nodoPerc, perc->nodo, DIRECIONADA, perc->valor);
      perc=perc->prox;
    }
  }

  return clone;
}
