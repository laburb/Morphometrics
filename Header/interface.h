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
