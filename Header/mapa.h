/*
 * mapa.h
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#ifndef MAPA_H_
#define MAPA_H_

  #include "ponto.h"

  typedef struct {
    Ponto eixoMinimo;
    Ponto eixoMaximo;
    Ponto limiteMinimo;
    Ponto limiteMaximo;

    Ponto visaoMinimo;
    Ponto visaoMaximo;
    int CamadaAtual;
    //BOOL CamadaAtiva[NUMCAMADAS];
  } Mapa;

  Mapa mapa;

  void Mapa_calculaEixoMax();
  void Mapa_visao(double x, double y);

#endif /* MAPA_H_ */
