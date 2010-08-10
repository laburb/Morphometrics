/*
 * selecionarArquivo.c
 *
 *  Created on: 09/08/2010
 *      Author: bruno
 */

#include <string.h>
#include <gtk/gtk.h>

#include "Header/util.h"
#include "Header/selecionarArquivo.h"

/**
  *  @brief Mostra um dialog de seleção de arquivos.
  *
  *  @param titulo Titulo da janela
  *  @param botao Botão
  *  @param func Função que ira ser chamada ao clicar no botao
  *  @param extensoes Filtro de extensões formato: "bmp txt png"
  *
  */

void SelecionarArquivo(char *titulo, char *botao, void (*func)(char *), char *extensoes) {
  char exts[512], ext1[128],ext2[128];

  GtkFileFilter *filter;
  GtkWidget *fileSelect=gtk_file_chooser_dialog_new(titulo, NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
                                                                  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                                  botao, GTK_RESPONSE_ACCEPT,
                                                                  NULL);

  if (extensoes) {
    strncpy(exts,extensoes,512);

    char *pch = strtok(exts," ");

    while (pch != NULL) {
      sprintf(ext1, "*.%s", pch);

      convertToUpperCase(pch);
      sprintf(ext2, "Arquivos %s", pch);

      filter = gtk_file_filter_new();
      gtk_file_filter_set_name(filter,ext2);
      gtk_file_filter_add_pattern(filter, ext1);

      gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fileSelect), filter);

      pch = strtok(NULL," ");
    }
  }

  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter,"Todos os arquivos");
  gtk_file_filter_add_pattern(filter, "*");

  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(fileSelect), filter);

  if (gtk_dialog_run(GTK_DIALOG (fileSelect)) == GTK_RESPONSE_ACCEPT) {
    char *filename;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(fileSelect));
    func(filename);

    g_free (filename);
  }

  gtk_widget_destroy(fileSelect);
}
