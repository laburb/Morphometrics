/*
 * mapa.c
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#include "Header/grafo.h"
#include "Header/util.h"
#include "Header/math2.h"
#include "Header/mapa.h"

#include <math.h>

/**
 * Inicia o mapa com configuracões padrões
 */

void Mapa_iniciar() {
 mapa.eixoMaximo.x = 391071.78125;
 mapa.eixoMaximo.y = 6492782.0;
 mapa.eixoMinimo.x = 389957.125;
 mapa.eixoMinimo.y = 6491600.5;
 mapa.limiteMaximo.x = 391629.125;
 mapa.limiteMaximo.y = 6493373.0;
 mapa.limiteMinimo.x = 389399.8125;
 mapa.limiteMinimo.y = 6491010.0;

 mapa.CamadaAtual=0;
 mapa.exibirLabel=0;

 Mapa_setVisao(mapa.eixoMinimo,mapa.eixoMaximo);
}

/**
 * Acha o maior e o menor eixo.
 */

void Mapa_calculaEixoMax() {
  double p1x, p1y, p2x, p2y;

  Ponto eixoMax;
  Ponto eixoMin;

  Nodo *primNodo=(Nodo *) mapa.grafo->nodos->d;

  if (!primNodo)
    return;

  Math2_extremos(primNodo, &p1x, &p1y, &p2x, &p2y);

   eixoMax.x=p1x;
   eixoMin.x=p1x;
   eixoMax.y=p1y;
   eixoMin.y=p1y;


  forList(Nodo *, nodoPerc, mapa.grafo->nodos) {
    Math2_extremos(nodoPerc, &p1x, &p1y, &p2x, &p2y);

    if (p1x > eixoMax.x)
      eixoMax.x=p1x;

    if (p2x > eixoMax.x)
      eixoMax.x=p2x;

    if (p1y > eixoMax.y)
      eixoMax.y=p1y;

    if (p2y > eixoMax.y)
      eixoMax.y=p2y;

    if (p1x < eixoMin.x)
      eixoMin.x=p1x;

    if (p2x < eixoMin.x)
      eixoMin.x=p2x;

    if (p1y < eixoMin.y)
      eixoMin.y=p1y;

    if (p2y < eixoMin.y)
      eixoMin.y=p2y;
  }

  mapa.eixoMaximo.x=eixoMax.x;
  mapa.eixoMaximo.y=eixoMax.y;

  mapa.eixoMinimo.x=eixoMin.x;
  mapa.eixoMinimo.y=eixoMin.y;
}

/**
 * Seta a visão do mapa.
 *
 * @param min Menor ponto vizivel do mapa
 * @param max Maior ponto vizivel do mapa
 *
 */

void Mapa_setVisao(Ponto min, Ponto max) {
  mapa.visaoMinimo.x=min.x;
  mapa.visaoMinimo.y=min.y;

  mapa.visaoMaximo.x=max.x;
  mapa.visaoMaximo.y=max.y;
}

/**
 * Desloca a visão do mapa
 *
 * @param x Deslocamento x
 * @param y Deslocamento y
 *
 */
void Mapa_deslocarVisao(double x, double y) {
  double diffX=fabs(mapa.eixoMaximo.x-mapa.eixoMinimo.x);
  double diffY=fabs(mapa.eixoMaximo.y-mapa.eixoMinimo.y);
  x=x*diffX/500;
  y=y*diffY/500;

  mapa.visaoMinimo.x-=x;
  mapa.visaoMinimo.y-=y;

  mapa.visaoMaximo.x-=x;
  mapa.visaoMaximo.y-=y;
}

/**
 * Calcula a visão maxima apartir do tamanho da tela, para manter a proporção.
 *
 * @param w Largura da tela de desenho
 * @param h Altura da tela de desenho
 * @param mx Retorno da visão maxima em x
 * @param my Retorno da visão maxima em y
 *
 */

void Mapa_calcularVisaoMaximo(int w, int h, double *mx, double *my) {
  double dx, dy;

  if ( w <= 0 || h <= 0 )
    return;

  dx = mapa.visaoMaximo.x - mapa.visaoMinimo.x;
  dy = mapa.visaoMaximo.y - mapa.visaoMinimo.y;


  *mx=mapa.visaoMaximo.x;
  *my=mapa.visaoMaximo.y;

  if (dx > dy)
    *my=mapa.visaoMinimo.y + dx*h/w;
  else
    *mx=mapa.visaoMinimo.x + dy*w/h;
}

/**
 * Calcula a posição do mouse relativa no mapa.
 *
 * @param widget Widget da tela de desenho
 * @param mouseX Posicao x do mouse no widget
 * @param mouseY Posicao y do mouse no widget
 * @param posX Retorno da posição x do mouse no mapa
 * @param posY Retorno da posição y do mouse no mapa
 *
 */

void Mapa_mousePosicao(GtkWidget *widget, double mouseX, double mouseY, double *posX, double *posY) {
  double mx,my;

  int w=widget->allocation.width;
  int h=widget->allocation.height;

  Mapa_calcularVisaoMaximo(w, h, &mx, &my);

  *posX=mapa.visaoMinimo.x+mouseX*((mx-mapa.visaoMinimo.x)/w);
  *posY=mapa.visaoMinimo.y+(h-mouseY)*((my-mapa.visaoMinimo.y)/h);
}
