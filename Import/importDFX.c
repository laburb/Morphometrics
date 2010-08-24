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
 * importDFX.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header/util.h"
#include "../Header/grafo.h"
#include "../Header/ponto.h"
#include "../Header/mapa.h"
#include "Header/importDFX.h"

//#define DEBUG

static void obterLine(FILE *fp) {
  Nodo *nodoAtual=Grafo_adicionarNodo(mapa.grafo, ENTIDADE_LINE);
  Line *line=(Line *) nodoAtual->d;

  //ignora o id
  fscanf(fp, "%*d %*d");

  Arquivo_acharString(fp, "10", 0);
  fscanf(fp, "%lf", &line->p1.x);

  Arquivo_acharString(fp, "20", 0);
  fscanf(fp, "%lf", &line->p1.y);

  Arquivo_acharString(fp, "11", 0);
  fscanf(fp, "%lf", &line->p2.x);

  Arquivo_acharString(fp, "21", 0);
  fscanf(fp, "%lf", &line->p2.y);
}

static void obterPolyLine(FILE *fp, int versao) {
  Nodo *nodoAtual=NULL;
  Ponto pTmp;
  Ponto pTmpAnt;
  Line *line;

  int ok=0;

  char strTmp[256];

  if (versao < 14)
      Arquivo_acharString(fp, "VERTEX", 0);

  while (fscanf(fp, "%s", strTmp) != EOF) {
    if (!strcmp("AutoCAD", strTmp))
      break;
    if ((ok) && (!strcmp(((versao >= 14)?"0":"SEQEND"), strTmp)))
      break;
    else if (!strcmp("10", strTmp)) {
      fscanf(fp, "%lf", &pTmp.x);

      Arquivo_acharString(fp, "20", 0);
      fscanf(fp, "%lf", &pTmp.y);

      if (ok) {
        nodoAtual=Grafo_adicionarNodo(mapa.grafo, ENTIDADE_LINE);
        line=(Line *) nodoAtual->d;

        line->p1.x=pTmpAnt.x;
        line->p1.y=pTmpAnt.y;
        line->p2.x=pTmp.x;
        line->p2.y=pTmp.y;
      }

      pTmpAnt.x=pTmp.x;
      pTmpAnt.y=pTmp.y;

      ok=1;
    }
  }
}

static void obterArc(FILE *fp) {
  Nodo *nodoAtual=Grafo_adicionarNodo(mapa.grafo, ENTIDADE_ARC);
  Arc *arc=(Arc *) nodoAtual->d;

  //ignora o id
  fscanf(fp, "%*d %*d");

  Arquivo_acharString(fp, "10", 0);
  fscanf(fp, "%lf", &arc->centro.x);

  Arquivo_acharString(fp, "20", 0);
  fscanf(fp, "%lf", &arc->centro.y);

  Arquivo_acharString(fp, "40", 0);
  fscanf(fp, "%lf", &arc->raio);

  Arquivo_acharString(fp, "50", 0);
  fscanf(fp, "%lf", &arc->anguloInicial);

  Arquivo_acharString(fp, "51", 0);
  fscanf(fp, "%lf", &arc->anguloFinal);
}

/**
  *  Função que importa arquivo no formato DFX
  *
  *  @param arquivo String referente ao comando.
  *
  *  @return Sucesso na importação
  *
  *  @retval 1 Sucesso
  *  @retval 0 Falha
  *  @retval -1 Versão não suportada
  *
  */

int importDFX(char *arquivo) {
  FILE *fp;
  char strTmp[256];
  int versao=-1;

  if (mapa.grafo)
    Grafo_deletar(&mapa.grafo);

  mapa.grafo=Grafo_iniciar();

  fp=fopen(arquivo, "r");
  if (!fp)
    return 0;

  if (Arquivo_acharString(fp, "AC1009", 1))
    versao=12;
  else if (Arquivo_acharString(fp, "AC1012", 1))
    versao=13;
  else if (Arquivo_acharString(fp, "AC1014", 1))
    versao=14;
  else if (Arquivo_acharString(fp, "AC1015", 1))
    versao=2000;
  else if (Arquivo_acharString(fp, "AC1018", 1))
    versao=2004;
  else if (Arquivo_acharString(fp, "AC1021", 1))
    versao=2007;

  if (versao == -1)
    return -1;

  if (!Arquivo_acharString(fp, "$EXTMIN", 1))
    return 0;

  fscanf(fp,"%*d %lf",&mapa.eixoMinimo.x);
  fscanf(fp,"%*d %lf",&mapa.eixoMinimo.y);

  if (!Arquivo_acharString(fp, "$EXTMAX", 0))
    return 0;

  fscanf(fp,"%*d %lf",&mapa.eixoMaximo.x);
  fscanf(fp,"%*d %lf",&mapa.eixoMaximo.y);

  if (!Arquivo_acharString(fp, "$LIMMIN", 0))
    return 0;

  fscanf(fp,"%*d %lf",&mapa.limiteMinimo.x);
  fscanf(fp,"%*d %lf",&mapa.limiteMinimo.y);

  if (!Arquivo_acharString(fp, "$LIMMAX", 0))
    return 0;

  fscanf(fp,"%*d %lf",&mapa.limiteMaximo.x);
  fscanf(fp,"%*d %lf",&mapa.limiteMaximo.y);

#ifdef DEBUG
  printf("eixoMinimo: %lf %lf eixoMaximo: %lf %lf\n", mapa.eixoMinimo.x,mapa.eixoMinimo.y, mapa.eixoMaximo.x,mapa.eixoMaximo.y);
  printf("limiteMinimo: %lf %lf limiteMaximo: %lf %lf\n", mapa.limiteMinimo.x,mapa.limiteMinimo.y, mapa.limiteMaximo.x,mapa.limiteMaximo.y);
#endif

  while (fscanf(fp, "%s",strTmp) != EOF) {
    if (!strcmp("LINE",strTmp))
      obterLine(fp);
    else if ((!strcmp("AcDbPolyline",strTmp)) || (!strcmp("POLYLINE",strTmp)))
      obterPolyLine(fp,versao);
    else if (!strcmp("ARC",strTmp))
      obterArc(fp);
  }

  Mapa_calculaEixoMax();
  Mapa_setVisao(mapa.eixoMinimo,mapa.eixoMaximo);

  return 1;
}
