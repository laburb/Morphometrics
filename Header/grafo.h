#ifndef _GRAFO_H_
#define _GRAFO_H_

  #include "estruturas.h"
  #include "ponto.h"

  typedef struct arestas Arestas;
  typedef struct nodo Nodo;

  enum ArestaTipo {
    DIRECIONADA,
    BIDIRECIONADA
  };

  enum EntidadeTipo {
    ENTIDADE_LINE,
    ENTIDADE_ARC
  };

  typedef struct {
    Ponto p1;
    Ponto p2;
  } Line;

  typedef struct {
    Ponto centro;
    double raio;
    double anguloInicial;
    double anguloFinal;
  } Arc;

  struct nodo {
    int id;
    void *d;
    enum EntidadeTipo tipo;
    double impedancia;
    Arestas *arestas;
  };

  struct arestas {
    int valor;
    Nodo *nodoBase;
    Nodo *nodo;
    Arestas *prox;
    enum ArestaTipo tipo;
  };

  typedef struct {
    long int tamanho;
    Lista *nodos;
  } Grafo;

  Grafo *Grafo_iniciar();
  void Grafo_deletar(Grafo **grafo);
  Nodo *Grafo_adicionarNodo(Grafo *grafo, enum EntidadeTipo tipo);
  void Grafo_adicionarAresta(Grafo *grafo, Nodo *a, Nodo *b, enum ArestaTipo tipo, int valor);
  void Grafo_removerAresta(Grafo *grafo, Nodo *a, Nodo *b);
  int Grafo_isAdjacente(Grafo *grafo, Nodo *a, Nodo *b);

  Arestas *Grafo_getAresta(Grafo *grafo, Nodo *a, Nodo *b);
  Nodo *Grafo_getNodo(Grafo *grafo, int id);

  void Grafo_setArestasValor(Grafo *grafo, int valor);

  Grafo *Grafo_duplicar(Grafo *base);

#endif
