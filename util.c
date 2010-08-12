/*
 * util.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
  char strTmp[256];

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
