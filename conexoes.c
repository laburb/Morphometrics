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
#include "Header/conexoes.h"

/**
 * Cria conexão entre os eixos que possuem interseccao.
 */

void Conexoes_verificar() {
  long int total=mapa.grafo->tamanho;
  long int cont=0;
  long int ant=-1;

  GtkWidget *frameProgresso=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "frameProgresso"));
  GtkProgressBar *progress=GTK_PROGRESS_BAR(gtk_builder_get_object(builderPrincipal, "progressbar"));
  gtk_widget_show(frameProgresso);

  forList(Nodo *, nodoPerc, mapa.grafo->nodos) {
    forList(Nodo *, nodoPerc2, nodoPercPercorre) {

      if (nodoPerc->valor == nodoPerc2->valor)
        continue;

      if (interseccao(&nodoPerc->p1, &nodoPerc->p2, &nodoPerc2->p1, &nodoPerc2->p2))
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

  gtk_widget_hide(frameProgresso);

}
