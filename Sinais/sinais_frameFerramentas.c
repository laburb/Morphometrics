/*
 * sinais_frameFerramentas.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "../Header/interface.h"
#include "../Header/editar.h"

static void desmarcar() {
  GtkToggleToolButton *tbAddEntidade=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddEntidade"));
  GtkToggleToolButton *tbAddImagem=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddImagem"));
  GtkToggleToolButton *tbAddTexto=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddTexto"));
  GtkToggleToolButton *tbAmpliar=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAmpliar"));
  GtkToggleToolButton *tbReduzir=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbReduzir"));

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
