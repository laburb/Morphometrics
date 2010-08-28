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
 * mapa.h
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#ifndef MAPA_H_
#define MAPA_H_

  #include <gtk/gtk.h>
  #include "ponto.h"
  #include "grafo.h"

  typedef struct {
    Ponto eixoMinimo;
    Ponto eixoMaximo;
    Ponto limiteMinimo;
    Ponto limiteMaximo;

    Ponto visaoMinimo;
    Ponto visaoMaximo;

    Grafo *grafo;

    char exibirLabel;

    int CamadaAtual;
  } Mapa;

  Mapa mapa;
  unsigned char corAlpha;

  void Mapa_iniciar();
  void Mapa_calculaEixoMax();
  void Mapa_deslocarVisao(double x, double y);
  void Mapa_setVisao(Ponto min, Ponto max);
  void Mapa_calcularVisaoMaximo(int w, int h, double *mx, double *my);
  void Mapa_mousePosicao(GtkWidget *widget, double mouseX, double mouseY, double *posX, double *posY);

#endif /* MAPA_H_ */
