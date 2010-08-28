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
 * interface.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkgl.h>

#include "Header/opengl.h"
#include "Header/projeto.h"
#include "Header/interface.h"

#define INTERFACE_CAMINHO "Interface/"
#define INTERFACE_PRINCIPAL "principal.glade"

struct resultaInter listaResult[4] = {
    { "conectividade", "Conectividade", "Conexoes", "valor",  { TRUE, TRUE , FALSE, FALSE, FALSE }},
    { "acess_geo", "Acessibilidade Geometrica", "", "absoluta",  { TRUE, FALSE, TRUE , TRUE , TRUE  }},
    { "acess_topo", "Acessibilidade Topologica", "", "absoluta", { TRUE, FALSE, TRUE , TRUE , TRUE  }},
    {""}
};

static char *colunasResult[] = {"valor", "absoluta", "relativa", "razao", ""};

/**
 *  Inicia o gtk e gtkextgl.
 *
 *  Carrega a interface definica pela macro INTERFACE_PRINCIPAL
 *
 */

void Interface_iniciar() {
  GtkWidget *window;
  GdkGLConfig *glconfig;

  gtk_init(NULL, NULL);
  gtk_gl_init(NULL, NULL);


  GtkBuilder *builderPrincipal=Interface_carregarXML(INTERFACE_PRINCIPAL);
  window = GTK_WIDGET(gtk_builder_get_object (builderPrincipal, "window"));
  drawOpengl=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "drawOpengl"));
  frameProgresso=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "frameProgresso"));
  progress=GTK_PROGRESS_BAR(gtk_builder_get_object(builderPrincipal, "progressbar"));
  labelPosicaoXY=GTK_LABEL(gtk_builder_get_object(builderPrincipal, "labelPosicaoXY"));
  ajustScrollHorizGL=GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollHorizGL"));
  ajustScrollVertGL=GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "ajustScrollVertGL"));
  adjustAlpha=GTK_ADJUSTMENT(gtk_builder_get_object(builderPrincipal, "adjustAlpha"));
  tbAddEntidade=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddEntidade"));
  tbAddImagem=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddImagem"));
  tbAddTexto=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAddTexto"));
  tbAmpliar=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbAmpliar"));
  tbReduzir=GTK_TOGGLE_TOOL_BUTTON(gtk_builder_get_object(builderPrincipal, "tbReduzir"));
  frameFerramentas=GTK_WIDGET(gtk_builder_get_object(builderPrincipal, "frameFerramentas"));

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

  g_object_unref(G_OBJECT(builderPrincipal));
}

/**
 *  Finaliza a interface
 *
 */

void Interface_finalizar() {

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
  GdkCursor *cur=gdk_cursor_new(tipoMouse);
  gdk_window_set_cursor(drawOpengl->window, cur );
  gdk_cursor_unref(cur);
}

/**
 * Chama Opengl_configTela e redesenha a tela.
 */

void Interface_atualizaOpengl() {
  Opengl_configTela(drawOpengl->allocation.width, drawOpengl->allocation.height);

  gdk_window_invalidate_rect (drawOpengl->window, &drawOpengl->allocation, FALSE);
  gdk_window_process_updates (drawOpengl->window, FALSE);
}

int getIndex(char *nome) {
  int i;

  for (i=0; colunasResult[i][0] ;i++)
    if (!strcmp(nome,colunasResult[i]))
      return i+1;

  return -1;
}

static int preencheResultados(void *x, int qtdCol, char **conteudo, char **nomeCol) {
  int i;
  GtkTreeIter iter;
  GtkListStore *listaStore=(GtkListStore *) x;

  gtk_list_store_append(listaStore, &iter);

  gtk_list_store_set(listaStore, &iter, 0, atoi(conteudo[0]), -1);

  for (i=1; i<qtdCol ;i++)
    gtk_list_store_set(listaStore, &iter, getIndex(nomeCol[i]), atof(conteudo[i]), -1);

  return 0;
}

static void addItemCombo(GtkListStore *listaCombo, char *nome, int id) {
  GtkTreeIter iter;

  gtk_list_store_append(listaCombo, &iter);

  gtk_list_store_set(listaCombo, &iter,
                     0, nome,
                     1, id,
                    -1);
}

void on_combobox_changed(GtkComboBox *combo_box, gpointer user_data) {
  GtkTreeView *treeview=GTK_TREE_VIEW(user_data);
  GtkTreeModel *model = gtk_combo_box_get_model(combo_box);
  GtkListStore *listaStore=GTK_LIST_STORE(gtk_tree_view_get_model(treeview));
  GtkTreeViewColumn *colTmp;
  GtkTreeIter iter;

  gint val = 0;
  int i;

  if (!gtk_combo_box_get_active_iter (combo_box, &iter))
    return;

  gtk_tree_model_get(model, &iter, 1, &val, -1);

  gtk_list_store_clear(listaStore);

  if (val == -1)
    return;

  if (listaResult[val].colResult[0]) {
    GtkTreeViewColumn *colTmp=gtk_tree_view_get_column(treeview, 1);

    gtk_tree_view_column_set_title(colTmp, listaResult[val].colResult);
  }

  for (i=0; i<5 ;i++) {
    colTmp=gtk_tree_view_get_column(treeview, i);
    gtk_tree_view_column_set_visible(colTmp, listaResult[val].colunasViziveis[i]);
  }

  Projeto_lista(preencheResultados, listaStore, listaResult[val].tabela, listaResult[val].colPrincipal, 1);
}


gint sort_iter_compare_func (GtkTreeModel *model,
                        GtkTreeIter  *a,
                        GtkTreeIter  *b,
                        gpointer      userdata) {

  gint sortcol = GPOINTER_TO_INT(userdata);

  if (sortcol == 0) {
    gint numero, numero2;

    gtk_tree_model_get(model, a, sortcol, &numero, -1);
    gtk_tree_model_get(model, b, sortcol, &numero2, -1);

    if (numero != numero2)
      return (numero>numero2)?1:-1;
  }
  else {
    gfloat numero, numero2;

    gtk_tree_model_get(model, a, sortcol, &numero, -1);
    gtk_tree_model_get(model, b, sortcol, &numero2, -1);

    if (numero != numero2)
      return (numero>numero2)?1:-1;
  }

  return 0;
}


void Interface_resultados() {
  int i;
  GtkBuilder *buildResult=Interface_carregarXML("resultados.glade");
  GtkWidget *window = GTK_WIDGET(gtk_builder_get_object (buildResult, "window"));
  comboResultados = GTK_COMBO_BOX(gtk_builder_get_object (buildResult, "combobox"));
  GtkListStore *listaCombo = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_INT);
  GtkTreeView *treeview = GTK_TREE_VIEW(gtk_builder_get_object (buildResult, "treeview"));
  GtkTreeSortable *treeOrdenar = GTK_TREE_SORTABLE(gtk_builder_get_object(buildResult, "liststore"));

  gtk_tree_sortable_set_sort_func(treeOrdenar, 0, sort_iter_compare_func, GINT_TO_POINTER(0), NULL);
  gtk_tree_sortable_set_sort_func(treeOrdenar, 1, sort_iter_compare_func, GINT_TO_POINTER(1), NULL);
  gtk_tree_sortable_set_sort_func(treeOrdenar, 2, sort_iter_compare_func, GINT_TO_POINTER(2), NULL);
  gtk_tree_sortable_set_sort_func(treeOrdenar, 3, sort_iter_compare_func, GINT_TO_POINTER(3), NULL);
  gtk_tree_sortable_set_sort_func(treeOrdenar, 4, sort_iter_compare_func, GINT_TO_POINTER(4), NULL);

  addItemCombo(listaCombo, "Selecione", -1);

  //Monta combo
  for (i=0; listaResult[i].tabela[0] ;i++) {
    if (Projeto_verificarExisteTabela(listaResult[i].tabela))
      addItemCombo(listaCombo, listaResult[i].nome, i);
  }

  gtk_combo_box_set_model(comboResultados, GTK_TREE_MODEL(listaCombo));
  GtkCellRenderer *cell_renderer = gtk_cell_renderer_text_new ();
  gtk_cell_layout_pack_start (GTK_CELL_LAYOUT(comboResultados), cell_renderer, TRUE);
  gtk_cell_layout_set_attributes (GTK_CELL_LAYOUT(comboResultados), cell_renderer, "text", 0, NULL);
  gtk_combo_box_set_active(comboResultados,0);

  g_signal_connect (comboResultados, "changed", G_CALLBACK (on_combobox_changed), treeview);

  gtk_builder_connect_signals(buildResult, NULL);
  gtk_widget_show(window);

  g_object_unref(G_OBJECT(buildResult));
}
