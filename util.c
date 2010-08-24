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
 * util.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "Header/ponto.h"
#include "Header/util.h"


/**
 *  Posiciona o 'cursor' do arquivo depois da string procurada.
 *
 *  Caso string não for achada o 'cursor' volta a posição anterior.
 *
 *  @param fp Arquivo
 *  @param str String procurada
 *  @param inicio Se for 1 procura desde o inicio, caso contrario apartir da posição atual do 'cursor.'
 *
 *  @return Retorna se achou com sucesso
 *
 *  @retval 1 Sucesso
 *  @retval 0 Falha
 *
 */

int Arquivo_acharString(FILE *fp, char *str, int inicio) {
  char strTmp[512];

  long posic=ftell(fp);

  if (inicio)
    rewind(fp);

  while (fscanf(fp, "%s",strTmp) != EOF) {
    if (!strcmp(str,strTmp))
      return 1;
  }

  fseek(fp, posic, SEEK_SET);
  return 0;
}

/**
 *  Converte string para maiúsculo
 *
 *  @param str String
 *
 */
void convertToUpperCase(char *str) {
   for (; *str ;str++)
     *str = toupper(*str);
}
