/*
 * editar.c
 *
 *  Created on: 11/08/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <math.h>

#include "Header/interface.h"
#include "Header/opengl.h"
#include "Header/grafo.h"
#include "Header/mapa.h"
#include "Header/editar.h"

enum TipoFerramenta ferramentaAtiva=FERRAMENTA_NAVEGAR;
enum TipoFerramenta ferramentaAnt=FERRAMENTA_NAVEGAR;

static char mapaClickAdd=0;
static Ponto mouseClick;
static Ponto mouseClickAnt={-999,-999};

/**
 * Seta a melhor visão do mapa.
 */

void Editar_melhorVisao() {
  Mapa_calculaEixoMax();
  Mapa_setVisao(mapa.eixoMinimo, mapa.eixoMaximo);

  Interface_atualizaOpengl();
}

/**
 * Da zoom na mapa e centraliza apartir do mouse.
 *
 * @param ampliar Se 1 amplia\nSe -1 reduz
 * @param mouseX Posição x do mouse no mapa
 * @param mouseY Posição y do mouse no mapa
 *
 */

static void Editar_zoom(int ampliar, double mouseX, double mouseY) {
  double visaoW=mapa.visaoMaximo.x-mapa.visaoMinimo.x;
  double visaoH=mapa.visaoMaximo.y-mapa.visaoMinimo.y;

  double deslocX=(mouseX-visaoW/2)-mapa.visaoMinimo.x;
  double deslocY=(mouseY-visaoH/2)-mapa.visaoMinimo.y;

  double zoomX=visaoW*0.20*ampliar;
  double zoomY=visaoH*0.20*ampliar;


  Ponto viMin={mapa.visaoMinimo.x+zoomX+deslocX, mapa.visaoMinimo.y+zoomY+deslocY};
  Ponto viMax={mapa.visaoMaximo.x-zoomX+deslocX, mapa.visaoMaximo.y-zoomY+deslocY};

  Mapa_setVisao(viMin, viMax);

  Interface_atualizaOpengl();
}

/**
 * Verifica se o zoom é normal ou é para mostra a area delimitada pelo retangulo.
 */
static int Editar_verifZoomAmpliar(double x, double x2, double y, double y2) {
  double visaoW=mapa.visaoMaximo.x-mapa.visaoMinimo.x;
  double visaoH=mapa.visaoMaximo.y-mapa.visaoMinimo.y;
  double entradaW=fabs(x2-x);
  double entradaH=fabs(y2-y);

  if ((entradaW*100/visaoW >= 1) && (entradaH*100/visaoH >= 1))
    return 0;

  return 1;
}

/**
 * Desloca a visão do mapa.
 */

static void Editar_moverMapa(double deslocX, double deslocY) {
  Ponto viMin={mapa.visaoMinimo.x-deslocX, mapa.visaoMinimo.y-deslocY};
  Ponto viMax={mapa.visaoMaximo.x-deslocX, mapa.visaoMaximo.y-deslocY};

  Mapa_setVisao(viMin, viMax);
}

/**
 * Função chamada quando o mouse é movido.
 *
 * @param mouseX Posição x do mouse no mapa
 * @param mouseY Posição y do mouse no mapa
 *
 */

void Editar_mouseMove(double mouseX, double mouseY) {
  if (mapaClickAdd) {
    if (ferramentaAtiva == FERRAMENTA_NAVEGAR) {
      if (mouseClickAnt.x != -999) {
        Editar_moverMapa(mouseX-mouseClickAnt.x,mouseY-mouseClickAnt.y);
        Interface_atualizaOpengl();

        mouseClickAnt.x=-999;
        return;
      }
    }
    else if (ferramentaAtiva == FERRAMENTA_ADD_ENTIDADE) {

      DrawLineXOR(mouseClick.x,mouseClick.y,mouseX,mouseY);

      if (mouseClickAnt.x != -999)
        DrawLineXOR(mouseClick.x,mouseClick.y,mouseClickAnt.x,mouseClickAnt.y);

      Interface_atualizaOpengl();
    }
    else if (ferramentaAtiva == FERRAMENTA_ZOOM_MAIS) {
      DrawQuadradoXOR(mouseClick.x,mouseClick.y,mouseX,mouseY);

      if (mouseClickAnt.x != -999)
        DrawQuadradoXOR(mouseClick.x,mouseClick.y,mouseClickAnt.x,mouseClickAnt.y);

      Interface_atualizaOpengl();
    }

    mouseClickAnt.x=mouseX;
    mouseClickAnt.y=mouseY;
  }
}

/**
 * Função chamada quando o mouse é pressionado.
 *
 * @param botao Botão do mouse pressionado
 * @param mouseX Posição x do mouse no mapa
 * @param mouseY Posição y do mouse no mapa
 *
 */

void Editar_mousePressiona(int botao, double mouseX, double mouseY) {
  if (botao == 1) {
    if (ferramentaAtiva == FERRAMENTA_NAVEGAR)
      Interface_mudarMouse(GDK_FLEUR);
    else if ((ferramentaAtiva == FERRAMENTA_ADD_ENTIDADE) || (ferramentaAtiva == FERRAMENTA_ZOOM_MAIS)) {
      mouseClick.x=mouseX;
      mouseClick.y=mouseY;

      openglDesenharAtivo=0;
    }

    mapaClickAdd=1;
  }
  else if (botao == 2) {
    ferramentaAnt=ferramentaAtiva;
    ferramentaAtiva=FERRAMENTA_NAVEGAR;
    Interface_mudarMouse(GDK_FLEUR);
    mapaClickAdd=1;
  }
}

/**
 * Função chamada quando o mouse é liberado.
 *
 * @param botao Botão do mouse liberado
 * @param mouseX Posição x do mouse no mapa
 * @param mouseY Posição y do mouse no mapa
 *
 */

void Editar_mouseLibera(int botao, double mouseX, double mouseY) {
  if (botao == 1) {
    Interface_mudarMouse(Mapa_cursor());

    if (ferramentaAtiva == FERRAMENTA_ADD_ENTIDADE) {
      Nodo *nodoAtual=Grafo_adicionarNodo(mapa.grafo, ENTIDADE_LINE);
      Line *line=(Line *) nodoAtual->d;
      line->p1.x=mouseClick.x;
      line->p1.y=mouseClick.y;
      line->p2.x=mouseX;
      line->p2.y=mouseY;

      openglDesenharAtivo=1;

      Interface_atualizaOpengl();
    }
    if (ferramentaAtiva == FERRAMENTA_ZOOM_MAIS) {
      if (Editar_verifZoomAmpliar(mouseClick.x,mouseX,mouseClick.y,mouseY))
        Editar_zoom(1,mouseX, mouseY);
      else {
        Ponto visMin={MIN(mouseClick.x,mouseX), MIN(mouseClick.y,mouseY)};
        Ponto visMax={MAX(mouseClick.x,mouseX), MAX(mouseClick.y,mouseY)};

        Mapa_setVisao(visMin, visMax);
      }

      openglDesenharAtivo=1;

      Interface_atualizaOpengl();
    }
    if (ferramentaAtiva == FERRAMENTA_ZOOM_MENOS)
      Editar_zoom(-1,mouseX, mouseY);

    mouseClickAnt.x=-999;
    mapaClickAdd=0;
  }
  else if (botao == 2) {
    ferramentaAtiva=ferramentaAnt;
    Interface_mudarMouse(Mapa_cursor());
    mapaClickAdd=0;
    mouseClickAnt.x=-999;
  }
}

/**
 * Verifica qual cursor deve ser usado.
 *
 * @return Retorna o curso ideal
 *
 */
GdkCursorType Mapa_cursor() {
  if (ferramentaAtiva == FERRAMENTA_NAVEGAR) return GDK_HAND1;
  else if (ferramentaAtiva == FERRAMENTA_ADD_ENTIDADE) return GDK_CROSS;
  else if (ferramentaAtiva == FERRAMENTA_ADD_IMAGEM) return GDK_CROSS;
  else if (ferramentaAtiva == FERRAMENTA_ADD_TEXTO) return GDK_XTERM;

  return GDK_ARROW;
}
