/*
 * importDFX.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <stdlib.h>

#include "../Header/util.h"
#include "../Header/grafo.h"
#include "../Header/ponto.h"
#include "../Header/mapa.h"
#include "Header/importDFX.h"

/**
  *  @brief Função que importa arquivo no formato DFX
  *
  *  @param arquivo String referente ao comando.
  *
  *  @return Sucesso na importação
  *
  *  @retval 1 Sucesso
  *  @retval 0 Falha
  *
  */

int importDFX(char *arquivo) {
  FILE *fp;
  double x1,x2,y1,y2;

  grafo=Grafo_iniciar();

  fp=fopen(arquivo, "r");
  if (!fp)
    return 0;

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

  while (Arquivo_acharString(fp, "AcDbLine", 0)) {
    Nodo *nodoAtual=Grafo_adicionarNodo(grafo);

    Arquivo_acharString(fp, "10", 0);
    fscanf(fp,"%lf",&x1);
    nodoAtual->p1.x=x1;

    Arquivo_acharString(fp, "20", 0);
    fscanf(fp,"%lf",&y1);
    nodoAtual->p1.y=y1;

    Arquivo_acharString(fp, "11", 0);
    fscanf(fp,"%lf",&x2);
    nodoAtual->p2.x=x2;

    Arquivo_acharString(fp, "21", 0);
    fscanf(fp,"%lf",&y2);
    nodoAtual->p2.y=y2;

    printf("Carregando entidade: %lf %lf %lf %lf\n",x1,y1,x2,y2);
  }

  return 1;
}
