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

	GLubyte bitShape[22] = {
		0xe7, 0x00,
		0xe7, 0x00,
		0xe7, 0x00,
		0xff, 0x00,
		0xff, 0x00,
		0xe7, 0x80,
		0xe7, 0x00,
		0xe7, 0x00,
		0xff, 0x00,
		0xff, 0x00,
	};
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glRasterPos2i(640, 360);

	glBitmap(16, 11, 10.0, 10.0, 15.0, 15.0, bitShape);

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