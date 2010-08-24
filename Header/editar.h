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
