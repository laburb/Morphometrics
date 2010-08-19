/*
 * dijkstra.h
 *
 *  Created on: 16/08/2010
 *      Author: bruno
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

  typedef struct {
    int topologico;
    double geometrico;
    double custo;
    Nodo *caminho;
    Nodo *nodo;
  } DijksDados;

  void dijkstraPrintCam(DijksDados *dados, Nodo *nodo);
  DijksDados *dijkstra(Grafo *grafo, int origem, int tipo);

#endif /* DIJKSTRA_H_ */
