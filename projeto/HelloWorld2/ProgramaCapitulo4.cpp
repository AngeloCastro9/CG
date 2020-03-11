// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>

void init(void) {
	// Três primeiros argumentos corresponde a valores normalizados de R, G e B. O último parâmetro
	// é o "alpha value" que é utilzado para "blend operations", ou seja, determinar a cor resultand de dois
	// objetos que se sobrepõem.
	glClearColor(1.0, 1.0, 1.0, 0);
	// Nesse primeiro programa, será mostrada uma linha em duas dimensões em tela. Para tanto,
	// é necessário "dizer" ao OpenGL como projetar nossa figura na tela, pois projetar uma figura bi-dimensional
	// é tratado pelo OpenGL como um caso especial de uma visualização tridimensional. Os dois próximos comandos
	// especificam que será utilizado uma projeção ortogonal (projeção de uma figura no espaço em um plano) para
	// mapear o conteudo de uma área bidimensional retangular para a tela, sendo que a coordenada "x" variará de 0 a 200
	// e a "y" de 0 a 150. Dessa forma, define-se a coordenada "lower left-corner" para 0 e 0 e a "upper right-corner"
	// para 200 e 150, respectivamente x e y.
	glMatrixMode(GL_PROJECTION);
	// Carrega a matriz identidade para como matriz de projeção. para garantir que a definição das coordenadas
	// a ser realizada em gluOrtho2D não considerarão sujeiras.
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);

}

void point(void) {
	// glClearColor atrubui uma cor à janela, mas não coloca a janela na tela. Para tal, deve-se executar
	// o comando abaixo. O parâmetro GL_COLOR_BUFFER_BIT indica que os bits do "color buffer (refresh buffer)", devem 
	// ser setados para os valores indicados no comando glClearColor.
	glClear(GL_COLOR_BUFFER_BIT);
	// Configura esquema de cor para os objetos que se que mostrar em tela. No exemplo abaixo, deseja-se 
	// setar a cor do objeto para verde escuro. o "f" indica que são valore de ponto flutuande ("float")
	glColor3f(0, 0.4, 0.2);
	//Cria pontos na tela
	// ******* S E Ç Ã O 1 ********
	// ******* pontos, retas e figuras
	/*glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex2f(10, 10);
		glVertex2f(20, 20);
		glVertex2f(30, 30);
		glVertex2f(1270, 710);
	glEnd();

	/*int point1[] = { 50.0,100.0 };
	int point2[] = { 75.0,150.0 };
	int point3[] = { 100,200 };
	// Observe que o sufixo "iv" indica que o argumento será um vetor de inteiros.
	glBegin(GL_POINTS);
		glVertex2iv(point1);
		glVertex2iv(point2);
		glVertex2iv(point3);
	glEnd();

	int p1[] = { 200,300 };
	int p2[] = { 400,200 };
	int p3[] = { 300,400 };
	int p4[] = { 200,200 };
	int p5[] = { 400,300 };
	// GL_LINES plotará linhas ligando pares de pontos. Como tem uma quantidade ímpar, o último ponto será
	// ignorado,
	/*glBegin(GL_LINES);
		glVertex2iv(p1);
		glVertex2iv(p2);
		glVertex2iv(p3);
		glVertex2iv(p4);
		glVertex2iv(p5);
	glEnd();*/
	// GL_LINE_STRIP  ligará os cinco pontos P1->P2, P2->P3... até P4->P5, mas não faz P5->P1!
	/*glBegin(GL_LINE_STRIP);
		glVertex2iv(p1);
		glVertex2iv(p2);
		glVertex2iv(p3);
		glVertex2iv(p4);
		glVertex2iv(p5);
	glEnd();*/
	// GL_LINE_LOOP  ligará os cinco pontos P1->P2, P2->P3... até P4->P5, e fará P5->P1!
	/*glBegin(GL_LINE_LOOP);
		glVertex2iv(p1);
		glVertex2iv(p2);
		glVertex2iv(p3);
		glVertex2iv(p4);
		glVertex2iv(p5);
	glEnd();*/
	//glRect* desenha um retângulo com colorido, onde * significa as diversas formas de usar os parâmetros, duas ou três dimensões, inteiros, reais
	//ou vetor, etc. As duas primeiras coordendas correspondem ao canto inferior direito do retângulo
	//enquanto as duas últimas correspondem ao canto superior esquerdo. O retângulo é gerado no sentido horário
	// ou seja, (200,100)->(50,100)->(50,250)->(200,250)->(200,100), fechando a figura.
    //glRecti(200,100,50,250);
	//GL_POLYGON desenha qualquer polígono usando os vértices no sentido anti-horário.
	/*glBegin(GL_POLYGON);
		glVertex2i(200, 200);
		glVertex2i(200, 300);
		glVertex2i(300, 400);
		glVertex2i(400, 300);
		glVertex2i(400, 200);
		glVertex2i(300, 100);
	glEnd();*/
	//São gerados dois triângulos separados
	/*glBegin(GL_TRIANGLES);
		glVertex2i(200, 200);
		glVertex2i(200, 300);
		glVertex2i(300, 100);
		glVertex2i(300, 400);
		glVertex2i(400, 300);
		glVertex2i(400, 200);
	glEnd();*/
	// Podem-se gerar triângulos separados (P1/P2/P6; P2/P6/P3; P6/P3/P5;P3/P5/P4) com GL_TRIANGLE_STRIP
	// e triângulos com vértice de origem fixo com GL_TRIANGLE_FAN. Podem-se desenhar quadriláterios preenchidos 
	// com GL_QUADS.
	// ******* F I N A L   D A  S E Ç Ã O 1 ********
	// ******* S E Ç Ã O 2 *********
	// ******* desenhando com bitmaps
	//Opcionalmente às primitivas gráficas de linhas, polígonos, etc, pode-se desenhar utilizar vetores
	//retangulares de cores. Cada valor no vetor é mapeado para um ou mais pixels da tela. 
	//Um vetor de pixels de valores de cor é denominado de pixmap. Outra forma de implementar 
	//um vetor de pixels é atribuir um bit 0 ou 1 para cada elemento da matrix. 
	//A cor será a que está definida atualmente para o desenho. 
	//
	GLubyte bitShape[22] = {
		0x1c, 0x00, 
		0x1c, 0x00, 
		0x1c, 0x00, 
		0x1c, 0x00, 
		0x1c, 0x00,
		0xff, 0x80, 
		0x7f, 0x00, 
		0x3e, 0x00, 
		0x1c, 0x00, 
		0x08, 0x00,
		0x08, 0x00
	};
	//Indica a forma de armazenamento de pixels e 
	//dizem respeito à forma como esses elementos são guardados na memória
	//(para mais detalhes ver página 161 / 162 do 
	//livro “OpenGL Uma Abordagem Prática e Objetiva
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// configura a posição raster (raster position) ou seja a posição dentro do frame buffer onde
	// o raster (bitmap) será condiderado (plotado)"	
	glRasterPos2i(640, 360);

	// Os dois primeiros parâmetros especificam a quantidade de colunas (bits) e linhas da figura. 
	// No exemplo, são 11 linhas cada uma com 16 bytes definidos que especificam o desenho.
	// Os dois próximos indicam a posição que deve ser considerada como a origem da imagem. 
	// Os quinto e sexto parâmetros especificam o descolocamento da posição atual da imagem 
	// após o bitmap ser mostrado em tela. No exemplo abaixo, as figuras subsequentes 
	// são deslocadas em 15 unidades para a direita e para cima, setando uma
	// nova posição raster (raster position).
	glBitmap(16, 11, 10.0, 10.0, 15.0, 15.0, bitShape);
	glBitmap(16, 11, 0.0, 0.0, 15.0, 15.0, bitShape);
	glBitmap(16, 11, 0.0, 0.0, 15.0, 15.0, bitShape);

	// **** F I M DA S E Ç Ã O 2 *********
	// **** S E Ç Ã O 3 ********
	// Primitivas para caracteres

	// O primeiro parâmetro especifica um conjunto particular de typefaces enquanto que o segundo parâmetro 
	// é o código ASCII do caracter que será mostrado em tela. A largura das fontes podem ser fixas ou 
	// proporcionais. Os parâmetros GLUT_BITMAP_8_BY_13 e GLUT_BITMAP_9_BY_15 especificam larguras fixas. 
	// Os parâmetros GLUT_BITMAP_TIMES_ROMAN_10 (também tem tamanho 12) E GLUT_BITMAP_HELVETICA_10 
	// (também tem tamanhos 12 e 18) especificam tamanhos espaçadas proporcionalmente. 
	// A cor dos caracteres é a que costa especificada atualmente. 
	// Após execução do comando o bitmap de caracteres é carregado no frame buffer e um 
	// deslocamento da posição atual da imagem (raster position) é realizado em função do tamanho 
	//dos caracteres.
	/*int k;
	glRasterPos2i(140, 140);
	for (k = 0; k < 36; k++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, k+64); // CARACTER 64 É O "A" NA TABELA ASCII
	};
	glRasterPos2i(140, 240);
	for (k = 0; k < 36; k++) {
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, k + 64);
	};
	// Outra forma de mostrar caracteres ASCII é com o comando abaixo. 
	// Há formas de configurar o tamanho e a posição dos caracteres antes de executá-lo. 
	// Os caracteres gerados com o comando são parte do pacote geométrico já que são construídos 
	// a partir de segmentos de reta. Dessa forma, podem ser visualizados
	// a partir de várias direções, podem ser comprimidos ou expandidos sem distorções. 
	// São, porém, mas lentos para serem gerados do que os construídos a partir de bitmaps, 
	// como os do comando glutBitmapCharacter.
	glRasterPos2i(140, 340);
	for (k = 0; k < 36; k++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, k + 64);
	};
	// Força a execução das funções OpenGL utlizadas no programa, que são armazenadas pelo SO em "buffers"
	// que se encontram em diferentes locais do sistema, dependnendo de como o OpenGL foi implementado.
	*/
	glFlush();
}

// Programa Principal 

int main(int argc, char ** argv)
{
	// Inicializa GLUT. Parâmetros são opcionais.
	glutInit(&argc, argv);
	// Configurar opções para mostrar a janela. No caso abaixo, optou-se pelo "single refresh buffer" - GLUT_SINGLE, 
	// e queremos utilizar o sistema de cores RGB - GLUT_RGB. A "|" indica operação "OR". Contrapondo a "single refresh
	// buffer", pode-se ter "double refresh buffer" para animações.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Configura a posição inicial o "upper left-corner" da janela (acima e à esquerda)
	glutInitWindowPosition(0, 0);
	// Configura a largura, primeiro parâmetro, e a altura da janela. Após mostrar a janela na tela
	// é possível reposicioná-la e redimensioná-la.
	glutInitWindowSize(1280, 720);
	// Criar uma janela com um título
	glutCreateWindow("Hello Word!");
	//Executa rotinas de inicialização
	init();
	// o procedimento lineSegment será "passado" para a janela criada. O procedimento "lineSegment" é denominado
	// de "display callback function" e esse procedimento é descrito com sendo "registrado" pela funcão
	// "glutDisplayFunc" como a rotina que será chamada sempre que a janela precisar ser mostrada novamente. Isso pode
	// ocorrer, por exemplo, se o usuário mover a janela. Nesse caso, "lineSegment" será novamente chamado.
	//glutDisplayFunc(lineSegment);
	glutDisplayFunc(point);
	// Deve ser a última função de seu código. Mostra o gráfico inicial e coloca o programa em um loop que 
	// avalia inputs do usuário, tipo uso do mouse ou do teclado. Nesse primeiro exemplo, não haverá interação,
	// então o programa mostrará a figura até que a janela seja fechada.
	glutMainLoop();

	return 0;
}