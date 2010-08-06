/*
 * importar.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */
#include <stdio.h>
#include <string.h>

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

  if ((arquivo == NULL) || (arquivo[0] == '\0')) {
    Mensagem(MENSAGEM_ERRO,"","Erro ao importar, informe um nome da arquivo válido.");
    return;
  }

  extTmp=strrchr(arquivo,'.');

  if (extTmp) {
    strncpy(extensao,extTmp,4);
    extensao[4]='\0';

    //chama funcao referente a extensao do arquivo
    for (i=0; listaExt[i].func ;i++) {
      if (!strcmp(listaExt[i].ext, extensao)) {
        if (listaExt[i].func(arquivo))
          Mensagem(MENSAGEM_INFORMACAO,"","Arquivo importado com sucesso!");
        else
          Mensagem(MENSAGEM_ERRO,"","Erro ao importar arquivo: %s",arquivo);

        return;
      }
    }
  }

  Mensagem(MENSAGEM_ERRO,"","Extensão não suportada.");
}
