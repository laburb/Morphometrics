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
 * mensagens.h
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#ifndef MENSAGENS_H_
#define MENSAGENS_H_

  typedef enum {
    MENSAGEM_INFORMACAO,
    MENSAGEM_AVISO,
    MENSAGEM_ERRO,
    MENSAGEM_ERRO_CRITICO
  } TipoMensagem;

  void Mensagem(TipoMensagem tipo, char *titulo, char *mesg, ...);
  void Pergunta(void (*fsim)(), void (*fnao)() , char *titulo, char *mesg, ...);

#endif /* MENSAGENS_H_ */
