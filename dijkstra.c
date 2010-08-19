/*
 * dijkstra.c
 *
 *  Created on: 16/08/2010
 *      Author: bruno
 */

#include <stdlib.h>
#include <limits.h>

#include "Header/heap.h"
#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/util.h"
#include "Header/math2.h"
#include "Header/dijkstra.h"

//funcao para comparar elementos na heap
int comparaDijkstra(void *a, void *b) {
  DijksDados *a1=(DijksDados *) a;
  DijksDados *a2=(DijksDados *) b;

  return (a1->custo < a2->custo);
}

//imprime caminho invertido
void dijkstraPrintCam(DijksDados *dados, Nodo *nodo) {
  if (nodo) {
    dijkstraPrintCam(dados,dados[nodo->id-1].caminho);
    printf("%d->",nodo->id);
  }
}

static double calcularCusto(Nodo *nodo, int tipo) {
  double custo;

  if (tipo == 1) {
    custo=Math2_comprimento(nodo)*nodo->impedancia;
  }
  else if (tipo == 2)
    custo=nodo->impedancia;

  return custo;
}

DijksDados *dijkstra(Grafo *grafo, int origem, int tipo) {
  double custo;
  int pos;
  DijksDados *dados=calloc(grafo->tamanho, sizeof(DijksDados));
  DijksDados *dijkAtual;
  DijksDados *dijkTmp;

  Arestas *aresta;
  Heap *Q=Heap_criar(comparaDijkstra);

  //Cria heap
  forList (Nodo *, percorreNodo, mapa.grafo->nodos) {
    dijkAtual=&dados[percorreNodo->id-1];

    dijkAtual->nodo=percorreNodo;
    dijkAtual->custo=(percorreNodo->id != origem)? INT_MAX:0;

    Heap_adicionar(Q, dijkAtual);
  }

  while (!Heap_vazio(Q)) {
    dijkAtual=(DijksDados *) Heap_remover(Q);

    aresta=dijkAtual->nodo->arestas;

    //percorre arestas
    while (aresta != NULL) {
      custo=calcularCusto(aresta->nodo, tipo);

      dijkTmp=&dados[aresta->nodo->id-1];
      //printf("%d %lf\n",dijkTmp->nodo->id,dijkTmp->geometrico);

      if (dijkAtual->custo + custo < dijkTmp->custo) {
        dijkTmp->custo=dijkAtual->custo + custo;
        dijkTmp->geometrico=dijkAtual->geometrico+custo+Math2_comprimento(dijkAtual->nodo);
        dijkTmp->topologico=dijkAtual->topologico+1;

        dijkTmp->caminho=dijkAtual->nodo;

        //procura posicao do nodo na heap
        for (pos=1; pos<=Q->numElm ;pos++)
          if (Q->elm[pos] == dijkTmp)
            break;

        Heap_atualiza(Q, pos);
      }

      aresta=aresta->prox;
    }
  }

//Imprime todos os menores caminhos possiveis
  /*for (i=0; i<grafo->tamanho ;i++) {
    if ((origem == i+1) || (grafo->nodos[i].aux == INT_MAX))
      continue;

    printf("Caminho de %d ate %d: ",origem,i+1);
    dijkstraPrintCam(caminho,caminho[i]);
    printf("%d , distancia: %d\n",i+1, grafo->nodos[i].aux);
  }
*/
  Heap_remover(Q);

  return dados;
}
