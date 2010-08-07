/*
 * mapa.h
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#ifndef MAPA_H_
#define MAPA_H_

  typedef struct {
    Ponto eixoMinimo;
    Ponto eixoMaximo;
    Ponto limiteMinimo;
    Ponto limiteMaximo;
    int CamadaAtual;
    //BOOL CamadaAtiva[NUMCAMADAS];
  } Mapa;

  Mapa mapa;

#endif /* MAPA_H_ */
