
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <time.h>


// Vari�veis para controles de navega��o
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

using namespace std;

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Desenha o objeto definido anteriormente: uma pir�mide
	//DesenhaObjetoWireframe(&piramide);
	// Base da pir�mide
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, -1); //canto inf esquerdo tras.
	glVertex3f(-1, 0, 1); //canto inf esquerdo diant.
	glVertex3f(1, 0, 1); //canto inf direito  diant.
	glVertex3f(1, 0, -1); //canfo inf direito  tras.
	glEnd();
	// Face 1 - ok
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 0, 1); //canto inf direito  diant.
	glVertex3f(1, 2, 1); //topo
	glEnd();
	// Face 2 - ok
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, 1);  //canto inf direito  diant.
	glVertex3f(-1, 2, 1);  //topo
	glEnd();
	// Face 3
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 0, -1);  //canfo inf direito  tras.
	glVertex3f(1, 2, -1);  //topo
	glEnd();

	// Face 4
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, -1);  //canfo inf direito  tras.
	glVertex3f(-1, 2, -1);  //topo
	glEnd();

	// Face 5 - ok
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 2, -1); //canto inf esquerdo tras.
	glVertex3f(-1, 2, 1); //canto inf esquerdo diant.
	glVertex3f(1, 2, 1); //canto inf direito  diant.
	glVertex3f(1, 2, -1); //canfo inf direito  tras.
	glEnd();
	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o usada para especificar a posi��o do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	// Posiciona e orienta o observador
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
}

// Fun��o usada para especificar o volume de visualiza��o
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva(angulo,aspecto,zMin,zMax)
	// Angle - Especifica o �ngulo de visualiza��o, em graus, na dire��o Y. 
	// Quanto maior for o valor, maior ser� o campo de vis�o.
	// fAspect - � a propor��o das coordenadas da figura na dire��o X. Define
	// propor��o (raz�o) entre a altura e largura.
	// Terceiro par�metro - dist�ncia do observador at� o plano frontal
	// Quarto par�metro - dist�ncia do observador at� o plano traseiro
	gluPerspective(angle, fAspect, 0.1, 1200);

	PosicionaObservador();
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica as dimens�es da viewport
	glViewport(0, 0, w, h);

	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun��o callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado(unsigned char tecla, int x, int y)
{
	if (tecla == 27) // ESC ?
	{
		// Libera mem�ria e finaliza programa
		exit(0);
	}
}

// Fun��o callback para tratar eventos de teclas especiais
void TeclasEspeciais(int tecla, int x, int y)
{
	switch (tecla)
	{
	case GLUT_KEY_HOME:	if (angle >= 10)  angle -= 5;
		break;
	case GLUT_KEY_END:	if (angle <= 150) angle += 5;
		break;
	case GLUT_KEY_UP:
		fAspect = fAspect + 0.01;
		break;
	case GLUT_KEY_DOWN:
		fAspect = fAspect - 0.01;
		break;
	case GLUT_KEY_RIGHT:
		obsX = obsX + 0.1;
		obsY = obsY + 0.1;
		break;

	case GLUT_KEY_LEFT:
		obsX = obsX - 0.1;
		obsY = obsY - 0.1;

		break;
	};
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();


}

// Fun��o callback para eventos de bot�es do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Salva os par�metros atuais
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

// Fun��o callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0
void GerenciaMovim(int x, int y)
{
	// Bot�o esquerdo ?
	if (bot == GLUT_LEFT_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica �ngulos
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}
	// Bot�o direito ?
	else if (bot == GLUT_RIGHT_BUTTON)
	{
		// Calcula diferen�a
		int deltaz = y_ini - y;
		// E modifica dist�ncia do observador
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}
	// Bot�o do meio ?
	else if (bot == GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferen�as
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posi��es
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualiza��o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a vari�vel que especifica o �ngulo da proje��o
	// perspectiva
	angle = 60;

	// Inicializa as vari�veis usadas para alterar a posi��o do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 5;
}

// Programa Principal 
int main(void)
{
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Desenho do wireframe de uma pir�mide");

	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);

	// Registra a fun��o callback de redimensionamento da janela de visualiza��o
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(GerenciaMouse);

	// Registra a fun��o callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a fun��o callback para tratamento das teclas normais 
	glutKeyboardFunc(Teclado);

	// Registra a fun��o callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}	