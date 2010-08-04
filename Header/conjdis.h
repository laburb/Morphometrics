#ifndef _CONJDIS_H_
#define _CONJDIS_H_

	typedef struct {
		int *v;
		int tamanho;
	} Conjdis;


	Conjdis *Conjdis_iniciar(int tamanho);
	void Conjdis_deletar(Conjdis **conj);

	int Conjdis_procurar(Conjdis *cd, int elem);
	void Conjdis_juntar(Conjdis *cd, int elem1, int elem2);

#endif
