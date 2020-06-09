
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <time.h>


// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

using namespace std;

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	// Altera a cor do desenho para preto
	glColor3f(0.0f, 0.0f, 0.0f);

	// Desenha o objeto definido anteriormente: uma pirâmide
	//DesenhaObjetoWireframe(&piramide);
	// Base da pirâmide
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

// Função usada para especificar a posição do observador virtual
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

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	// Angle - Especifica o ângulo de visualização, em graus, na direção Y. 
	// Quanto maior for o valor, maior será o campo de visão.
	// fAspect - É a proporção das coordenadas da figura na direção X. Define
	// proporção (razão) entre a altura e largura.
	// Terceiro parâmetro - distância do observador até o plano frontal
	// Quarto parâmetro - distância do observador até o plano traseiro
	gluPerspective(angle, fAspect, 0.1, 1200);

	PosicionaObservador();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto
	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado(unsigned char tecla, int x, int y)
{
	if (tecla == 27) // ESC ?
	{
		// Libera memória e finaliza programa
		exit(0);
	}
}

// Função callback para tratar eventos de teclas especiais
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

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Salva os parâmetros atuais
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

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo ?
	if (bot == GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}
	// Botão direito ?
	else if (bot == GLUT_RIGHT_BUTTON)
	{
		// Calcula diferença
		int deltaz = y_ini - y;
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}
	// Botão do meio ?
	else if (bot == GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa(void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle = 60;

	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 5;
}

// Programa Principal 
int main(void)
{
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho do wireframe de uma pirâmide");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc(Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}	