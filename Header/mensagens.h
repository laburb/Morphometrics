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

  void Mensagem(TipoMensagem tipo, gchar *titulo, gchar *mesg, ...);
  void Pergunta(void (*fsim)(), void (*fnao)() , gchar *titulo, gchar *mesg, ...);

#endif /* MENSAGENS_H_ */
