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

#ifndef _HEAP_H_
#define _HEAP_H_

  typedef struct {
    int numElm;
    int tamanho;
    void **elm;

    int (*funcao)(void *, void *);
  } Heap;


  Heap *Heap_criar(void *funcao);
  void Heap_deletar(Heap *heap);

  void Heap_adicionar(Heap *heap, void *dado);
  void *Heap_remover(Heap *heap);
  int Heap_vazio(Heap *heap);
  void Heap_atualiza(Heap *heap, int posicao);

#endif
