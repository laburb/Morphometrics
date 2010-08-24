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
 * editar.h
 *
 *  Created on: 11/08/2010
 *      Author: bruno
 */

#ifndef EDITAR_H_
#define EDITAR_H_

  enum TipoFerramenta {
    FERRAMENTA_NAVEGAR,
    FERRAMENTA_ADD_ENTIDADE,
    FERRAMENTA_ADD_TEXTO,
    FERRAMENTA_ADD_IMAGEM,
    FERRAMENTA_ZOOM_MAIS,
    FERRAMENTA_ZOOM_MENOS
  };

  enum TipoFerramenta ferramentaAtiva;

  void Editar_mouseMove(int x, int y, double mouseX, double mouseY);
  void Editar_mousePressiona(int botao, double mouseX, double mouseY);
  void Editar_mouseLibera(int botao, double mouseX, double mouseY);

  void Editar_melhorVisao();

  GdkCursorType Mapa_cursor();


#endif /* EDITAR_H_ */
