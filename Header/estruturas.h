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
 * estruturas.h
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */

#ifndef ESTRUTURAS_H_
#define ESTRUTURAS_H_

  #define MUDAR_ID 1
  #define NAO_MUDAR_ID 0

  #define ADD_CERTO 2

  typedef struct lista {
    int id;
    void *d;
    struct lista *prox;
  } Lista;

  typedef struct {
    void **val;
    int topo;
    int tamanhoMaximo;
  } Pilha;

  typedef struct fila {
    void *dado;
    struct fila *prox;
  } Fila;

  void *Lista_acao(char acao, Lista **prim_lista, int id, int opcao, int tamanho);

  void Pilha_deletar(Pilha *p);
  Pilha *Pilha_criar(int tamanho);
  void Pilha_push(Pilha *p,void *dado);
  void *Pilha_pop(Pilha *p);

  void Fila_inserir(Fila **fila, void *dado);
  void *Fila_remover(Fila **fila);
  void Fila_apagar(Fila **fila);

#endif /* ESTRUTURAS_H_ */
