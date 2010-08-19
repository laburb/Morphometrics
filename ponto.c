/*
 * ponto.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include "Header/ponto.h"

Ponto Ponto_menos(Ponto p1, Ponto p2) {
  Ponto ret;
  ret.x=p1.x-p2.x;
  ret.y=p1.y-p2.y;

  return ret;
}

Ponto Ponto_mais(Ponto p1, Ponto p2) {
  Ponto ret;
  ret.x=p1.x+p2.x;
  ret.y=p1.y+p2.y;

  return ret;
}

void Ponto_vezes(Ponto *pt, double vezes) {
  pt->x*=vezes;
  pt->y*=vezes;
}
