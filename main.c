/*
 * main.c
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#include <stdlib.h>
#include <locale.h>

#include "Header/interface.h"
#include "Header/importar.h"
#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/util.h"
#include "Header/projeto.h"

/**
 * Função principal do sistema.
 */

int main(int argc, char *argv[]) {
  mapa.grafo=Grafo_iniciar();
  Mapa_iniciar();
  Interface_iniciar();

  setlocale(LC_ALL,"C");

  gtk_main();

  Interface_finalizar();
  Projeto_fechar();

  return 0;
}
