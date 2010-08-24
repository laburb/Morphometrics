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

  void convertToUpperCase(char *str);

#endif /* UTIL_H_ */
