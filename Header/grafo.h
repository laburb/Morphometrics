/**
 *   Morphometrics
 *   Copyright (C) 2010  Bruno C. Stone
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    int cor;
    int espessura;
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
