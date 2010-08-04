/*
 * sinais.h
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#ifndef SINAIS_H_
#define SINAIS_H_

    void on_drawOpengl_realize(GtkWidget *widget, gpointer user_data);
    gboolean on_drawOpengl_expose_event(GtkWidget *widget, GdkEventExpose *event, gpointer user_data);
    gboolean on_drawOpengl_configure_event(GtkWidget *widget, GdkEventConfigure *event, gpointer user_data);

#endif /* SINAIS_H_ */
