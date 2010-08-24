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

void Classificacao(ArrayValor *valores) {
  int *kclass;
  double *data;
  int numData,i,classe=0;
  int numClassTmp=numClass;
  Grafo *grafo=mapa.grafo;
  Nodo *nodo;

  //conta quantos elemento possui em valores
  for (numData=0; valores[numData].id != -1 ;numData++);

  data=malloc(numData*sizeof(double));

  for (i=0; i<numData ;i++)
    data[i]=valores[i].valor;

  if (numClassTmp > numData)
    numClassTmp=numData;

  if (classificaoAtiva == CLASS_NATURALBREAKS)
    kclass=NaturalBreaks(data, numData, numClassTmp);

  for (i=0; i<numData ;i++) {
    while (valores[i].valor > data[kclass[classe]])
      classe++;

    nodo=Grafo_getNodo(grafo, valores[i].id);

    if (!nodo) {
      Mensagem(MENSAGEM_ERRO, "Erro", "Erro ao classificar, o mapa atual não corresponde aos resultados.");

      break;
    }

    nodo->cor.r=cores[classe].r;
    nodo->cor.g=cores[classe].g;
    nodo->cor.b=cores[classe].b;
  }

  free(kclass);
  free(data);
}
