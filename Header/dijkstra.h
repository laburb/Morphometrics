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
