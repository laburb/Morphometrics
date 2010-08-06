/*
 * importDFX.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include <stdio.h>

#include "Header/importDFX.h"

/**
  *  @brief Função que importa arquivo no formato DFX
  *
  *  @param arquivo String referente ao comando.
  *
  *  @return Sucesso na importação
  *
  *  @retval 1 Sucesso
  *  @retval 0 Falha
  *
  */

int importDFX(char *arquivo) {
  FILE *fp;

  fp=fopen(arquivo, "r");
  if (!fp)
    return 0;



  return 1;
}
