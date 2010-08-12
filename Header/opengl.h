/*
 * opengl.h
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#ifndef OPENGL_H_
#define OPENGL_H_

    void Opengl_iniciar(int w, int h);
    void Opengl_redimencionar(int w, int h);
    void Opengl_configTela(int w, int h);

    void Opengl_desenha();
    void Opengl_atualizar();

    void DrawLineXOR(double x1, double y1, double x2, double y2);
    void DrawQuadradoXOR(double x1, double y1, double x2, double y2);

    char openglDesenharAtivo;

#endif /* OPENGL_H_ */
