/*
 * GL2PS, an OpenGL to PostScript Printing Library
 * Copyright (C) 1999-2003  Christophe Geuzaine 
 *
 * $Id: gl2psTest.c,v 1.7 2003-01-22 04:24:19 geuzaine Exp $
 *
 * E-mail: geuz@geuz.org
 * URL: http://www.geuz.org/gl2ps/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

/*
  Original author: Rouben Rostamian <rostamian@umbc.edu>

  To compile on a Linux system, type:

  gcc -O3 gl2psTest.c gl2ps.c -lglut -lGLU -lGL -L/usr/X11R6/lib -lX11 -lm
*/

#include <GL/glut.h>
#include <stdlib.h>
#include "gl2ps.h"

void init(void){
  float pos[3] = {0.,0.,1000.};

  glClearColor(0., 0., 0., 0.);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);
  glEnable(GL_LIGHT0);
}

void triangles(void){
  glDisable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);
  
  glColor3f(1., 0., 0.);
  glVertex3f(-1., 1., 0.);
  glColor3f(1., 1., 0.);
  glVertex3f(-1., 0., 0.);
  glColor3f(1., 0., 1.);
  glVertex3f(1., 0., 0.2);
  
  glColor3f(0., 1., 0.);
  glVertex3f(1., 0., 0.);
  glColor3f(0., 1., 1.);
  glVertex3f(1., 0.5, 0.);
  glColor3f(0., 1., 1.);
  glVertex3f(-1., 0.5, 0.1);
  
  glEnd();
}

static float rotation = 0.;

void teapot(void){
  glEnable(GL_LIGHTING);
  glPushMatrix();
  glRotatef(rotation, 2., 0., 1.);
  glutSolidTeapot(0.6);
  glPopMatrix();
}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  triangles();
  teapot();
  glFlush();
}

void reshape(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.1,1.1, -1.1,1.1, -1.1,1.1);
  glMatrixMode(GL_MODELVIEW);
}

void writeps(int format, int sort, int options, int nbcol, char *file){
  FILE *fp;
  int state = GL2PS_OVERFLOW;
  int bufsize = 0;
 
  fp = fopen(file, "w");

  if(!fp){
    printf("Unable to open file %s for writing\n", file);
    exit(1);
  }

  printf("Saving image to file %s... ", file);
  fflush(stdout);

  while(state == GL2PS_OVERFLOW){
    gl2psBeginPage(file, "test", format, sort, options, GL_RGBA, 0, NULL,
		   bufsize, fp, file);
    if(nbcol) gl2psNumShadeColors(nbcol,nbcol,nbcol);
    display();
    state = gl2psEndPage();
  }

  fclose(fp);

  printf("Done!\n");
  fflush(stdout);
}

void keyboard(unsigned char key, int x, int y){
  int opt;

  switch(key){
  case 27:
  case 'q':
    exit(0);
    break;
  case 'w':
    opt = 0;
    writeps(GL2PS_EPS, GL2PS_SIMPLE_SORT, opt, 0, "outSimple.eps");

    opt = GL2PS_OCCLUSION_CULL;
    writeps(GL2PS_EPS, GL2PS_SIMPLE_SORT, opt, 0, "outSimpleCulled.eps");

    opt = GL2PS_NO_PS3_SHADING;
    writeps(GL2PS_EPS, GL2PS_SIMPLE_SORT, opt, 2, "outSimpleShading2.eps");
    writeps(GL2PS_EPS, GL2PS_SIMPLE_SORT, opt, 8, "outSimpleShading7.eps");
    writeps(GL2PS_EPS, GL2PS_SIMPLE_SORT, opt, 16, "outSimpleShading16.eps");

    opt = GL2PS_BEST_ROOT | GL2PS_SILENT;
    writeps(GL2PS_EPS, GL2PS_BSP_SORT, opt, 0, "outBsp.eps");

    opt = GL2PS_OCCLUSION_CULL | GL2PS_BEST_ROOT | GL2PS_SILENT;
    writeps(GL2PS_EPS, GL2PS_BSP_SORT, opt, 0, "outBspCulled.eps");

    printf("Done with all images\n");
    break;
  }
}

void motion(int x, int y){
  rotation += 10.;
  display();
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMotionFunc(motion);
  
  printf("Press:\n");
  printf("  w: to save images\n");
  printf("  q: to quit\n");
  printf("Move the mouse to rotate the teapot\n");
  
  glutMainLoop();
  return 0;
}
