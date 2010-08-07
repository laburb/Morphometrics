/*
 * estruturas.c
 *
 *  Created on: 06/08/2010
 *      Author: bruno
 */
#include <stdio.h>
#include <stdlib.h>

#include "Header/estruturas.h"

static void Lista_arrumar(Lista *l) {
  int novo_id=1;
  for (; l!=NULL; l=l->prox) {
    l->id=novo_id++;
  }
}

/**
  *  @brief Lista encadeada generica
  *
  *  @param acao 'n' Novo item\n 'd' Deleta item\n 's' Procura elemento
  *  @param prim_lista Ponteiro para lista
  *  @param id Id do elemento que vai sofrer ação
  *  @param opcao MUDAR_ID modifica id para ficar em sequencia\n NAO_MUDAR_ID ação modifica o id\n ADD_CERTO adiciona no final da lista
  *  @param tamanho Tamanho da estrutura que ira ser adiciona na lista
  *
  *  @return Retorna estrutura
  *
  *  @retval poteiro para estrutura
  *  @retval NULL Falha
  *
  */

void *Lista_acao(char acao, Lista **prim_lista, int id, int opcao, int tamanho) {
  Lista *atual_lista=NULL;

  if (id<=0) {
    printf("ERRO: Id lista\n");
    return NULL;
  }

  if (acao=='n') {
    if (opcao&ADD_CERTO) {
      atual_lista = (Lista *) calloc(1,sizeof(Lista));
      atual_lista->d = (void *) calloc(1,tamanho);
      atual_lista->id = id;
      atual_lista->prox = NULL;

      if (*prim_lista!=NULL) {
        Lista *t=*prim_lista;
        while (t->prox!=NULL) t=t->prox;

        t->prox=atual_lista;
      }
      else *prim_lista=atual_lista;
    }
    else {
      atual_lista = (Lista *) calloc(1,sizeof(Lista));
      atual_lista->d = (void *) calloc(1,tamanho);
      atual_lista->id = id;
      atual_lista->prox = *prim_lista;
      *prim_lista=atual_lista;
    }
    if (opcao&MUDAR_ID) Lista_arrumar(*prim_lista);
  }
  else if (acao=='d') {
    Lista *ant = NULL;        /*  ponteiro para elemento anterior */
    Lista *p = *prim_lista;   /* ponteiro para percorrer a lista*/
    /* procura elemento na lista, guardando anterior */
    while ((p != NULL) && (p->id != id)) {
       ant = p;
       p = p->prox;
    }
    /* verifica se achou elemento */
    if (p == NULL)
       return NULL;
    /* retira elemento */
    if (ant == NULL) {
       /* retira elemento do inicio */
       *prim_lista = p->prox;
    }
    else {
       /* retira elemento do meio da lista */
       ant->prox = p->prox;
    }
    free(p->d);
    p->d=NULL;
    free(p);
    p=NULL;
    atual_lista=*prim_lista;

    if (opcao&MUDAR_ID) Lista_arrumar(*prim_lista);
  }
  else if (acao=='s') {
    for (atual_lista=*prim_lista; atual_lista!=NULL; atual_lista=atual_lista->prox) {
      if (atual_lista->id == id) {
        return atual_lista->d;
      }
    }

    if (opcao&MUDAR_ID) Lista_arrumar(*prim_lista);

    atual_lista=NULL;
  }
  else printf("ERRO: Opção invalida lista\n");

  if (atual_lista != NULL)
    return atual_lista->d;
  else
    return NULL;
}

/**
  *  @brief Insere elemento na Fila
  *
  *  @param fila Estrutura da filia
  *  @param dado Dado a ser adicionado
  *
  */

void Fila_inserir(Fila **fila, void *dado) {
  Fila *novo=calloc(1, sizeof(Fila));

  novo->dado=dado;
  novo->prox=*fila;

  *fila=novo;
}

/**
  *  @brief Remove elemento da Fila
  *
  *  @param fila Ponteiro para estrutura da filia
  *
  *  @return Retorna ultimo elemento da fila
  *
  *  @retval poteiro para o dado
  *  @retval NULL Falha
  *
  */

void *Fila_remover(Fila **fila) {
  void *dado;

  Fila *perc=*fila;
  Fila *ant=NULL;

  while (perc != NULL) {
    if (perc->prox == NULL) {
      if (ant == NULL)
        *fila=perc->prox;
      else
        ant->prox=perc->prox;

      dado=perc->dado;
      free(perc);

      return dado;
    }

    ant=perc;
    perc=perc->prox;
  }

  return NULL;
}

/**
  *  @brief Libera a fila da memoria
  *
  *  @param fila Ponteiro para estrutura da filia
  *
  */

void Fila_apagar(Fila **fila) {
  Fila *perc=*fila;
  Fila *ant;

  while (perc) {
    ant=perc;
    perc=perc->prox;
    free(ant);
  }

  *fila=NULL;
}

/**
  *  @brief Libera a pilha da memoria
  *
  *  @param p Ponteiro para estrutura da pilha
  *
  */

void Pilha_deletar(Pilha *p) {
  int percorre=0;
  for (percorre=0; percorre < p->tamanhoMaximo ;percorre++) {
    p->val[percorre]=NULL;
  }
  p->topo=0;
}

/**
  *  @brief Cria pilha
  *
  *  @param tamanho Tamanho da pilha
  *
  *  @return Estrutura da pilha
  *
  *  @retval poteiro para a pilha
  *
  */

Pilha *Pilha_criar(int tamanho) {
  Pilha *p=(Pilha *) malloc(sizeof(Pilha));
  p->val=(void **) calloc(tamanho,sizeof(void *));
  p->topo=0;
  p->tamanhoMaximo=tamanho;
  return p;
}

/**
  *  @brief Adicona elemento na pilha
  *
  *  @param p Estrutura da pilha
  *  @param dado Dado a ser adicionado
  *
  */

void Pilha_push(Pilha *p,void *dado) {
  if (p->topo < p->tamanhoMaximo)
    p->val[p->topo++]=dado;
  else
    printf("Estorou pilha\n");
}

/**
  *  @brief Remove elemento da pilha
  *
  *  @param p Estrutura da pilha
  *
  *  @return Retorna primeiro elemento da pilha
  *
  *  @retval poteiro para o dado
  *  @retval NULL Falha
  *
  */

void *Pilha_pop(Pilha *p) {
  if (p->topo>0)
    return p->val[--p->topo];
  else
    return NULL;
}
