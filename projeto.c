/*
 * projeto.c
 *
 *  Created on: 19/08/2010
 *      Author: bruno
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "Header/sqlite3.h"
#include "Header/mensagens.h"
#include "Header/acessibilidade.h"
#include "Header/projeto.h"

//#define DEBUG

char *projetoAtual="Projetos/teste.morph";
static sqlite3 *handle=NULL;

void Projeto_novo() {
  if (projetoAtual)
    free(projetoAtual);

  projetoAtual=NULL;
  handle=NULL;
}

void Projeto_abrir(char *nome) {
  projetoAtual=strdup(nome);
}

void Projeto_salvar(char *nome) {

}

static int Projeto_openBanco(int mostraErro) {
  int retval = sqlite3_open(projetoAtual,&handle);

  if (retval) {
    if (mostraErro)
      Mensagem(MENSAGEM_ERRO, "Erro", "Erro ao abrir projeto: ", sqlite3_errmsg(handle));

    sqlite3_close(handle);
    return 0;
  }

  return 1;
}

static int execSql(char *sql, int (*callback)(void*,int,char**,char**), void *arg, int mostraErro) {
  char *zErrMsg=NULL;
  int retval;

  if (handle == NULL) {
    if (!Projeto_openBanco(mostraErro))
      return 0;
  }

#ifdef DEBUG
  printf("Debug: %s\n",sql);
#endif

  retval=sqlite3_exec(handle,sql,callback,arg,&zErrMsg);

  if (retval != SQLITE_OK) {
    if (mostraErro)
      Mensagem(MENSAGEM_ERRO, "Erro", "Erro: %s", zErrMsg);

    sqlite3_free(zErrMsg);
    return 0;
  }

  return 1;
}

int Projeto_iniciarTransacao() {
  return execSql("BEGIN", NULL, NULL, 1);
}

int Projeto_terminarTransacao() {
  return execSql("COMMIT", NULL, NULL, 1);
}

int Projeto_verificarExisteTabela(char *tabela) {
  char sql[256];

  sprintf(sql,"select 1 from %s limit 1", tabela);

  return execSql(sql,0,0,0);
}

int Projeto_zeraAcessibilidade(enum TipoAcessibilidade tipo) {
  if (tipo == ACESS_GEOMETRICA) {
    char create_table[256] = "CREATE TABLE IF NOT EXISTS acess_geo (id INTEGER PRIMARY KEY,absoluta FLOAT NOT NULL)";
    if (!execSql(create_table,NULL, NULL, 1))
      return 0;

    if (!execSql("delete from acess_geo",NULL, NULL, 1))
      return 0;
  }
  else if (tipo == ACESS_TOPOLOGICA) {
    char create_table[256] = "CREATE TABLE IF NOT EXISTS acess_topo (id INTEGER PRIMARY KEY,absoluta FLOAT NOT NULL)";
    if (!execSql(create_table,NULL, NULL, 1))
      return 0;

    if (!execSql("delete from acess_topo",NULL, NULL, 1))
      return 0;
  }

  return 1;
}

int Projeto_addAcessibilidade(enum TipoAcessibilidade tipo, int id, double absoluta) {
  char sql[256];

  sprintf(sql,"insert into %s values(%d,%lf)",(tipo == ACESS_GEOMETRICA)?"acess_geo":"acess_topo",id, absoluta);

  return execSql(sql,0,0,1);
}

int Projeto_zeraConectividade() {
  char create_table[256] = "CREATE TABLE IF NOT EXISTS conectividade (id INTEGER PRIMARY KEY,valor INTEGER NOT NULL)";
  if (!execSql(create_table,NULL, NULL, 1))
    return 0;

  if (!execSql("delete from conectividade",NULL, NULL, 1))
    return 0;

  return 1;
}

int Projeto_addConectividade(int id, int conct) {
  char sql[256];

  sprintf(sql,"insert into conectividade values(%d,%d)",id, conct);

  return execSql(sql,0,0,1);
}

int Projeto_lista(int (*callback)(void*,int,char**,char**), void *parm,char *tabela, char *ordemCol, int ordem) {
  char sql[256];

  if (!Projeto_verificarExisteTabela("conectividade"))
    return 0;

  sprintf(sql,"select * from %s order by %s %s",tabela, ordemCol, (ordem == 1)?"desc":"asc");

  return execSql(sql, callback, parm, 1);
}

void Projeto_fechar() {
  if (handle)
    sqlite3_close(handle);
}

ArrayValor *Projeto_getArrayValor(char *tabela, char *coluna, int ordem, int mostraErro) {
  char sql[256];
  char *zErrMsg=NULL;
  char **resultado;
  int retval, i, numRow;
  ArrayValor *retorno=NULL;

  if (handle == NULL) {
    if (!Projeto_openBanco(mostraErro))
      return 0;
  }

  sprintf(sql, "select id, %s from %s order by %s %s", coluna, tabela, coluna ,(ordem == 1)?"desc":"asc");

  retval=sqlite3_get_table(handle, sql, &resultado, &numRow, NULL, &zErrMsg);

  if (retval != SQLITE_OK) {
    if (mostraErro)
      Mensagem(MENSAGEM_ERRO, "Erro", "Erro: %s", zErrMsg);

    sqlite3_free(zErrMsg);

    return NULL;
  }

  retorno=malloc((numRow+1) * sizeof(ArrayValor));

  for (i=2; i<(numRow+1)*2 ; i++) {
    if (i%2 == 0)
      retorno[(i-2)/2].id=atoi(resultado[i]);
    else
      retorno[(i-2)/2].valor=atof(resultado[i]);
  }

  retorno[numRow].id=-1;

  sqlite3_free_table(resultado);

  return retorno;
}
