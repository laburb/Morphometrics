/*
 * sinais.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "Header/opengl.h"
#include "Header/sinais.h"
#include "Header/interface.h"

int timeID=0;

G_MODULE_EXPORT void on_window_destroy(GtkObject *object, gpointer user_data) {
  if (timeID) {
    g_source_remove(timeID);
    timeID=0;
  }

  while (gtk_events_pending())
    gtk_main_iteration();

  gtk_main_quit();
}

G_MODULE_EXPORT void onClickTeste(GtkObject *object, gpointer user_data) {
  GtkWidget *frame=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "frameFerramentas"));

  if (!GTK_WIDGET_VISIBLE(frame))
    gtk_widget_show(frame);
  else
    gtk_widget_hide(frame);
  //gtk_widget_set_visible(frame, !gtk_widget_get_visible(frame));
}

//-------------------------- Inicio sinais: drawOpengl --------------------------

G_MODULE_EXPORT void on_drawOpengl_realize(GtkWidget *widget, gpointer user_data) {
  GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return;

  Opengl_iniciar(widget->allocation.width, widget->allocation.height);

  gdk_gl_drawable_gl_end(gldrawable);
  /*** OpenGL END ***/
}

G_MODULE_EXPORT gboolean on_drawOpengl_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data) {
  GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return FALSE;

  Opengl_desenha();

  if (gdk_gl_drawable_is_double_buffered(gldrawable))
    gdk_gl_drawable_swap_buffers(gldrawable);
  else
    glFlush();

  gdk_gl_drawable_gl_end(gldrawable);
  /*** OpenGL END ***/

  return FALSE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data) {
  GdkGLContext *glcontext = gtk_widget_get_gl_context(widget);
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (widget);

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return FALSE;

  Opengl_redimencionar(widget->allocation.width, widget->allocation.height);

  gdk_gl_drawable_gl_end(gldrawable);
  /*** OpenGL END ***/

  return FALSE;
}

static gboolean rotate(gpointer user_data) {
  GtkWidget *da = GTK_WIDGET (user_data);

  Opengl_atualizar();

  gdk_window_invalidate_rect (da->window, &da->allocation, FALSE);
  gdk_window_process_updates (da->window, FALSE);

  return TRUE;
}

G_MODULE_EXPORT void on_drawOpengl_map_event(GtkWidget *widget, gpointer data) {
  if (!timeID)
    timeID=g_timeout_add(500 / 60, rotate, widget);
}

G_MODULE_EXPORT void on_drawOpengl_unmap_event(GtkWidget *widget, gpointer data) {
  if (timeID) {
    g_source_remove(timeID);
    timeID=0;
  }
}

G_MODULE_EXPORT gboolean on_drawOpengl_enter_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
  Interface_mudarMouse(gtk_widget_get_window(GTK_WIDGET(widget)), GDK_CROSSHAIR);

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_leave_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
  Interface_mudarMouse(gtk_widget_get_window(GTK_WIDGET(widget)), GDK_ARROW);

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {

  return TRUE;
}

//-------------------------- Fim sinais: drawOpengl --------------------------
