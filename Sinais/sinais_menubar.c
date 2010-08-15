/*
 * sinais_menubar.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "../Header/importar.h"
#include "../Header/conexoes.h"
#include "../Header/selecionarArquivo.h"

G_MODULE_EXPORT void on_mbArquivoImportarDFX_activate(GtkObject *object, gpointer user_data) {
  SelecionarArquivo("Importar arquivo","Importar", importar,"dxf");
}

G_MODULE_EXPORT void on_mbCalcularConectividade_activate(GtkObject *object, gpointer user_data) {
  Conexoes_verificar();
}
