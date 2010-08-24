/*
 * math2.c
 *
 *  Created on: 13/08/2010
 *      Author: bruno
 */

#include <math.h>

#include "Header/grafo.h"
#include "Header/ponto.h"
#include "Header/math2.h"

#undef  MAX
#define MAX(a, b)  (((a) > (b)) ? (a) : (b))

#undef  MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))

#define ZERO_TOLERANCE 1e-06f

//Verifica em que posição o ponto (Px,PY) esta em relação a reta.
//Retirado de java.awt.geom.Line2D
static int relativeCCW(double X1, double Y1, double X2, double Y2, double PX, double PY) {
  X2-=X1;
  Y2-=Y1;
  PX-=X1;
  PY-=Y1;

  double ccw=PX * Y2 - PY * X2;

  // The point is colinear, classify based on which side of
  // the segment the point falls on. We can calculate a
  // relative value using the projection of PX,PY onto the
  // segment - a negative value indicates the point projects
  // outside of the segment in the direction of the particular
  // endpoint used as the origin for the projection.
  if (ccw == 0.0) {
    // Reverse the projection to be relative to the original X2,Y2
    // X2 and Y2 are simply negated.
    // PX and PY need to have (X2 - X1) or (Y2 - Y1) subtracted
    // from them (based on the original values)
    // Since we really want to get a positive answer when the
    // point is "beyond (X2,Y2)", then we want to calculate
    // the inverse anyway - thus we leave X2 & Y2 negated.

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

int Math2_interseccao(Nodo *nodo1, Nodo *nodo2) {
  if ((nodo1->tipo == ENTIDADE_LINE) && (nodo2->tipo == ENTIDADE_LINE)) {
    Line *l1=(Line *) nodo1->d;
    Line *l2=(Line *) nodo2->d;

    return Math2_intrSegmentoRetas(&l1->p1, &l1->p2, &l2->p1, &l2->p2);
  }
  if ((nodo1->tipo == ENTIDADE_ARC) && (nodo2->tipo == ENTIDADE_LINE)) {
    Arc *arco=(Arc *) nodo1->d;
    Line *linha=(Line *) nodo2->d;

    return Math2_intrSegmentoRetaCirculo(linha, &arco->centro, arco->raio);
    return Math2_intrSegmentoRetaArco(linha, arco);
  }
  if ((nodo1->tipo == ENTIDADE_LINE) && (nodo2->tipo == ENTIDADE_ARC)) {
    Line *linha=(Line *) nodo1->d;
    Arc *arco=(Arc *) nodo2->d;
    return Math2_intrSegmentoRetaCirculo(linha, &arco->centro, arco->raio);
    return Math2_intrSegmentoRetaArco(linha, arco);
  }
  return 0;
}

/**
 * Verifica se os dois eixos possuem intersecção.
 *
 * @param p1Ini Ponto inicial do eixo 1
 * @param p1Fim Ponto final do eixo 1
 * @param p2Ini Ponto inicial do eixo 2
 * @param p2Fim Ponto inicial do eixo 2
 *
 */

int Math2_intrSegmentoRetas(Ponto *p1Ini, Ponto *p1Fim, Ponto *p2Ini, Ponto *p2Fim) {
  double p1IniX=MIN(p1Ini->x,p1Fim->x);
  double p1FimX=MAX(p1Ini->x,p1Fim->x);
  double p2IniX=MIN(p2Ini->x,p2Fim->x);
  double p2FimX=MAX(p2Ini->x,p2Fim->x);

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
  //Retirado de java.awt.geom.Line2D
  return ((relativeCCW(p1Ini->x, p1Ini->y, p1Fim->x, p1Fim->y, p2Ini->x, p2Ini->y) *
            relativeCCW(p1Ini->x, p1Ini->y, p1Fim->x, p1Fim->y, p2Fim->x, p2Fim->y) <= 0)
           && (relativeCCW(p2Ini->x, p2Ini->y, p2Fim->x, p2Fim->y, p1Ini->x, p1Ini->y) *
               relativeCCW(p2Ini->x, p2Ini->y, p2Fim->x, p2Fim->y, p1Fim->x, p1Fim->y) <= 0));
}

int Math2_intrLinhaCirculo(Ponto *origem, Ponto *direcao, Ponto *centro, double raio, int *quantidade, double t[2]) {
  Ponto diff;

  diff.x=origem->x-centro->x;
  diff.y=origem->y-centro->y;

  double a0 = diff.x*diff.x+ diff.y+diff.y-raio*raio;
  double a1 = direcao->x*diff.x + direcao->y*diff.y;
  double discr = a1*a1 - a0;

  if (discr > ZERO_TOLERANCE) {
      *quantidade = 2;
      discr = sqrt(discr);
      t[0] = -a1 - discr;
      t[1] = -a1 + discr;
  }
  else if (discr < -ZERO_TOLERANCE)
      *quantidade = 0;
  else { // discr == 0
      *quantidade = 1;
      t[0] = -a1;
  }

  return (*quantidade != 0);
}

int Math2_ArcoContemPonto(Arc *arco, Ponto *ponto) {
  Ponto diffPE0, diffE1E0;
  diffPE0.x = ponto->x - 170.835;
  diffPE0.y = ponto->y - 340.021;
  diffE1E0.x = 279.1571 - 170.835;
  diffE1E0.y = 199.3545 - 340.021;

  double dotPerp = diffPE0.x*diffE1E0.y - diffPE0.y*diffE1E0.x;
  return dotPerp >= 0.0f;

  return 1;
}

double Math2_produtoEscalar(Ponto p1, Ponto p2) {
  return p1.x*p2.x+p1.y*p2.y;
}

int Math2_intrSegmentoRetaCirculo(Line *linha, Ponto *centro, double raio) {
  Ponto dir=Ponto_menos(linha->p2, linha->p1);
  Ponto diff=Ponto_menos(*centro, linha->p1);

  double t = Math2_produtoEscalar(diff,dir) / Math2_produtoEscalar(dir,dir);
  if (t < 0.0f)
      t = 0.0f;
  if (t > 1.0f)
      t = 1.0f;

  Ponto_vezes(&dir, t);

  Ponto closest = Ponto_mais(linha->p1,dir);
  Ponto d = Ponto_menos(*centro, closest);
  double distsqr = Math2_produtoEscalar(d,d);

  return distsqr <= raio * raio;
}

int Math2_intrSegmentoRetaArco(Line *linha, Arc *arco) {
  Ponto centro, direcao, mPoint[2];
  double t[2], extent;
  int quantidade, interseccoes,i;

  Math2_pontoMedioSegmentoReta(&linha->p1, &linha->p2, &centro.x, &centro.y);

  direcao.x=linha->p1.x-linha->p2.x;
  direcao.y=linha->p1.y-linha->p2.y;

  double length = sqrt(direcao.x*direcao.x + direcao.y+direcao.y);

  if (length > ZERO_TOLERANCE) {
    float invLength = 1.0f/length;
    direcao.x *= invLength;
    direcao.y *= invLength;
  }
  else {
    length = 0.0f;
    direcao.x = 0.0f;
    direcao.y = 0.0f;
  }

  extent=0.5*length;

  interseccoes=Math2_intrLinhaCirculo(&centro, &direcao, &arco->centro, arco->raio, &quantidade, t);

  int mQuantity=0;
  if (interseccoes) {
         // Reduce root count if line-circle intersections are not on segment.
         if (quantidade == 1) {
             if (fabs(t[0]) > extent) {
               quantidade = 0;
             }
         }
         else {
             if (t[1] < -extent || t[0] > extent)
               quantidade = 0;
             else {
                 if (t[1] <= extent) {
                     if (t[0] < -extent) {
                       quantidade = 1;
                         t[0] = t[1];
                     }
                 }
                 else
                   quantidade = (t[0] >= -extent ? 1 : 0);
             }
         }

         Ponto point;
         for (i=0; i < quantidade; i++) {
             point.x=centro.x + direcao.x*t[i];
             point.y=centro.y + direcao.y*t[i];
printf("%lf %lf\n",point.x,point.y);
             if (Math2_ArcoContemPonto(arco, &point)) {
               mQuantity++;
                 //mPoint[mQuantity++] = point;
             }
         }
     }

     //mIntersectionType = (mQuantity > 0 ? IT_POINT : IT_EMPTY);
     return (mQuantity > 0);

}
/**
 * Retorna o ponto medio da entidade.
 *
 * @param nodo Nodo
 * @param medioX Ponteiro para o retorno do resultado
 * @param medioY Ponteiro para o retorno do resultado
 *
 */

void Math2_pontoMedio(Nodo *nodo, double *medioX, double *medioY) {
  if (nodo->tipo == ENTIDADE_LINE) {
    Line *line=(Line *) nodo->d;
    Math2_pontoMedioSegmentoReta(&line->p1, &line->p2, medioX, medioY);
  }
  else if (nodo->tipo == ENTIDADE_ARC) {
    Arc *arc=(Arc *) nodo->d;
    *medioX=arc->centro.x;
    *medioY=arc->centro.y;
  }
}

void Math2_pontoMedioSegmentoReta(Ponto *p1, Ponto *p2, double *medioX, double *medioY) {
  *medioX=(p1->x + p2->x)/2;
  *medioY=(p1->y + p2->y)/2;
}


double Math2_comprimento(Nodo *nodo) {
  if (nodo->tipo == ENTIDADE_LINE) {
    Line *line=(Line *) nodo->d;

    return Math2_distanciaPontos(&line->p1, &line->p2);
  }

  if (nodo->tipo == ENTIDADE_ARC) {
    Arc *arc=(Arc *) nodo->d;

    double angFim=arc->anguloFinal;

    if (arc->anguloInicial > arc->anguloFinal)
      angFim+=360;

    return (arc->raio*M_PI*(angFim-arc->anguloInicial))/180;
  }

  return 0;
}

double Math2_distanciaPontos(Ponto *ptIni, Ponto *ptFim) {
  return sqrt(pow(ptFim->x-ptIni->x,2) + pow(ptFim->y-ptIni->y,2));
}

void Math2_extremos(Nodo *nodo, double *p1x, double *p1y, double *p2x, double *p2y) {
  if (nodo->tipo == ENTIDADE_LINE) {
    Line *line=(Line *) nodo->d;

    *p1x=line->p1.x;
    *p1y=line->p1.y;
    *p2x=line->p2.x;
    *p2y=line->p2.y;
  }
  else if (nodo->tipo == ENTIDADE_ARC) {
    Arc *arc=(Arc *) nodo->d;

    *p1x=arc->centro.x - arc->raio;
    *p1y=arc->centro.y - arc->raio;
    *p2x=arc->centro.x + arc->raio;
    *p2y=arc->centro.y + arc->raio;
  }
}
