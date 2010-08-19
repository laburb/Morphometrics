/*
 * interface.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "Header/opengl.h"
#include "Header/projeto.h"
#include "Header/interface.h"

#define INTERFACE_CAMINHO "Interface/"
#define INTERFACE_PRINCIPAL "principal.glade"

/**
 *  Inicia o gtk e gtkextgl.
 *
 *  Carrega a interface definica pela macro INTERFACE_PRINCIPAL
 *
 */

void Interface_iniciar() {
  GtkWidget *drawOpengl;
  GtkWidget *window;
  GdkGLConfig *glconfig;

  gtk_init(NULL, NULL);
  gtk_gl_init(NULL, NULL);


  builderPrincipal=Interface_carregarXML(INTERFACE_PRINCIPAL);
  window = GTK_WIDGET(gtk_builder_get_object (builderPrincipal, "window"));
  drawOpengl=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "drawOpengl"));

  /*gtk_adjustment_set_value(GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollHorizGL")),500);
  gtk_adjustment_set_value(GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollVertGL")),500);*/

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

/**
 *  Finaliza a interface
 *
 */

void Interface_finalizar() {
  g_object_unref(G_OBJECT(builderPrincipal));
}

/**
 *  Carrega a interface do arquivo xml.
 *
 *  Diretorio base especificado pela macro INTERFACE_CAMINHO
 *
 *  @param arquivo Nome do arquivo a ser carregado
 *
 */

GtkBuilder *Interface_carregarXML(char *arquivo) {
  char local[256];
  GtkBuilder *builder;

  strcpy(local,INTERFACE_CAMINHO);
  strcat(local,arquivo);

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, local, NULL);


  return builder;
}
/*
#include "Imagens/cursor/zoom-out.xbm"
#include "Imagens/cursor/zoom-out-mask.xbm"
void Interface_carregaCursor() {
  GdkCursor *cursor;
  GdkPixmap *source, *mask;
  GdkColor fg = { 0, 0, 0, 0 };
  GdkColor bg = { 0, 65535, 65535, 65535 };

  source = gdk_bitmap_create_from_data (NULL, zoom_out_bits, zoom_out_width, zoom_out_height);
  mask = gdk_bitmap_create_from_data (NULL, zoom_out_mask_bits, zoom_out_mask_width, zoom_out_mask_height);
  cursor = gdk_cursor_new_from_pixmap (source, mask, &fg, &bg, 8, 8);
  g_object_unref (source);
  g_object_unref (mask);

  gdk_window_set_cursor (GDK_ROOT_PARENT(), cursor);
}*/


/**
 *  Modifica o cursor do mouse.
 *
 *  @param tipoMouse Tipo do mouse
 *
 */

void Interface_mudarMouse(GdkCursorType tipoMouse) {
  GtkWidget *drawOpengl=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "drawOpengl"));

  GdkCursor *cur=gdk_cursor_new(tipoMouse);
  gdk_window_set_cursor(drawOpengl->window, cur );
  gdk_cursor_unref(cur);
}

/**
 * Chama Opengl_configTela e redesenha a tela.
 */

void Interface_atualizaOpengl() {
  GtkWidget *drawOpengl=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "drawOpengl"));

  Opengl_configTela(drawOpengl->allocation.width, drawOpengl->allocation.height);

  gdk_window_invalidate_rect (drawOpengl->window, &drawOpengl->allocation, FALSE);
  gdk_window_process_updates (drawOpengl->window, FALSE);
}



void Interface_resultados() {
  GtkBuilder *buildResult=Interface_carregarXML("resultados.glade");
  GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (buildResult, "window"));
  GtkComboBox *combo = GTK_COMBO_BOX(gtk_builder_get_object (buildResult, "combobox"));
  GtkListStore *listaCombo = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
  GtkTreeIter iter;

  gtk_builder_connect_signals(builderPrincipal, NULL);
  gtk_widget_show(window);

  gtk_list_store_append (listaCombo, &iter);

  if (Projeto_verificarExisteTabela("conectividade")) {
    gtk_list_store_set (listaCombo, &iter,
                        0, "Conectividade",
                        1, 1,
                        -1);
    gtk_list_store_append (listaCombo, &iter);
  }

  if (Projeto_verificarExisteTabela("acess_geo")) {
    gtk_list_store_set (listaCombo, &iter,
                        0, "Acessibilidade Geometrica",
                        1, 2,
                        -1);
    gtk_list_store_append (listaCombo, &iter);
  }

  if (Projeto_verificarExisteTabela("acess_topo")) {
    gtk_list_store_set (listaCombo, &iter,
                        0, "Acessibilidade Topologica",
                        1, 3,
                        -1);
    gtk_list_store_append (listaCombo, &iter);
  }


  gtk_combo_box_set_model(combo, GTK_TREE_MODEL(listaCombo));
  GtkCellRenderer *cell_renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(combo), cell_renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT(combo), cell_renderer, "text", 0, NULL);
  gtk_combo_box_set_active_iter (GTK_COMBO_BOX(combo), &iter);


  /*if (Projeto_verificarExisteTabela("conectividade")) {
    gtk_combo_box_append_text(combo, "Conectividade");
  }*/
  /*gtk_combo_box_append_text(combo, "Conectividade");
  gtk_combo_box_append_text(combo, "Conectividade2");
  gtk_combo_box_append_text(combo, "sdfsdfsd");*/
/*
  if (Projeto_verificarExisteTabela("acess_geo"))
      gtk_combo_box_append_text(combo, "Acessibilidade Geometrica");

  if (Projeto_verificarExisteTabela("acess_topo"))
        gtk_combo_box_append_text(combo, "Acessibilidade Topologica");
*/
  g_object_unref(G_OBJECT(buildResult));
}
