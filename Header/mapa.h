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

  void Mapa_iniciar();
  void Mapa_calculaEixoMax();
  void Mapa_deslocarVisao(double x, double y);
  void Mapa_setVisao(Ponto min, Ponto max);
  void Mapa_calcularVisaoMaximo(int w, int h, double *mx, double *my);
  void Mapa_mousePosicao(GtkWidget *widget, double mouseX, double mouseY, double *posX, double *posY);

#endif /* MAPA_H_ */
