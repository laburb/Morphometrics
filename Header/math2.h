/*
 * math2.h
 *
 *  Created on: 13/08/2010
 *      Author: bruno
 */

#ifndef MATH2_H_
#define MATH2_H_

  int Math2_interseccao(Nodo *nodo1, Nodo *nodo2);
  int Math2_intrSegmentoRetas(Ponto *p1Ini, Ponto *p1Fim, Ponto *p2Ini, Ponto *p2Fim);
  int Math2_intrSegmentoRetaArco(Line *linha, Arc *arco);
  int Math2_intrSegmentoRetaCirculo(Line *linha, Ponto *centro, double raio);

  void Math2_pontoMedio(Nodo *nodo, double *medioX, double *medioY);
  void Math2_pontoMedioSegmentoReta(Ponto *p1, Ponto *p2, double *medioX, double *medioY);

  double Math2_comprimento(Nodo *nodo);
  double Math2_distanciaPontos(Ponto *ptIni, Ponto *ptFim);

  void Math2_extremos(Nodo *nodo, double *p1x, double *p1y, double *p2x, double *p2y);

#endif /* MATH2_H_ */
