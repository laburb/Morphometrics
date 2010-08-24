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
