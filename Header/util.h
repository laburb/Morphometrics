/*
 * util.h
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#ifndef UTIL_H_
#define UTIL_H_
  #include <stdio.h>

  #define forList(Tipo, Var, primListaPer) \
    Tipo Var=NULL; \
    Lista *Var##Percorre; \
    int Var##_Id; \
    for (Var##Percorre=primListaPer; (Var##Percorre!=NULL) && (Var = (Tipo) Var##Percorre->d) && (Var##_Id = Var##Percorre->id); Var##Percorre=Var##Percorre->prox)

  int Arquivo_acharString(FILE *fp, char *str, int inicio);

#endif /* UTIL_H_ */
