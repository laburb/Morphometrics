/*
 * sinais_geral.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

G_MODULE_EXPORT void on_window_destroy(GtkObject *object, gpointer user_data) {
  while (gtk_events_pending())
    gtk_main_iteration();

  gtk_main_quit();
}
