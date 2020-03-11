// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);

}

void point(void) {

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0, 0.4, 0.2);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

;	glBegin(GL_POLYGON);
	int wTamPad = 250;
	GLint k;

	for (k = 0; k < 40; k++) {
		double theta = 3.14159265359 * k / 39;
		glVertex2i(640 + wTamPad * cos(theta),
			360 + wTamPad * sin(theta));
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Hello Word!");
	init();

	glutDisplayFunc(point);

	glutMainLoop();

	return 0;
}