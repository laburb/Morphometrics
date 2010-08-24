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
 * projeto.h
 *
 *  Created on: 19/08/2010
 *      Author: bruno
 */

#ifndef PROJETO_H_
#define PROJETO_H_

  #include "acessibilidade.h"

  typedef struct {
    int id;
    double valor;
  } ArrayValor;

  void Projeto_fechar();

  int Projeto_verificarExisteTabela(char *tabela);

  int Projeto_zeraAcessibilidade(enum TipoAcessibilidade tipo);
  int Projeto_addAcessibilidade(enum TipoAcessibilidade tipo, int id, double absoluta);

  int Projeto_zeraConectividade();
  int Projeto_addConectividade(int id, int conct);

  int Projeto_lista(int(*callback)(void*, int, char**, char**), void *parm, char *tabela, char *ordemCol, int ordem);

  int Projeto_iniciarTransacao();
  int Projeto_terminarTransacao();

  ArrayValor *Projeto_getArrayValor(char *tabela, char *coluna, int ordem, int mostraErro);

  char *projetoAtual;

#endif /* PROJETO_H_ */
