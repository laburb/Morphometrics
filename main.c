/*
 * main.c
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "Header/interface.h"
#include "Header/importar.h"

/**
 * Função principal do sistema.
 */

int main(int argc, char *argv[]) {

  Interface_iniciar();

  importar("rectangle_DXF_CAD2000.dxf");
  gtk_main();

  Interface_finalizar();

  return 0;
}
