/*
 * mensagens.c
 *
 *  Created on: 23/07/2010
 *      Author: bruno
 */

#include <gtk/gtk.h>

#include "Header/mensagens.h"

void Mensagem_generica(GtkMessageType gtkTipo, void (*fsim)(), void (*fnao)(), gchar *titulo, gchar *mesg) {
  GtkButtonsType botao=(gtkTipo == GTK_MESSAGE_QUESTION)? GTK_BUTTONS_YES_NO:GTK_BUTTONS_OK;

  GtkWidget *mesgWid=gtk_message_dialog_new(NULL,GTK_DIALOG_MODAL, gtkTipo, botao,"%s", mesg);
  gtk_window_set_title(GTK_WINDOW(mesgWid), titulo);
  gtk_window_set_position(GTK_WINDOW(mesgWid), GTK_WIN_POS_CENTER_ON_PARENT);
  gint result=gtk_dialog_run(GTK_DIALOG (mesgWid));
  gtk_widget_destroy(mesgWid);

  if ((result == GTK_RESPONSE_YES) && (fsim))
    fsim();
  else if ((result == GTK_RESPONSE_NO) && (fnao))
    fnao();
}

void Mensagem(TipoMensagem tipo, gchar *titulo, gchar *mesg, ...) {
  GtkMessageType gtkTipo;
  gchar mesgF[256];

  va_list ap;

  if (mesg == NULL) return;

  va_start(ap, mesg);
  vsprintf(mesgF, mesg, ap);
  va_end(ap);

  if (tipo == MENSAGEM_AVISO)
     gtkTipo=GTK_MESSAGE_WARNING;
   else if (tipo == MENSAGEM_INFORMACAO)
     gtkTipo=GTK_MESSAGE_INFO;
   else
     gtkTipo=GTK_MESSAGE_ERROR;

  Mensagem_generica(gtkTipo, NULL, NULL, titulo, mesgF);
}

void Pergunta(void (*fsim)(), void (*fnao)() , gchar *titulo, gchar *mesg, ...) {
  gchar mesgF[256];

  va_list ap;

  if (mesg == NULL) return;

  va_start(ap, mesg);
  vsprintf(mesgF, mesg, ap);
  va_end(ap);

  Mensagem_generica(GTK_MESSAGE_QUESTION,fsim,fnao, titulo, mesgF);
}
