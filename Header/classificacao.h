/*
 * classificacao.h
 *
 *  Created on: 24/08/2010
 *      Author: bruno
 */

#ifndef CLASSIFICACAO_H_
#define CLASSIFICACAO_H_

  enum ClassificaoTipo {
    CLASS_NATURALBREAKS
  };

  enum ClassificaoTipo classificaoAtiva;

  void Classificacao(ArrayValor *valores);
#endif /* CLASSIFICACAO_H_ */
