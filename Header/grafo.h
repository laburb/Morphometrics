#ifndef _GRAFO_H_
#define _GRAFO_H_

  typedef struct arestas Arestas;
  typedef struct nodo Nodo;

  enum ArestaTipo {
    DIRECIONADA,
    BIDIRECIONADA
  };

  struct nodo {
    int valor;
    int aux;
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
    int tamanho;
    Nodo *nodos;
  } Grafo;


  Grafo *Grafo_iniciar(int n);
  void Grafo_deletar(Grafo **grafo);
  void Grafo_adicionarAresta(Grafo *grafo, int a, int b, enum ArestaTipo tipo, int valor);
  void Grafo_removerAresta(Grafo *grafo, int a, int b);
  int Grafo_isAdjacente(Grafo *grafo, int a, int b);

  Arestas *Grafo_getAresta(Grafo *grafo, int a, int b);
  Nodo *Grafo_getNodo(Grafo *grafo, int nodo);

  void Grafo_setNodosAux(Grafo *grafo, int valor);
  void Grafo_setArestasValor(Grafo *grafo, int valor);

  Grafo *Grafo_duplicar(Grafo *base);

#endif