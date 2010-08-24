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
