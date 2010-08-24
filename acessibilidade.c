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
 * acessibilidade.c
 *
 *  Created on: 16/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <float.h>

#include "Header/grafo.h"
#include "Header/dijkstra.h"
#include "Header/interface.h"
#include "Header/mapa.h"
#include "Header/math2.h"
#include "Header/util.h"
#include "Header/projeto.h"
#include "Header/acessibilidade.h"

void Acessibilidade_calcular(enum TipoAcessibilidade tipoAcess) {
  DijksDados *dijksDados;
  long int total=mapa.grafo->tamanho;
  long int cont=0;
  long int ant=-1;
  int i;

  double custo;

  if (!Projeto_zeraAcessibilidade(tipoAcess))
    return;

  if (!Projeto_iniciarTransacao())
    return;

  gtk_widget_show(frameProgresso);

  forList(Nodo *, nodoPerc, mapa.grafo->nodos) {
    dijksDados=dijkstra(mapa.grafo, nodoPerc->id, tipoAcess);

    custo=0;

    //g_print("ID: %d\n",nodoPerc->id);
    for (i=0; i<mapa.grafo->tamanho ;i++) {
      if (dijksDados[i].custo != DBL_MAX) {
        if ((tipoAcess == ACESS_GEOMETRICA) && (dijksDados[i].geometrico != 0))
          custo+=2/dijksDados[i].geometrico;
        else if ((tipoAcess == ACESS_TOPOLOGICA) && (dijksDados[i].topologico != 0))
          custo+=1.0/dijksDados[i].topologico;
      }
    }

    if (!Projeto_addAcessibilidade(tipoAcess, nodoPerc->id, custo))
      break;

    /*forList(Nodo *, nodoPerc2, mapa.grafo->nodos) {
      if ((nodoPerc2->id == nodoPerc->id) || (dijksDados[nodoPerc2->id -1].custo == INT_MAX))
        continue;

      printf("%d :",nodoPerc2->id);
      dijkstraPrintCam(dijksDados, dijksDados[nodoPerc2->id -1].nodo);
      printf("%d T %d\n",nodoPerc2->id,dijksDados[nodoPerc2->id -1].topologico);
    }*/

    free(dijksDados);
    if (ant < cont*100/total) {
      gtk_progress_bar_set_fraction(progress,((double)(cont))/total);

      while(gtk_events_pending())
          gtk_main_iteration();

      ant=cont*100/total;
    }
    cont++;
  }

  if (!Projeto_terminarTransacao())
      return;

  gtk_widget_hide(frameProgresso);
}
