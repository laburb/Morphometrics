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
