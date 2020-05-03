// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>	
#include <thread>

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);
}

void newPoint() {
	glColor3f(0, 0.4, 0.2);
	glPointSize(35);
	glBegin(GL_POINTS);
	glVertex2i(100, 100);
	glEnd();
	glFlush();
}

void oldPoint() {
	glColor3f(0, 0, 0);
	glPointSize(35);
	glBegin(GL_POINTS);
	glVertex2i(100, 100);
	glEnd();
	glFlush();
}

void translate(int x, int y) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
}

void display(void) {
	int a = 10.0f;
	int b = 10.0f;
	int x = 10.0f;
	int y = 10.0f;

	while (true) {
		newPoint();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		oldPoint();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		translate(x, y);

		if (a != 600) {
			x = x + 10.0f;
			a = a + 10.0f;
		}
		else if (x > 10) {
			x = x - 10.0f;
			if (x == 10.0f) {
				a = 10.0f;
			}
		}
		if (b != 600) {
			y = y + 10.0f;
			b = b + 10.0f;
		}
		else if (y > 10) {
			y = y - 10.0f;
			if (y == 10.0f) {
				b = 10.0f;
			}
		}

		glEnd();
		glFlush();
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Hello Word!");
	init();
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}