/*
 * Eixo.h
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#ifndef PONTO_H_
#define PONTO_H_

  typedef struct {
    double x;
    double y;
  } Ponto;

  Ponto Ponto_menos(Ponto p1, Ponto p2);
  Ponto Ponto_mais(Ponto p1, Ponto p2);
  void Ponto_vezes(Ponto *pt, double vezes);

#endif /* PONTO_H_ */
