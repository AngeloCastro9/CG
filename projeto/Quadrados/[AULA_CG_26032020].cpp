// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>
#include<time.h> 

typedef struct {
	float x;
	float y;
} wcPt2D;

wcPt2D dataPts[6];

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1700, 0, 800);
}

int square;

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	int begin = 0;
	int tamanho1 = 40;
	int tamanho2 = 50;
	int tamanho3 = 60;
	int x = 50;
	int y = 50;
	float color1 = 0.0;
	float color2 = 0.1;
	float color3 = 0.3;

	while (begin < square) {
		glPointSize(tamanho3);
		tamanho3 = tamanho3 + 10;
		glBegin(GL_POINTS);
		glColor3f(color1, color2, color3);
		color1 = color1 + 0.1;
		color2 = color2 + 0.1;
		color3 = color3 + 0.1;
		glVertex2i(x, y);
		x = x + 70;
		y = y + 70;
		glEnd();
		begin++;
	}
	
	glFlush();
}

int main(int argc, char** argv)
{
	std::cout << "Informe a quantidade de quadrados:";
	std::cin >> square;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Capitulo 5");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}