/*
 * sinais_toolbar.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "../Header/grafo.h"
#include "../Header/mapa.h"
#include "../Header/interface.h"

G_MODULE_EXPORT void on_tbEditar_toggled(GtkObject *object, gpointer user_data) {
  if (!GTK_WIDGET_VISIBLE(frameFerramentas))
    gtk_widget_show(frameFerramentas);
  else
    gtk_widget_hide(frameFerramentas);
  //gtk_widget_set_visible(frame, !gtk_widget_get_visible(frame));
}
