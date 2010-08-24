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
 * interface.h
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#ifndef INTERFACE_H_
#define INTERFACE_H_

    #include <gtk/gtk.h>

    GtkWidget *drawOpengl;
    GtkWidget *frameProgresso;
    GtkProgressBar *progress;
    GtkLabel *labelPosicaoXY;

    GtkAdjustment *ajustScrollHorizGL;
    GtkAdjustment *ajustScrollVertGL;

    GtkToggleToolButton *tbAddEntidade;
    GtkToggleToolButton *tbAddImagem;
    GtkToggleToolButton *tbAddTexto;
    GtkToggleToolButton *tbAmpliar;
    GtkToggleToolButton *tbReduzir;

    GtkWidget *frameFerramentas;

    GtkComboBox *comboResultados;

    struct resultaInter {
      //Nome da tabela no banco de dados
      char *tabela;
      //Nome que ira aparecer na combobox
      char *nome;
      //Nome que ira aparecer na coluna resultado
      char *colResult;
      //Nome da coluna principal que ira ser usada para visualizacao
      char *colPrincipal;
      //Colunas viziveis
      gboolean colunasViziveis[5];
    };

    struct resultaInter listaResult[4];

    void Interface_iniciar();
    void Interface_finalizar();

    GtkBuilder *Interface_carregarXML(char *arquivo);

    void Interface_mudarMouse(GdkCursorType tipoMouse);

    void Interface_atualizaOpengl();

    void Interface_resultados();

#endif /* INTERFACE_H_ */
