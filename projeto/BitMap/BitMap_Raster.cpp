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

	int k;
	glRasterPos2i(140, 240);
	for (k = 1; k < 2; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, k + 64);
	};

	glRasterPos2i(190, 300);
	for (k = 14; k < 15; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, k + 64);
	};

	glRasterPos2i(240, 240);
	for (k = 7; k < 8; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, k + 64);
	};

	glRasterPos2i(190, 180);
	for (k = 5; k < 6; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, k + 64);
	};
	
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