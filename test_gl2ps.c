/*
gcc test_gl2ps.c gl2ps.c -lglut -lGLU -lGL -lX11 -lm -Wall -ansi -pedantic
*/

#include <GL/glut.h>
#include <stdlib.h>
#include "gl2ps.h"


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void triangle(void)
{
	glBegin(GL_TRIANGLES);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.2);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.5, 0.0);
	glVertex3f(0.0, 0.5, 0.1);

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	triangle();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.1,1.1, -0.1,1.1, -1.1,1.1);
	glMatrixMode(GL_MODELVIEW);
}

void write_with_gl2ps(void)
{
	FILE *fp;
	char *file = "zz.ps";
	int state = GL2PS_OVERFLOW;
	int bufsize = 0;

	if ((fp=fopen(file, "w"))==NULL) {
		fprintf(stderr, "unable to open file %s for writing\n", file);
		exit(1);
	}

	while (state == GL2PS_OVERFLOW) {
		gl2psBeginPage(
				file,
				"test",
				GL2PS_PS,
				GL2PS_BSP_SORT,
				GL2PS_DRAW_BACKGROUND,
				GL_RGBA, 0, NULL,
				bufsize, fp, file);
		display();
		state = gl2psEndPage();
	}

	fclose(fp);

	printf("image saved to file %s\n", file);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
	case 'q':
		exit(0);
		break;
	case 'w':
		write_with_gl2ps();
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	putchar('\n');
	printf("in the image window:\n");
	putchar('\n');
	printf("\tw: save image to postscript file\n");
	printf("\tq: quit\n");
	putchar('\n');

	glutMainLoop();
	return 0;
}
