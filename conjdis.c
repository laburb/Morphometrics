#include <stdio.h>
#include <stdlib.h>

#include "Header/conjdis.h"

Conjdis *Conjdis_iniciar(int tamanho) {
	int i;
	Conjdis *a=malloc(sizeof(Conjdis));
	a->v=malloc(tamanho * sizeof(int));
	a->tamanho=tamanho;

	for (i=0; i<tamanho ;i++)
		a->v[i]=i;

	return a;
}

void Conjdis_deletar(Conjdis **conj) {
  if (*conj) {
    if ((*conj)->v)
      free((*conj)->v);
    free(*conj);
  }

  *conj=NULL;
}

int Conjdis_procurar(Conjdis *cd, int elem) {
	int i=elem;

	if ((elem >= cd->tamanho) || (elem < 0))
		return -1;

	while (cd->v[i] != i)
		i=cd->v[i];

	cd->v[elem]=i;

	return i;
}

void Conjdis_juntar(Conjdis *cd, int elem1, int elem2) {
	int pos1=Conjdis_procurar(cd,elem1);
	int pos2=Conjdis_procurar(cd,elem2);

	if ((pos1 != -1) && (pos2 != -1))
		cd->v[pos1]=pos2;
}
