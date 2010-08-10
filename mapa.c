/*
 * mapa.c
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#include "Header/ponto.h"
#include "Header/grafo.h"
#include "Header/util.h"
#include "Header/mapa.h"

#include <math.h>

/**
 * Acha o maior e o menor eixo.
 */

void Mapa_calculaEixoMax() {
  Ponto eixoMax;
  Ponto eixoMin;

  Nodo *primNodo=(Nodo *) grafo->nodos->d;

  if (!primNodo)
    return;

   eixoMax.x=primNodo->p1.x;
   eixoMin.x=primNodo->p1.x;
   eixoMax.y=primNodo->p1.y;
   eixoMin.y=primNodo->p1.y;


  forList(Nodo *, nodoPerc, grafo->nodos) {
    if (nodoPerc->p1.x > eixoMax.x)
      eixoMax.x=nodoPerc->p1.x;

    if (nodoPerc->p2.x > eixoMax.x)
      eixoMax.x=nodoPerc->p2.x;

    if (nodoPerc->p1.y > eixoMax.y)
      eixoMax.y=nodoPerc->p1.y;

    if (nodoPerc->p2.y > eixoMax.y)
      eixoMax.y=nodoPerc->p2.y;

    if (nodoPerc->p1.x < eixoMin.x)
      eixoMin.x=nodoPerc->p1.x;

    if (nodoPerc->p2.x < eixoMin.x)
      eixoMin.x=nodoPerc->p2.x;

    if (nodoPerc->p1.y < eixoMin.y)
      eixoMin.y=nodoPerc->p1.y;

    if (nodoPerc->p2.y < eixoMin.y)
      eixoMin.y=nodoPerc->p2.y;
  }

  mapa.eixoMaximo.x=eixoMax.x;
  mapa.eixoMaximo.y=eixoMax.y;

  mapa.eixoMinimo.x=eixoMin.x;
  mapa.eixoMinimo.y=eixoMin.y;
}

void Mapa_visao(double x, double y) {
  double diffX=fabs(mapa.eixoMaximo.x-mapa.eixoMinimo.x);
  double diffY=fabs(mapa.eixoMaximo.y-mapa.eixoMinimo.y);
  x=x*diffX/500;
  y=y*diffY/500;

  mapa.visaoMinimo.x=mapa.eixoMinimo.x-x;
  mapa.visaoMinimo.y=mapa.eixoMinimo.y-y;

  mapa.visaoMaximo.x=mapa.eixoMaximo.x-x;
  mapa.visaoMaximo.y=mapa.eixoMaximo.y-y;
}
