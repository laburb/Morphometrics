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
 * sinais_menubar.c
 *
 *  Created on: 10/08/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "../Header/importar.h"
#include "../Header/conexoes.h"
#include "../Header/acessibilidade.h"
#include "../Header/interface.h"
#include "../Header/selecionarArquivo.h"

G_MODULE_EXPORT void on_mbArquivoImportarDFX_activate(GtkObject *object, gpointer user_data) {
  SelecionarArquivo("Importar arquivo","Importar", importar,"dxf");
}

G_MODULE_EXPORT void on_mbCalcularConectividade_activate(GtkObject *object, gpointer user_data) {
  Conexoes_verificar();
}

G_MODULE_EXPORT void on_mbAcessibilidadeTopo_activate(GtkObject *object, gpointer user_data) {
  Acessibilidade_calcular(ACESS_TOPOLOGICA);
}

G_MODULE_EXPORT void on_mbAcessibilidadeGeo_activate(GtkObject *object, gpointer user_data) {
  Acessibilidade_calcular(ACESS_GEOMETRICA);
}

G_MODULE_EXPORT void on_mbCalcularResultados_activate(GtkObject *object, gpointer user_data) {
  Interface_resultados();
}
