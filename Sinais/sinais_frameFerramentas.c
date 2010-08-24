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
 * sinais_frameFerramentas.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "../Header/interface.h"
#include "../Header/mapa.h"
#include "../Header/editar.h"

static void desmarcar() {
  if (ferramentaAtiva != FERRAMENTA_ADD_ENTIDADE) gtk_toggle_tool_button_set_active(tbAddEntidade, FALSE);
  if (ferramentaAtiva != FERRAMENTA_ADD_IMAGEM) gtk_toggle_tool_button_set_active(tbAddImagem, FALSE);
  if (ferramentaAtiva != FERRAMENTA_ADD_TEXTO) gtk_toggle_tool_button_set_active(tbAddTexto, FALSE);
  if (ferramentaAtiva != FERRAMENTA_ZOOM_MAIS) gtk_toggle_tool_button_set_active(tbAmpliar, FALSE);
  if (ferramentaAtiva != FERRAMENTA_ZOOM_MENOS) gtk_toggle_tool_button_set_active(tbReduzir, FALSE);
}

static int itemClick=0;

G_MODULE_EXPORT void on_tbAddEntidade_toggled(GtkObject *object, gpointer user_data) {
  if (itemClick)
    return;

  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  itemClick=1;
  if (estado) {
    ferramentaAtiva=FERRAMENTA_ADD_ENTIDADE;
    desmarcar();
  }
  else
    ferramentaAtiva=FERRAMENTA_NAVEGAR;

  itemClick=0;
}

G_MODULE_EXPORT void on_tbAddImagem_toggled(GtkObject *object, gpointer user_data) {
  if (itemClick)
      return;
  itemClick=2;

  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  if (estado) {
    ferramentaAtiva=FERRAMENTA_ADD_IMAGEM;
    desmarcar();
  }
  else
    ferramentaAtiva=FERRAMENTA_NAVEGAR;

  itemClick=0;
}

G_MODULE_EXPORT void on_tbAddTexto_toggled(GtkObject *object, gpointer user_data) {
  if (itemClick)
      return;
  itemClick=3;

  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  if (estado) {
    ferramentaAtiva=FERRAMENTA_ADD_TEXTO;
    desmarcar();
  }
  else
    ferramentaAtiva=FERRAMENTA_NAVEGAR;

  itemClick=0;
}

G_MODULE_EXPORT void on_tbAmpliar_toggled(GtkObject *object, gpointer user_data) {
  if (itemClick)
      return;
  itemClick=4;

  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  if (estado) {
    ferramentaAtiva=FERRAMENTA_ZOOM_MAIS;
    desmarcar();
  }
  else
    ferramentaAtiva=FERRAMENTA_NAVEGAR;

  itemClick=0;
}

G_MODULE_EXPORT void on_tbReduzir_toggled(GtkObject *object, gpointer user_data) {
  if (itemClick)
      return;
  itemClick=5;

  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  if (estado) {
    ferramentaAtiva=FERRAMENTA_ZOOM_MENOS;
    desmarcar();
  }
  else
    ferramentaAtiva=FERRAMENTA_NAVEGAR;

  itemClick=0;
}

G_MODULE_EXPORT void on_tbMelhorAjuste_clicked(GtkObject *object, gpointer user_data) {
  Editar_melhorVisao();
}

G_MODULE_EXPORT void on_tbExibirLabel_toggled(GtkObject *object, gpointer user_data) {
  gboolean estado=gtk_toggle_tool_button_get_active(GTK_TOGGLE_TOOL_BUTTON(object));

  mapa.exibirLabel=estado;
  Interface_atualizaOpengl();
}
