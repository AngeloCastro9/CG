#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <GLFW/glut.h>
#include <Windows.h>

int b;
int qtdTriangles;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 200, 0, 200);

}
void lineSegment(void) {
	int i = 0;

	while (i != qtdTriangles) {
		glColor3f(0, 0.1, 0.6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_TRIANGLES);

		double d = sqrt((b * b) - pow(b / 2, 2));

		double x1 = 100 - b / 2;
		double y1 = 100 - d / 2;

		double x2 = 100 + b / 2;
		double y2 = y1;

		double x3 = 100;
		double y3 = d / 2 + 100;

		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);

		i++;
		b = b - 10;
	}

	glEnd();
	glFlush();
}

int main()
{
	std::cout << "Informe a quantidade de triangulos:";
	std::cin >> qtdTriangles;
	std::cout << "Informe o B:";
	std::cin >> b;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);

	glutCreateWindow("Hello Word!");


	init();

	glutDisplayFunc(lineSegment);

	glutMainLoop();

	return 0;
}





