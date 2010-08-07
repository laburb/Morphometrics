/*
 * importar.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */
#include <stdio.h>
#include <string.h>
#include <locale.h>

#include "Header/mensagens.h"
#include "Import/Header/importDFX.h"
#include "Header/importar.h"

/**
 * Estrutura contendo as extensões suportadas e as funções especificas.
 */
  struct {
    /** Extensão */
    char *ext;

    /** Função */
    int (*func)(char *);

  } listaExt[] = {
      {".dxf", importDFX},
      {"", NULL}
  };

/**
 *  Importa um arquivo.
 *
 *  Chama outra função responsavel por importar o arquivo especificada em listaExt.
 *
 *  @param arquivo Caminho do arquivo
 *
 */

void importar(char *arquivo) {
  int i;
  char extensao[5];
  char *extTmp;
  char *old_locale, *saved_locale;

  if ((arquivo == NULL) || (arquivo[0] == '\0')) {
    Mensagem(MENSAGEM_ERRO,"","Erro ao importar, informe um nome da arquivo válido.");
    return;
  }

  extTmp=strrchr(arquivo,'.');

  if (extTmp) {
    strncpy(extensao,extTmp,4);
    extensao[4]='\0';

    //seta a localidade para usar o ponto decimal como '.'
    old_locale = setlocale (LC_ALL, NULL);
    saved_locale=strdup(old_locale);

    setlocale(LC_ALL,"C");

    //chama funcao referente a extensao do arquivo
    for (i=0; listaExt[i].func ;i++) {
      if (!strcmp(listaExt[i].ext, extensao)) {
        listaExt[i].func(arquivo);
        /*
        if (listaExt[i].func(arquivo))
          Mensagem(MENSAGEM_INFORMACAO,"","Arquivo importado com sucesso!");
        else
          Mensagem(MENSAGEM_ERRO,"","Erro ao importar arquivo: %s",arquivo);
*/
        //volta a localidade anterior
        setlocale(LC_ALL,saved_locale);
        free(saved_locale);
        return;
      }
    }

    //volta a localidade anterior
    setlocale(LC_ALL,saved_locale);
    free(saved_locale);
  }

  Mensagem(MENSAGEM_ERRO,"","Extensão não suportada.");
}
