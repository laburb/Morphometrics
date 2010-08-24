/*
 * opengl.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <gtk/gtkgl.h>
#include <string.h>
#include <math.h>

#include "Header/ponto.h"
#include "Header/util.h"
#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/math2.h"
#include "Header/opengl.h"

char openglDesenharAtivo=1;
int telaH, telaW;

GLuint font_list_base;
int font_height;

/**
 * Carrega uma fonte.
 * @param fonte Fonte e tamanho. ex.: "courier 10"
 *
 */

void Opengl_carregarFonte(char * fonte) {
  PangoFontDescription *font_desc;
  PangoFont *font;
  PangoFontMetrics *font_metrics;

  font_list_base = glGenLists(128);
  font_desc = pango_font_description_from_string (fonte);

  font = gdk_gl_font_use_pango_font(font_desc, 0, 128, font_list_base);
  if (font == NULL)
    g_print ("*** Can't load font '%s'\n", fonte);

  font_metrics = pango_font_get_metrics (font, NULL);

  font_height = pango_font_metrics_get_ascent(font_metrics) + pango_font_metrics_get_descent(font_metrics);
  font_height = PANGO_PIXELS(font_height);

  pango_font_description_free (font_desc);
  pango_font_metrics_unref (font_metrics);
}

/**
 * Escreve um texto na tela.
 *
 * @param posX Posição x do texto
 * @param posY Posição y do texto
 * @param mesg Formato do texto
 *
 */

void Opengl_drawTexto(double posX, double posY, char *mesg, ...) {
  char texto[256];
  char *mPont;
  va_list ap;

  va_start(ap, mesg);
    vsprintf(texto, mesg, ap);
  va_end(ap);

  glLoadIdentity();

  glColor3ub(97, 49, 49);
  glRasterPos2d(posX,posY );


  for (mPont=texto; *mPont ;mPont++)
    glCallList (font_list_base+*mPont);
}

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

  telaH=h;
  telaW=w;

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
  /*glEnable( GL_LINE_SMOOTH );
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

  Opengl_configTela(w,h);

  Opengl_carregarFonte("courier 10");
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

static void DrawLine(Cor *cor, double x1, double y1, double x2, double y2) {
  glColor3ub(cor->r, cor->g, cor->b);
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();

  glEnable(GL_TEXTURE_2D);
}

static void DrawArc(Cor *cor, double x, double y, double raio, double inicial, double final) {
  double deltaAngle, anguloInicial, anguloFinal, angulo;
  double tmp;

  tmp=inicial;
  inicial=360-final;
  final=360-tmp;

  deltaAngle=20.0/raio;
  anguloInicial=inicial *(2.0 * M_PI / 360.0);
  anguloFinal=final *(2.0 * M_PI / 360.0);
  if (inicial > final) {
    anguloFinal += (2.0 * M_PI);
  }

  glColor3ub(cor->r, cor->g, cor->b);
  glBegin(GL_LINE_STRIP);
  angulo = anguloInicial;
  while (angulo <= anguloFinal) {
    glVertex2f(x + raio * cos(angulo), y + raio * sin(angulo));

    angulo += deltaAngle;
  }

  if (angulo-deltaAngle < anguloFinal)
    glVertex2f(x + raio * cos(anguloFinal), y + raio * sin(anguloFinal));

  glEnd();
}
/**
 * Verifica se esta dentro da area de visão
 */

static int Opengl_verificaDentroVisao(Nodo *nodo, double mx, double my) {
  double p1x, p1y, p2x, p2y;

  Math2_extremos(nodo, &p1x, &p1y, &p2x, &p2y);

  double pIniX=MIN(p1x, p2x);
  double pFImX=MAX(p1x, p2x);

  double pIniY=MIN(p1y, p2y);
  double pFImY=MAX(p1y, p2y);

  if (mx < pIniX)
    return 0;
  if (mapa.visaoMinimo.x > pFImX)
    return 0;
  if (my < pIniY)
    return 0;
  if (mapa.visaoMinimo.y > pFImY)
    return 0;

  return 1;
}

/**
 *  Desenha
 */

void Opengl_desenha() {
  double mx, my, medioX, medioY;
  Line *line;
  Arc *arc;

  if (!openglDesenharAtivo)
    return;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glLoadIdentity();

  Mapa_calcularVisaoMaximo(telaW, telaH, &mx, &my);

  forList(Nodo *, nodoPerc, mapa.grafo->nodos) {
    if (Opengl_verificaDentroVisao(nodoPerc, mx, my)) {
      if (mapa.exibirLabel) {
        Math2_pontoMedio(nodoPerc, &medioX, &medioY);

        Opengl_drawTexto(medioX, medioY, "%d", nodoPerc->id);
      }

      if (nodoPerc->tipo == ENTIDADE_LINE) {
        line=(Line *) nodoPerc->d;
        DrawLine(&nodoPerc->cor, line->p1.x,line->p1.y,line->p2.x,line->p2.y);
      }
      else if (nodoPerc->tipo == ENTIDADE_ARC) {
        arc=(Arc *) nodoPerc->d;
        DrawArc(&nodoPerc->cor, arc->centro.x, arc->centro.y, arc->raio, arc->anguloInicial, arc->anguloFinal);
      }
    }
  }
}
