/*
 * math2.c
 *
 *  Created on: 13/08/2010
 *      Author: bruno
 */

#include <math.h>

#include "Header/ponto.h"
#include "Header/math2.h"

#undef  MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

static int relativeCCW(double X1, double Y1, double X2, double Y2, double PX, double PY) {
  X2-=X1;
  Y2-=Y1;
  PX-=X1;
  PY-=Y1;
  double ccw=PX * Y2 - PY * X2;
  if (ccw == 0.0) {

    ccw=PX * X2 + PY * Y2;
    if (ccw > 0.0) {
      PX-=X2;
      PY-=Y2;
      ccw=PX * X2 + PY * Y2;
      if (ccw < 0.0) {
        ccw=0.0;
      }
    }
  }

  return (ccw < 0.0) ? -1 : ((ccw > 0.0) ? 1 : 0);
}

/**
 * Verifica se os dois eixos possuem interseccao.
 *
 * @param p1Ini Ponto inicial do eixo 1
 * @param p1Fim Ponto final do eixo 1
 * @param p2Ini Ponto inicial do eixo 2
 * @param p2Fim Ponto inicial do eixo 2
 *
 */

int interseccao(Ponto *p1Ini, Ponto *p1Fim, Ponto *p2Ini, Ponto *p2Fim) {
  static Ponto *antePot=(void *)0;
  static double p1IniX, p1FimX, p2IniX, p2FimX;

  if (antePot != p1Ini) {
    p1IniX=MIN(p1Ini->x,p1Fim->x);
    p1FimX=MAX(p1Ini->x,p1Fim->x);
    p2IniX=MIN(p2Ini->x,p2Fim->x);
    p2FimX=MAX(p2Ini->x,p2Fim->x);

    antePot=p1Ini;
  }

  double p1IniY=MIN(p1Ini->y,p1Fim->y);
  double p1FimY=MAX(p1Ini->y,p1Fim->y);
  double p2IniY=MIN(p2Ini->y,p2Fim->y);
  double p2FimY=MAX(p2Ini->y,p2Fim->y);

  // Verifica se pode ter interseccao
  if (p2FimX < p1IniX)
    return 0;
  if (p2IniX > p1FimX)
    return 0;
  if (p2FimY < p1IniY)
    return 0;
  if (p2IniY > p1FimY)
    return 0;

  //Teste se realmente tem interseccao
  return ((relativeCCW(p1Ini->x, p1Ini->y, p1Fim->x, p1Fim->y, p2Ini->x, p2Ini->y) *
            relativeCCW(p1Ini->x, p1Ini->y, p1Fim->x, p1Fim->y, p2Fim->x, p2Fim->y) <= 0)
           && (relativeCCW(p2Ini->x, p2Ini->y, p2Fim->x, p2Fim->y, p1Ini->x, p1Ini->y) *
               relativeCCW(p2Ini->x, p2Ini->y, p2Fim->x, p2Fim->y, p1Fim->x, p1Fim->y) <= 0));
}


/**
 * Retorna o ponto medio do eixo.
 *
 * @param ptIni Ponto inicial do eixo
 * @param ptFim Ponto final do eixo
 * @param medioX Ponteiro para o retorno do resultado
 * @param medioY Ponteiro para o retorno do resultado
 *
 */

void pontoMedio(Ponto *ptIni, Ponto *ptFim, double *medioX, double *medioY) {
  *medioX=(ptIni->x + ptFim->x)/2;
  *medioY=(ptIni->y + ptFim->y)/2;
}
