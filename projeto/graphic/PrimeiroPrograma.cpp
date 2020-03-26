//

#include<GLFW/glut.h>

// Tamanho inicial da janela 
GLsizei winWidth = 600, winHeight = 500;
// Posição raster inicial
GLint xRaster = 25, yRaster = 150;

GLubyte label[36] = { 'J','a', 'n',		'F', 'e', 'v',	'M' , 'a', 'r',
					  'A','b', 'r',		'M', 'a', 'i',  'J' , 'u', 'n',
					  'J','u', 'l',		'A', 'g', 'o',  'S', 'e', 't',
					  'O','u', 't',		'N', 'o', 'v',  'D', 'e', 'z' };

GLint dataValue[12]{ 420, 342, 324, 310, 262, 185,
					  190, 196, 217, 240, 312, 438 };

void init(void) {

	// Três primeiros argumentos corresponde a valores normalizados de R, G e B. O último parâmetro
	// é o "alpha value" que é utilzado para "blend operations", ou seja, determinar a cor resultand de dois
	// objetos que se sobrepõem.
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	// Carrega a matriz identidade para como matriz de projeção. para garantir que a definição das coordenadas
	// a ser realizada em gluOrtho2D não considerarão sujeiras.
	glLoadIdentity();
	gluOrtho2D(0, 600.0, 0, 500.0);
}

void lineGraph(void) {
	GLint month, k;
	//Posição x inicial do gráfico
	GLint x = 30;
	// glClearColor atrubui uma cor à janela, mas não coloca a janela na tela. Para tal, deve-se executar
	// o comando abaixo. O parâmetro GL_COLOR_BUFFER_BIT indica que os bits do "color buffer (refresh buffer)", devem 
	// ser setados para os valores indicados no comando glClearColor. Toda vez que a janela precisar ser
	// redesenhada, quando for modificada sua posição, por exemplo, o glClear deve ser executado. Se colocar
	// no procedimento "Init" isso não ocorrerá e, ao modificar a posição da janela, ela ficará preta.
	glClear(GL_COLOR_BUFFER_BIT);
	// Configura esquema de cor para os objetos que se que mostrar em tela. No exemplo abaixo, deseja-se 
	// setar a cor do objeto para vermelho. o "f" indica que são valore de ponto flutuande ("float")
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 12; k++) {
		glVertex2i(x + k * 50, dataValue[k] - 4);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0); // Set marker color to red.
	for (k = 0; k < 12; k++) { // Plot data as asterisk polymarkers.
		glRasterPos2i(xRaster + k * 50, dataValue[k] - 4);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	};

	glColor3f(0.0, 0.0, 0.0); // Set text color to black.
	xRaster = 20; // Display chart labels.
	for (month = 0; month < 12; month++) {
		glRasterPos2i(xRaster, yRaster);
		for (k = 3 * month; k < 3 * month + 3; k++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
		xRaster += 50;
	};

	glFlush();
}

// Programa Principal 

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	// Inicializa GLUT. Parâmetros são opcionais.
	glutInit(&argc, argv);
	// Configurar opções para mostrar a janela. No caso abaixo, optou-se pelo "single refresh buffer" - GLUT_SINGLE, 
	// e queremos utilizar o sistema de cores RGB - GLUT_RGB. A "|" indica operação "OR". Contrapondo a "single refresh
	// buffer", pode-se ter "double refresh buffer" para animações.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Configura a posição inicial o "upper left-corner" da janela (acima e à esquerda)
	glutInitWindowPosition(100, 100);
	// Configura a largura, primeiro parâmetro, e a altura da janela. Após mostrar a janela na tela
	// é possível reposicioná-la e redimensioná-la.
	glutInitWindowSize(winWidth, winHeight);
	// Criar uma janela com um título
	glutCreateWindow("Testando Reshape");
	//Executa rotinas de inicialização
	init();
	// "display callback function" é a rotina que será chamada sempre que a janela precisar ser mostrada novamente. Isso pode
	// ocorrer, por exemplo, se o usuário mover a janela. Nesse caso, "regHexagon" será novamente chamado.
	glutDisplayFunc(lineGraph);
	// Deve ser a última função de seu código. Mostra o gráfico inicial e coloca o programa em um loop que 
	// avalia inputs do usuário, tipo uso do mouse ou do teclado. Nesse primeiro exemplo, não haverá interação,
	// então o programa mostrará a figura até que a janela seja fechada.
	//glutReshapeFunc(winReshapeFcn);
	//
	glutMainLoop();

	return 0;
}