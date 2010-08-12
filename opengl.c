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
#include "Header/util.h"
#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/opengl.h"

char openglDesenharAtivo=1;

/**
 *  Reconfigura a vião do OpenGL
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_configTela(int w, int h) {
  GLdouble mx, my;

  if ( w <= 0 || h <= 0 )
    return;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  Mapa_calcularVisaoMaximo(w, h, &mx, &my);

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

/**
 * Desenha uma linha usando a operação XOR
 */

void DrawLineXOR(double x1, double y1, double x2, double y2) {
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_XOR);

  glColor3ub(255, 255, 255);
  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();

  glDisable(GL_COLOR_LOGIC_OP);
}

/**
 * Desenha um quadrado usando a operação XOR
 */

void DrawQuadradoXOR(double x1, double y1, double x2, double y2) {
  glEnable(GL_LINE_STIPPLE);
  glLineStipple(1, 0x00FF);

  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_XOR);

  glColor3ub(255, 255, 255);

  glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
  glEnd();

  glDisable(GL_COLOR_LOGIC_OP);
  glDisable(GL_LINE_STIPPLE);
}

static void DrawLine(double x1, double y1, double x2, double y2) {
  glColor3ub(0, 0, 0);
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();

  glEnable(GL_TEXTURE_2D);
}

/**
 *  Desenha
 */

void Opengl_desenha() {
  if (!openglDesenharAtivo)
    return;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();

  forList(Nodo *, nodoPerc, mapa.grafo->nodos)
    DrawLine(nodoPerc->p1.x,nodoPerc->p1.y,nodoPerc->p2.x,nodoPerc->p2.y);
}
