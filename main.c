/*
 * main.c
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "Header/sinais.h"
#include "Header/opengl.h"
#include "Header/mensagens.h"
#include "Header/interface.h"

int main(int argc, char *argv[]) {

  Interface_iniciar();

  gtk_main();

  Interface_finalizar();

  return 0;
}
