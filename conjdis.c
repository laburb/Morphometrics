#include <stdio.h>
#include <stdlib.h>

#include "Header/conjdis.h"

/**
 *  Inciar o conjunto disjunto.
 *
 *  @param tamanho Tamanho do conjunto
 *
 *  @return Estrutura do conjunto
 */

Conjdis *Conjdis_iniciar(int tamanho) {
	int i;
	Conjdis *a=malloc(sizeof(Conjdis));
	a->v=malloc(tamanho * sizeof(int));
	a->tamanho=tamanho;

	for (i=0; i<tamanho ;i++)
		a->v[i]=i;

	return a;
}

/**
 *  Libera da memoria o conjunto.
 *
 *  @param conj Ponteiro para estrutura do conjunto
 */


void Conjdis_deletar(Conjdis **conj) {
  if (*conj) {
    if ((*conj)->v)
      free((*conj)->v);
    free(*conj);
  }

  *conj=NULL;
}

/**
 *  Procura o conjunto de um elemento.
 *
 *  @param cd Estrutura do conjunto
 *  @param elem Elemento
 *
 *  @return Retorna o conjunto pertencente do elemento
 *
 *  @retval 1>= Conjunto pertencente
 *  @retval -1 Falha
 *
 */

int Conjdis_procurar(Conjdis *cd, int elem) {
	int i=elem;

	if ((elem >= cd->tamanho) || (elem < 0))
		return -1;

	while (cd->v[i] != i)
		i=cd->v[i];

	cd->v[elem]=i;

	return i;
}

/**
 *  Junta dois conjuntos apartir do conjunto dos dois elementos passados por parametro.
 *
 *  @param cd Estrutura do conjunto
 *  @param elem1 Elemento
 *  @param elem2 Elemento
 *
 */

void Conjdis_juntar(Conjdis *cd, int elem1, int elem2) {
	int pos1=Conjdis_procurar(cd,elem1);
	int pos2=Conjdis_procurar(cd,elem2);

	if ((pos1 != -1) && (pos2 != -1))
		cd->v[pos1]=pos2;
}
