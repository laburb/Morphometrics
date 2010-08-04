/*
 * interface.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "Header/interface.h"

#define INTERFACE_CAMINHO "Interface/"
#define INTERFACE_PRINCIPAL "principal.glade"

void Interface_iniciar() {
  GtkWidget *drawOpengl;
  GtkWidget *window;
  GdkGLConfig *glconfig;

  gtk_init(NULL, NULL);
  gtk_gl_init(NULL, NULL);


  builderPrincipal=Interface_carregarXML(INTERFACE_PRINCIPAL);
  window = GTK_WIDGET(gtk_builder_get_object (builderPrincipal, "window"));
  drawOpengl=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "drawOpengl"));

  gtk_adjustment_set_value(GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollHorizGL")),500);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollVertGL")),500);

  //Configura widget para opengl
  glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB    |
                                        GDK_GL_MODE_DEPTH  |
                                        GDK_GL_MODE_DOUBLE);

  if (!glconfig) {
      g_print ("*** Cannot find the double-buffered visual.\n");
      g_print ("*** Trying single-buffered visual.\n");

      /* Try single-buffered visual */
      glconfig = gdk_gl_config_new_by_mode (GDK_GL_MODE_RGB  | GDK_GL_MODE_DEPTH);
      if (!glconfig) {
          g_print ("*** No appropriate OpenGL-capable visual found.\n");
          g_assert_not_reached();
        }
    }


  if (!gtk_widget_set_gl_capability(drawOpengl, glconfig, NULL, TRUE, GDK_GL_RGBA_TYPE))
    g_assert_not_reached();

  gtk_builder_connect_signals(builderPrincipal, NULL);
  gtk_widget_show(window);
}

void Interface_finalizar() {
  g_object_unref(G_OBJECT(builderPrincipal));
}

GtkBuilder *Interface_carregarXML(char *arquivo) {
  char local[256];
  GtkBuilder *builder;

  strcpy(local,INTERFACE_CAMINHO);
  strcat(local,arquivo);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, local, NULL);


  return builder;
}


void Interface_mudarMouse(GdkWindow *windowT, GdkCursorType tipoMouse) {
  //GdkWindow *windowT=gtk_widget_get_window(GTK_WIDGET(builderPrincipal));

  GdkCursor *cur=gdk_cursor_new(tipoMouse);
  gdk_window_set_cursor(windowT, cur );
  gdk_cursor_unref(cur);
}