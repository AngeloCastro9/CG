#include <stdlib.h>
#include<GLFW/glut.h>
#include<math.h>
#include <iostream>

using namespace std;

struct Coordenada {
	float x;
	float y;
};

Coordenada coordenadas[6];

GLdouble theta;

int stars;

static void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);
}

void gerarContornoDaEstrela(GLsizei ladoPontaLateral, GLsizei tamanhoDaPonta) {
	// Cor do contorno da estrela
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glPolygonMode(GL_FRONT, GL_LINE);

	// Ponta nordeste
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glVertex2f(coordenadas[1].x + ladoPontaLateral, coordenadas[1].y);
	glEnd();

	// Ponta norte
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glVertex2f(coordenadas[2].x + (coordenadas[1].x - coordenadas[2].x) / 2, coordenadas[2].y + tamanhoDaPonta);
	glEnd();

	// Ponta noroeste
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glVertex2f(coordenadas[2].x - ladoPontaLateral, coordenadas[2].y);
	glEnd();

	// Ponta sudoeste
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glVertex2f(coordenadas[2].x - ladoPontaLateral, coordenadas[4].y);
	glEnd();

	// Ponta sul
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glVertex2f(coordenadas[4].x + (coordenadas[5].x - coordenadas[4].x) / 2, coordenadas[4].y - tamanhoDaPonta);
	glEnd();

	// Ponta sudeste
	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glVertex2f(coordenadas[5].x + ladoPontaLateral, coordenadas[5].y);
	glEnd();
}

void gerarEstrela(GLsizei ladoPontaLateral, GLsizei tamanhoDaPonta, GLuint wTamPad) {

	// Cor do polígono interno
	glColor3f((float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX);
	glPolygonMode(GL_FRONT, GL_FILL);

	// 	Carregar coordenadas e desenhar polígono interno
	glBegin(GL_POLYGON);
	int x = rand() % (160 - 1100) + 160;
	int y = rand() % (210 - 500) + 210;
	for (int k = 0; k < 6; k++) {
		theta = 6.2831853 * k / 6;
		coordenadas[k].x = x + wTamPad * cos(theta);
		coordenadas[k].y = y + wTamPad * sin(theta);

		// ponto para compor poligono
		glVertex2f(coordenadas[k].x, coordenadas[k].y);
	}
	glEnd();

	// Ponta nordeste
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glVertex2f(coordenadas[1].x + ladoPontaLateral, coordenadas[1].y);
	glEnd();

	// Ponta norte
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glVertex2f(coordenadas[2].x + (coordenadas[1].x - coordenadas[2].x) / 2, coordenadas[2].y + tamanhoDaPonta);
	glEnd();

	// Ponta noroeste
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glVertex2f(coordenadas[2].x - ladoPontaLateral, coordenadas[2].y);
	glEnd();

	// Ponta sudoeste
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glVertex2f(coordenadas[2].x - ladoPontaLateral, coordenadas[4].y);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glEnd();

	// Ponta sul
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glVertex2f(coordenadas[4].x + (coordenadas[5].x - coordenadas[4].x) / 2, coordenadas[4].y - tamanhoDaPonta);
	glEnd();

	// Ponta noroeste
	glBegin(GL_TRIANGLES);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glVertex2f(coordenadas[5].x + ladoPontaLateral, coordenadas[5].y);
	glEnd();

	// Chama a função que gere contornos
	gerarContornoDaEstrela(ladoPontaLateral, tamanhoDaPonta);

	glFlush();
}

void StarLoop() {
	int loop = 0;

	while (loop != stars) {
		GLuint wTamPad = rand() % (50 - 150) + 50;

		GLsizei tamanhoDaPonta = rand() % (50 - 150) + 50;

		// Tamanho da lateral horizontal das pontas nordeste, noroeste, sudeste e sudoeste.
		GLsizei ladoPontaLateral = sqrt(pow(tamanhoDaPonta, 2) + pow((coordenadas[1].x - coordenadas[2].x) / 2, 2));

		gerarEstrela(ladoPontaLateral, tamanhoDaPonta, wTamPad);
		loop++;
	}
}


int main(int argc, char** argv)
{
	std::cout << "Informe a quantidade de estrelas:";
	std::cin >> stars;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 780);
	glutCreateWindow("Exercicio estrela");
	init();
	glutDisplayFunc(StarLoop);
	glutMainLoop();

	return 0;
}