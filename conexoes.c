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
 * conexoes.c
 *
 *  Created on: 13/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/math2.h"
#include "Header/util.h"
#include "Header/interface.h"
#include "Header/projeto.h"
#include "Header/conexoes.h"

/**
 * Cria conexão entre os eixos que possuem interseccao.
 */

void Conexoes_verificar() {
  int total=mapa.grafo->tamanho*2;
  int cont=0, conectividade;
  int ant=-1;

  if (!Projeto_zeraConectividade())
    return;

  gtk_widget_show(frameProgresso);

  forList(Nodo *, nodoPerc, mapa.grafo->nodos) {
    forList(Nodo *, nodoPerc2, nodoPercPercorre) {

      if (nodoPerc->id == nodoPerc2->id)
        continue;

      if (Math2_interseccao(nodoPerc, nodoPerc2))
        Grafo_adicionarAresta(mapa.grafo, nodoPerc, nodoPerc2, BIDIRECIONADA, 10);

      if (ant < cont*100/total) {
        gtk_progress_bar_set_fraction(progress,((double)(cont))/total);

        while(gtk_events_pending())
            gtk_main_iteration();

        ant=cont*100/total;
      }
    }
    cont++;
  }

  Arestas *perc;

  if (!Projeto_iniciarTransacao())
    return;

  forList(Nodo *, nodoPerc3, mapa.grafo->nodos) {
    perc=nodoPerc3->arestas;
    conectividade=0;
    while (perc != NULL) {
      conectividade++;
      perc=perc->prox;
    }

    if (!Projeto_addConectividade(nodoPerc3->id, conectividade))
      break;

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
