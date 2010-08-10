/*
 * opengl.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

#include "Header/ponto.h"
#include "Header/mapa.h"
#include "Header/util.h"
#include "Header/grafo.h"
#include "Header/opengl.h"

/**
 *  Reconfigura a vião do OpenGL
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_configTela(int w, int h) {
  GLdouble dx, dy, mx, my;

  if ( w <= 0 || h <= 0 )
    return;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  dx = mapa.visaoMaximo.x - mapa.visaoMinimo.x;
  dy = mapa.visaoMaximo.y - mapa.visaoMinimo.y;


  mx=mapa.visaoMaximo.x;
  my=mapa.visaoMaximo.y;

  if (dx < dy)
    my=mapa.visaoMinimo.y + dx*h/w;
  else
    mx=mapa.visaoMinimo.x + dy*w/h;

  glOrtho(mapa.visaoMinimo.x, mx, mapa.visaoMinimo.y, my, -100, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

/**
 *  Incializa o opengl
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_iniciar(int w, int h) {
  glClearColor( 0.72f, 0.72f, 0.72f, 0.0f );
  glEnable( GL_LINE_SMOOTH );
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Opengl_configTela(w,h);
}

/**
 *  Função chamada quando a tela é redimencionada
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_redimencionar(int w, int h) {
  Opengl_configTela(w,h);

}

static void DrawLine(float x1, float y1, float x2, float y2) {
 glColor3ub(0, 0, 0);
 glDisable(GL_TEXTURE_2D);

 glBegin(GL_LINES);
  glVertex2f(x1-100, y1-100);
  glVertex2f(x2-100, y2-100);
 glEnd();
}


/**
 *  Desenha
 */

void Opengl_desenha() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();

  forList(Nodo *, nodoPerc, grafo->nodos) {
    DrawLine(nodoPerc->p1.x,nodoPerc->p1.y,nodoPerc->p2.x,nodoPerc->p2.y);
  }
}
