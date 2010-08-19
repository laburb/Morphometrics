/*
 * acessibilidade.h
 *
 *  Created on: 16/08/2010
 *      Author: bruno
 */

#ifndef ACESSIBILIDADE_H_
#define ACESSIBILIDADE_H_

  enum TipoAcessibilidade {
    ACESS_GEOMETRICA=1,
    ACESS_TOPOLOGICA
  };

  void Acessibilidade_calcular(enum TipoAcessibilidade tipoAcess);

#endif /* ACESSIBILIDADE_H_ */
