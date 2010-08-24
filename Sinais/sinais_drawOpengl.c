/*
 * sinais_drawOpengl.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "../Header/grafo.h"
#include "../Header/mapa.h"
#include "../Header/opengl.h"
#include "../Header/interface.h"
#include "../Header/editar.h"

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
  GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable(widget);

  /*** OpenGL BEGIN ***/
  if (!gdk_gl_drawable_gl_begin(gldrawable, glcontext))
    return FALSE;

  Opengl_redimencionar(widget->allocation.width, widget->allocation.height);

  gdk_gl_drawable_gl_end(gldrawable);
  /*** OpenGL END ***/

  return FALSE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_enter_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {

  Interface_mudarMouse(Mapa_cursor());

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_leave_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
  Interface_mudarMouse(GDK_ARROW);

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data) {
  double mouseX,mouseY;
  char str[256];

  Mapa_mousePosicao(widget, event->x, event->y, &mouseX, &mouseY);

  Editar_mouseMove(event->x, event->y, mouseX,mouseY);

  sprintf(str,"%lf - %lf",mouseX,mouseY);
  gtk_label_set_text(labelPosicaoXY, str);

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_button_press_event(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  double mouseX, mouseY;

  Mapa_mousePosicao(widget, event->x, event->y, &mouseX, &mouseY);

  Editar_mousePressiona(event->button, mouseX, mouseY);

  return TRUE;
}

G_MODULE_EXPORT gboolean on_drawOpengl_button_release_event(GtkWidget *widget, GdkEventButton *event, gpointer data) {
  double mouseX, mouseY;
  Mapa_mousePosicao(widget, event->x, event->y, &mouseX, &mouseY);

  Editar_mouseLibera(event->button, mouseX, mouseY);

  return TRUE;
}

G_MODULE_EXPORT void on_ajustScroll_value_changed(GtkObject *object, gpointer user_data) {
  static double antHoriz=0;
  static double antVert=0;

  Mapa_deslocarVisao(-gtk_adjustment_get_value(ajustScrollHorizGL)-antHoriz,gtk_adjustment_get_value(ajustScrollVertGL)-antVert);

  antHoriz=-gtk_adjustment_get_value(ajustScrollHorizGL);
  antVert=gtk_adjustment_get_value(ajustScrollVertGL);

  Interface_atualizaOpengl();
}
