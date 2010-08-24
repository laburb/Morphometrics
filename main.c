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
