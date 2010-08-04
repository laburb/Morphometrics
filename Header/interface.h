/*
 * interface.h
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

    GtkBuilder *builderPrincipal;

    void Interface_iniciar();
    void Interface_finalizar();

    GtkBuilder *Interface_carregarXML(char *arquivo);

    void Interface_mudarMouse(GdkWindow *windowT, GdkCursorType tipoMouse);

#endif /* INTERFACE_H_ */
