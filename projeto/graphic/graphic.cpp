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
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600.0, 0, 500.0);
}

void lineGraph(void) {
	GLint month, k;
	GLint x = 30;
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 12; k++) {
		if (dataValue[k] < 200) {
			glColor3f(0.0, 1.0, 0.0);
		}
		if (dataValue[k] > 200 && dataValue[k] < 300) {
			glColor3f(1.0, 1.0, 0.0);
		}
		if (dataValue[k] > 300) {
			glColor3f(1.0, 0.0, 0.0);
		}
		glVertex2i(x + k * 50, dataValue[k] - 4);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0); 
	for (k = 0; k < 12; k++) {
		glRasterPos2i(xRaster + k * 50, dataValue[k] - 4);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	};

	glColor3f(1.0, 1.0, 1.0);
	xRaster = 20;
	for (month = 0; month < 12; month++) {
		glRasterPos2i(xRaster, yRaster);
		for (k = 3 * month; k < 3 * month + 3; k++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
		xRaster += 50;
	};

	glFlush();
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Testando Reshape");
	init();
	glutDisplayFunc(lineGraph);
	glutMainLoop();

	return 0;
}