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
 * ponto.c
 *
 *  Created on: 05/08/2010
 *      Author: bruno
 */

#include "Header/ponto.h"

Ponto Ponto_menos(Ponto p1, Ponto p2) {
  Ponto ret;
  ret.x=p1.x-p2.x;
  ret.y=p1.y-p2.y;

  return ret;
}

Ponto Ponto_mais(Ponto p1, Ponto p2) {
  Ponto ret;
  ret.x=p1.x+p2.x;
  ret.y=p1.y+p2.y;

  return ret;
}

void Ponto_vezes(Ponto *pt, double vezes) {
  pt->x*=vezes;
  pt->y*=vezes;
}
