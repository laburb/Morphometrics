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
 * sinais_resultados.c
 *
 *  Created on: 20/08/2010
 *      Author: bruno
 */
#include <gtk/gtk.h>
#include <stdlib.h>

#include "../Header/projeto.h"
#include "../Header/classificacao.h"
#include "../Header/mensagens.h"
#include "../Header/interface.h"

G_MODULE_EXPORT void on_colOrdenar_clicked(GtkTreeViewColumn *coluna, gpointer user_data) {
  GtkTreeView *treeView=GTK_TREE_VIEW(coluna->tree_view);
  GtkTreeSortable *treeSort=GTK_TREE_SORTABLE(gtk_tree_view_get_model(treeView));
  GList *listaColunas=gtk_tree_view_get_columns(treeView);
  GList *node;
  int id=0,cont=0;

  gboolean indicador=gtk_tree_view_column_get_sort_indicator(coluna);
  GtkSortType sortTipo=gtk_tree_view_column_get_sort_order(coluna);

  //Tira o indicador de ordenação de todas as colunas
  for (node = listaColunas;  node != NULL ;  node = node->next,cont++) {
      GtkTreeViewColumn *colunaTMP = (GtkTreeViewColumn*) node->data;

      if (colunaTMP == coluna)
        id=cont;

      gtk_tree_view_column_set_sort_indicator(colunaTMP,FALSE);
  }

  gtk_tree_view_column_set_sort_indicator(coluna,TRUE);

  if (!indicador)
    sortTipo=GTK_SORT_ASCENDING;
  else
    sortTipo=(sortTipo == GTK_SORT_ASCENDING)?GTK_SORT_DESCENDING:GTK_SORT_ASCENDING;

  gtk_tree_view_column_set_sort_order(coluna, sortTipo);


  gtk_tree_sortable_set_sort_column_id(treeSort, id, sortTipo);

  g_list_free(listaColunas);
}

G_MODULE_EXPORT void on_btExportar_clicked(GtkObject *obj, gpointer user_data) {
  printf("aqui\n");
}

G_MODULE_EXPORT void on_btVisualizar_clicked(GtkObject *obj, gpointer user_data) {
  GtkTreeModel *model = gtk_combo_box_get_model(comboResultados);
  GtkTreeIter iter;

  gint val = 0;

  if (!gtk_combo_box_get_active_iter (comboResultados, &iter))
    return;

  gtk_tree_model_get(model, &iter, 1, &val, -1);

  if (val == -1)
    Mensagem(MENSAGEM_ERRO, "Erro", "Selecione a opção que deseja visualizar.");
  else {
    ArrayValor *valores=Projeto_getArrayValor(listaResult[val].tabela, listaResult[val].colPrincipal, 2, 1);

    Classificacao(valores);

    free(valores);

    Interface_atualizaOpengl();
  }
}
