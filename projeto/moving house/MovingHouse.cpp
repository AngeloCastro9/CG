
#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>
#include <ctime>
#include <stdlib.h>

using namespace std;
int OffsetX = 0, OffsetY = 0;
float R = 0, G = 0, B = 1;
GLint V = 0, Ang = 0;
bool signal = true;

void init(void) {
	
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-400, 400, -400, 400);
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(R, G, B);
	
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, -400);
	glVertex2i(0, 400);
	glVertex2i(-400, 0);
	glVertex2i(400, 0);
	glEnd();
	
	glColor3f(0,0,1);
	glLoadIdentity();
	cout << Ang << endl;
	glRotatef(Ang, 0.0, 0.0, 1.0); 
	glRecti(100, 0, 50, 50);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(100, 50);
	glVertex2f(50, 50);
	glVertex2f(75, 75);
	glEnd();

	glFlush();
}

void Teclado(unsigned char key, int x, int y)
{
	if (key == 13) {
		if (signal == true) {
			signal = false;
		}
		else {
			signal = true;
		}
	}
}

void Anima(int value)
{
	if (signal == true) {
		Ang = Ang + 10;
	}
	else {
		Ang = Ang - 10;
	}
	if (Ang == 360 || Ang == -360) { Ang = 0; }
	glutPostRedisplay();
	glutTimerFunc(800, Anima, 1);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	
	glutCreateWindow("Hello Word!");
	
	init();
	
	glutDisplayFunc(lineSegment);
	glutTimerFunc(V, Anima, 1);
	glutKeyboardFunc(Teclado);
	glutMainLoop();

	return 0;

}