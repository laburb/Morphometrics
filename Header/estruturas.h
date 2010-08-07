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
