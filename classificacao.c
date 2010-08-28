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
 * classificacao.c
 *
 *  Created on: 24/08/2010
 *      Author: bruno
 */

#include <stdlib.h>

#include "Classificacoes/Header/naturalbreaks.h"
#include "Header/projeto.h"
#include "Header/mapa.h"
#include "Header/mensagens.h"
#include "Header/classificacao.h"

enum ClassificaoTipo classificaoAtiva=CLASS_NATURALBREAKS;
int numClass=5;
Cor cores[5]={
    {132,76,209},
    {163,56,157},
    {193,38,104},
    {224,19,53},
    {255,0,0}
};
Cor corPadrao={0,0,0};

int espessuraMin=1;
int espessuraMax=10;

void Classificacao(ArrayValor *valores) {
  int *classCor=NULL;
  int *classEspessura=NULL;
  double *data;
  int numData,i;
  int classePerCor=0,classePerEspes=0;
  int numClassCor=numClass;
  int numClassEspessura=espessuraMax-espessuraMin;
  Grafo *grafo=mapa.grafo;
  Nodo *nodo;

  //conta quantos elemento possui em valores
  for (numData=0; valores[numData].id != -1 ;numData++);

  data=malloc(numData*sizeof(double));

  for (i=0; i<numData ;i++)
    data[i]=valores[i].valor;

  if (numClassCor > numData)
    numClassCor=numData;

  if (numClassEspessura > numData)
    numClassEspessura=numData;

  if (classificaoAtiva == CLASS_NATURALBREAKS) {
    classCor=NaturalBreaks(data, numData, numClassCor);

    if (numClassEspessura)
      classEspessura=NaturalBreaks(data, numData, numClassEspessura);
  }

  for (i=0; i<numData ;i++) {
    while (valores[i].valor > data[classCor[classePerCor]])
      classePerCor++;

    if (numClassEspessura) {
      while (valores[i].valor > data[classEspessura[classePerEspes]])
        classePerEspes++;
    }

    nodo=Grafo_getNodo(grafo, valores[i].id);

    if (!nodo) {
      Mensagem(MENSAGEM_ERRO, "Erro", "Erro ao classificar, o mapa atual não corresponde aos resultados.");

      break;
    }

    nodo->cor=classePerCor;
    nodo->espessura=espessuraMin+classePerEspes;
  }

  free(classCor);
  if (classEspessura)
    free(classEspessura);

  free(data);
}
