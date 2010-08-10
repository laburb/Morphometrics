/*
 * main.c
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "Header/interface.h"
#include "Header/importar.h"
#include "Header/grafo.h"
#include "Header/util.h"

/**
 * Função principal do sistema.
 */

int main(int argc, char *argv[]) {
  grafo=Grafo_iniciar();

  Interface_iniciar();

  gtk_main();

  Interface_finalizar();

  return 0;
}
