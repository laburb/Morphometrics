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

static GLfloat rtri, rquad;

/**
 *  Incializa o opengl
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_iniciar(int cx, int cy) {
  GLdouble dx, dy, dX, dY, xM, yM;

  if ( cx <= 0 || cy <= 0 )
    return;

  dx = mapa.limiteMaximo.x - mapa.limiteMinimo.x;
  dy = mapa.limiteMaximo.y - mapa.limiteMinimo.y;

  // select the full client area
  glViewport(0, 0, cx, cy);

  /* change to the projection matrix and set our viewing volume. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Now that the dimensions are set up, we can set up the projection
  // matrix. Since we've overridden OnSize(), we need to do it ourselves

  // select the viewing volume
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (fabs(dx) > 0.001 || fabs(dy) > 0.001)
  {
   if (dx < dy)
   {
    dY = dx * cx / cy;
    yM = mapa.limiteMinimo.y  + dY;

    glOrtho(mapa.limiteMinimo.x, mapa.limiteMaximo.x, mapa.limiteMinimo.y, yM, -100, 100);
   }
   else
   {
    dX = dy * cx / cy;
    xM = mapa.limiteMinimo.x + dX;

    glOrtho(mapa.limiteMinimo.x, xM, mapa.limiteMinimo.y, mapa.limiteMaximo.y, -100, 100);
   }
  }

  // switch back to the modelview matrix and clear it
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

}

/**
 *  Função chamada quando a tela é redimencionada
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_redimencionar(int w, int h) {
  GLdouble dx, dy;
  dx = mapa.limiteMaximo.x - mapa.limiteMinimo.x;
  dy = mapa.limiteMaximo.y - mapa.limiteMinimo.y;

  glViewport(0, 0, dx, dy);
}

void DrawLine(float x1, float y1, float x2, float y2) {
 glColor3ub(255, 255, 255);
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

void Opengl_atualizar() {

}
