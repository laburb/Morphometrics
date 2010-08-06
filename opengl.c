/*
 * opengl.c
 *
 *  Created on: 24/07/2010
 *      Author: bruno
 */

#include <GL/gl.h>
#include <GL/glu.h>

#include "Header/opengl.h"

static GLfloat rtri, rquad;

/**
 *  Incializa o opengl
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_iniciar(int w, int h) {
  /* Height / width ration */
  GLfloat ratio;

  /* Protect against a divide by zero */
  if (h == 0)
    h = 1;

  ratio = (GLfloat) w / (GLfloat) h;

  /* Setup our viewport. */
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);

  /* change to the projection matrix and set our viewing volume. */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* Set our perspective */
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);

  /* Make sure we're chaning the model view and not the projection */
  glMatrixMode(GL_MODELVIEW);

  /* Reset The View */
  glLoadIdentity();

  glShadeModel(GL_SMOOTH);

  /* Set the background black */
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

  /* Depth buffer setup */
  glClearDepth(1.0f);

  /* Enables Depth Testing */
  glEnable(GL_DEPTH_TEST);

  /* The Type Of Depth Test To Do */
  glDepthFunc(GL_LEQUAL);

  /* Really Nice Perspective Calculations */
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

/**
 *  Função chamada quando a tela é redimencionada
 *
 *  @param w Largura
 *  @param h Altura
 *
 */

void Opengl_redimencionar(int w, int h) {
  glViewport(0, 0, w, h);
}

/**
 *  Desenha
 */

void Opengl_desenha() {
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  /* Move Left 1.5 Units And Into The Screen 6.0 */
  glLoadIdentity();
  glTranslatef( -1.5f, 0.0f, -6.0f );

  /* Rotate The Triangle On The Y axis ( NEW ) */
  glRotatef( rtri, 0.0f, 1.0f, 0.0f );

  glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
    glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
    glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Front)       */
    glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
    glVertex3f( -1.0f, -1.0f,  1.0f ); /* Left Of Triangle (Front)      */
    glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
    glVertex3f(  1.0f, -1.0f,  1.0f ); /* Right Of Triangle (Front)     */

    glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
    glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Right)       */
    glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
    glVertex3f(  1.0f, -1.0f,  1.0f ); /* Left Of Triangle (Right)      */
    glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
    glVertex3f(  1.0f, -1.0f, -1.0f ); /* Right Of Triangle (Right)     */

    glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
    glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Back)        */
    glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
    glVertex3f(  1.0f, -1.0f, -1.0f ); /* Left Of Triangle (Back)       */
    glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
    glVertex3f( -1.0f, -1.0f, -1.0f ); /* Right Of Triangle (Back)      */

    glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
    glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle (Left)        */
    glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
    glVertex3f( -1.0f, -1.0f, -1.0f ); /* Left Of Triangle (Left)       */
    glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
    glVertex3f( -1.0f, -1.0f,  1.0f ); /* Right Of Triangle (Left)      */
  glEnd( );                            /* Finished Drawing The Triangle */

  /* Move Right 3 Units */
  glLoadIdentity( );
  glTranslatef( 1.5f, 0.0f, -6.0f );

  /* Rotate The Quad On The X axis ( NEW ) */
  glRotatef( rquad, 1.0f, 0.0f, 0.0f );

  /* Set The Color To Blue One Time Only */
  glColor3f( 0.5f, 0.5f, 1.0f);

  glBegin( GL_QUADS );                 /* Draw A Quad                      */
    glColor3f(   0.0f,  1.0f,  0.0f ); /* Set The Color To Green           */
    glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Top)      */
    glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Top)       */
    glVertex3f( -1.0f,  1.0f,  1.0f ); /* Bottom Left Of The Quad (Top)    */
    glVertex3f(  1.0f,  1.0f,  1.0f ); /* Bottom Right Of The Quad (Top)   */

    glColor3f(   1.0f,  0.5f,  0.0f ); /* Set The Color To Orange          */
    glVertex3f(  1.0f, -1.0f,  1.0f ); /* Top Right Of The Quad (Botm)     */
    glVertex3f( -1.0f, -1.0f,  1.0f ); /* Top Left Of The Quad (Botm)      */
    glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Botm)   */
    glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Botm)  */

    glColor3f(   1.0f,  0.0f,  0.0f ); /* Set The Color To Red             */
    glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Front)    */
    glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Front)     */
    glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Front)  */
    glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Front) */

    glColor3f(   1.0f,  1.0f,  0.0f ); /* Set The Color To Yellow          */
    glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Back)   */
    glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Back)  */
    glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Back)     */
    glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Back)      */

    glColor3f(   0.0f,  0.0f,  1.0f ); /* Set The Color To Blue            */
    glVertex3f( -1.0f,  1.0f,  1.0f ); /* Top Right Of The Quad (Left)     */
    glVertex3f( -1.0f,  1.0f, -1.0f ); /* Top Left Of The Quad (Left)      */
    glVertex3f( -1.0f, -1.0f, -1.0f ); /* Bottom Left Of The Quad (Left)   */
    glVertex3f( -1.0f, -1.0f,  1.0f ); /* Bottom Right Of The Quad (Left)  */

    glColor3f(   1.0f,  0.0f,  1.0f ); /* Set The Color To Violet          */
    glVertex3f(  1.0f,  1.0f, -1.0f ); /* Top Right Of The Quad (Right)    */
    glVertex3f(  1.0f,  1.0f,  1.0f ); /* Top Left Of The Quad (Right)     */
    glVertex3f(  1.0f, -1.0f,  1.0f ); /* Bottom Left Of The Quad (Right)  */
    glVertex3f(  1.0f, -1.0f, -1.0f ); /* Bottom Right Of The Quad (Right) */
  glEnd( );                            /* Done Drawing The Quad            */
}

void Opengl_atualizar() {
  /* Increase The Rotation Variable For The Triangle ( NEW ) */
  rtri += 0.2f;
  /* Decrease The Rotation Variable For The Quad     ( NEW ) */
  rquad -= 0.15f;
}
