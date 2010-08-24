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
 * Eixo.h
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#ifndef PONTO_H_
#define PONTO_H_

  typedef struct {
    double x;
    double y;
  } Ponto;

  Ponto Ponto_menos(Ponto p1, Ponto p2);
  Ponto Ponto_mais(Ponto p1, Ponto p2);
  void Ponto_vezes(Ponto *pt, double vezes);

#endif /* PONTO_H_ */
