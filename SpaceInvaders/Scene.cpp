#include "Scene.h"

#pragma region Structs

struct Bullet
{
	bool foiAtirada;
	bool atingiu;
	float translacaoY;
	float translacaoX;	
};

struct Alien
{
	bool atingido;
	bool desenhado;
	double posicaoX;
	double posicaoY;
};

struct Ponto
{
	float pontoX;
	float pontoY;
};

#pragma endregion

#pragma region Vari�veis Globais

float translacaoNaveX;
float translacaoX;
float translacaoY;

Bullet bullet[2];
Alien alien[20];
Ponto ponto;

float contadorPontuacao;
int naveAtingida, i, j;
float atingidos, troca;

bool direita = true;
bool desce = false;
int telaAtual = 1;

#pragma endregion

#pragma region Desenhos e Textos

// 
void PontoColisao(Ponto ponto) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.48 + ponto.pontoX, 0.7 + 2.0);
	glVertex2f(-0.48 + ponto.pontoX, 0.38 + 2.0);
	glVertex2f(-0.02 + ponto.pontoY, 0.38 + 2.0);
	glVertex2f(-0.02 + ponto.pontoY, 0.7 + 2.0);
	glEnd();
}

// Desenha a nave do jogador
void DesenhaNave() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.1 + translacaoNaveX, -0.76);
	glVertex2f(-0.06 + translacaoNaveX, -0.76);
	glVertex2f(-0.06 + translacaoNaveX, -0.96);
	glVertex2f(-0.1 + translacaoNaveX, -0.96);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(0.1 + translacaoNaveX, -0.76);
	glVertex2f(0.06 + translacaoNaveX, -0.76);
	glVertex2f(0.06 + translacaoNaveX, -0.96);
	glVertex2f(0.1 + translacaoNaveX, -0.96);
	glEnd();

	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glVertex2f(-0.05 + translacaoNaveX, -0.99);
	glVertex2f(0.05 + translacaoNaveX, -0.99);
	glVertex2f(0.05 + translacaoNaveX, -0.96);
	glVertex2f(-0.05 + translacaoNaveX, -0.96);
	glEnd();

	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.12 + translacaoNaveX, -0.96);
	glVertex2f(0.12 + translacaoNaveX, -0.96);
	glVertex2f(0.0 + translacaoNaveX, -0.76);
	glEnd();
}

// Somente desenha o alien
void DesenhaAlien(Alien alien) {
	//1 ponta antena esquerda
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.4 + alien.posicaoX, 0.7 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.7 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.66 + alien.posicaoY);
	glVertex2f(-0.4 + alien.posicaoX, 0.66 + alien.posicaoY);
	glEnd();

	//2 base antena esquerda
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.36 + alien.posicaoX, 0.66 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.32 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.32 + alien.posicaoX, 0.66 + alien.posicaoY);
	glEnd();

	//3 corpo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.4 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.46 + alien.posicaoY);
	glVertex2f(-0.4 + alien.posicaoX, 0.46 + alien.posicaoY);
	glEnd();

	//4 baixo corpo esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.4 + alien.posicaoX, 0.46 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.46 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.4 + alien.posicaoX, 0.42 + alien.posicaoY);
	glEnd();

	//5 baixo corpo direito
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.1 + alien.posicaoX, 0.46 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.46 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.42 + alien.posicaoY);
	glEnd();

	//6 base antena direita
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.18 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.62 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.66 + alien.posicaoY);
	glVertex2f(-0.18 + alien.posicaoX, 0.66 + alien.posicaoY);
	glEnd();

	//7 ponta antena direita 
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.14 + alien.posicaoX, 0.66 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.7 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.7 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.66 + alien.posicaoY);
	glEnd();

	//8 p� esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.36 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.28 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.28 + alien.posicaoX, 0.38 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.38 + alien.posicaoY);
	glEnd();

	//9 p� direito
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.14 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.38 + alien.posicaoY);
	glVertex2f(-0.22 + alien.posicaoX, 0.38 + alien.posicaoY);
	glVertex2f(-0.22 + alien.posicaoX, 0.42 + alien.posicaoY);
	glEnd();

	//10 ombro esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.4 + alien.posicaoX, 0.58 + alien.posicaoY);
	glVertex2f(-0.44 + alien.posicaoX, 0.58 + alien.posicaoY);
	glVertex2f(-0.44 + alien.posicaoX, 0.50 + alien.posicaoY);
	glVertex2f(-0.4 + alien.posicaoX, 0.50 + alien.posicaoY);
	glEnd();

	//11 ombro direito
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.1 + alien.posicaoX, 0.58 + alien.posicaoY);
	glVertex2f(-0.1 + alien.posicaoX, 0.50 + alien.posicaoY);
	glVertex2f(-0.06 + alien.posicaoX, 0.50 + alien.posicaoY);
	glVertex2f(-0.06 + alien.posicaoX, 0.58 + alien.posicaoY);
	glEnd();

	//12 bra�o esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.44 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.48 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.48 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.44 + alien.posicaoX, 0.42 + alien.posicaoY);
	glEnd();

	//13 bra�o direito
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.06 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.06 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.02 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.02 + alien.posicaoX, 0.54 + alien.posicaoY);
	glEnd();

	//14 olho esquerdo
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.36 + alien.posicaoX, 0.58 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.32 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.32 + alien.posicaoX, 0.58 + alien.posicaoY);
	glEnd();

	//15 olho direito
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.18 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.14 + alien.posicaoX, 0.58 + alien.posicaoY);
	glVertex2f(-0.18 + alien.posicaoX, 0.58 + alien.posicaoY);
	glEnd();
}

// Somente desenha a bala
void DesenhaBala(Bullet bullet) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.0125 + bullet.translacaoX, -0.76 + bullet.translacaoY);
	glVertex2f(-0.0125 + bullet.translacaoX, -0.66 + bullet.translacaoY);
	glVertex2f(0.0125 + bullet.translacaoX, -0.66 + bullet.translacaoY);
	glVertex2f(0.0125 + bullet.translacaoX, -0.76 + bullet.translacaoY);
	glEnd();
}

// Controla a pontua��o
void EscrevePontuacaoGeral() {
	char texto[12] = "Pontuacao: ";
	char textoPontuacao[20];
	int k = 0;

	sprintf_s(textoPontuacao, "%.0f", contadorPontuacao);

	glColor3ub(255, 255, 255);
	glRasterPos3f(0.7, -1.0, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[k]);

	for (k = 0; k <= strlen(textoPontuacao); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoPontuacao[k]);
}

void EscreveMenuAuxiliar() {
	char texto[50] = "Aperte Z para Reiniciar ou X para Fechar";
	int k = 0;

	glColor3ub(255, 255, 255);
	glRasterPos3f(-2.0, -0.7, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[k]);
}

void EscrevePerdedor() {
	char texto[11] = "PERDEU";
	int k = 0;

	glColor3ub(254, 255, 255);
	glRasterPos3f(-0.5, 1.0, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[k]);
}

void EscreveGanhou() {
	char texto[8] = "GANHOU";
	int k = 0;

	glColor3ub(255, 255, 255);
	glRasterPos3f(-0.5, 1.0, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[k]);
}

#pragma endregion

void Inicio() {
	contadorPontuacao, atingidos = 0;
	int aux = 0;
	//Valores iniciais para Balas
	for (aux = 0; aux < 2; aux++) {
		bullet[aux].translacaoX = bullet[aux].translacaoY = 0.0;
		bullet[aux].foiAtirada = false;
	}

	//Valores iniciais para Aliens
	for (aux = 0; aux < 20; aux++)
	{
		alien[aux].atingido = alien[aux].desenhado = false;
		alien[aux].posicaoX = -1.5;
		alien[aux].posicaoY = 2.0;
	}

	translacaoX = alien[0].posicaoX;
	troca = translacaoX;
	translacaoY = alien[0].posicaoY;
	translacaoNaveX = 0.0;

	//Manipula o x e y iniciais dos aliens
	for (i = 0; i < 20; i++)
	{
		if (translacaoX >= 1) {
			translacaoX = troca;
			translacaoY += -0.5;
			alien[i].atingido = false;
		}

		if (alien[i].atingido == false) {
			if (i == 0) {
				translacaoX = alien[i].posicaoX;
				translacaoY = alien[i].posicaoY;
			}
			else {
				alien[i].posicaoX = translacaoX;
				alien[i].posicaoY = translacaoY;
			}
			translacaoX += 0.5;
		}
	}
	ponto.pontoX = alien[0].posicaoX;
	ponto.pontoY = alien[4].posicaoX;
}

void DesenhaCena() {

	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, -1.2, 2.8); // Redimenciona os elementos na tela

	if (telaAtual == 1) {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		DesenhaNave();
		EscrevePontuacaoGeral();
		PontoColisao(ponto);

		//Desenha Aliens
		for (i = 0; i < 20; i++)
		{
			if (alien[i].atingido == false)
				DesenhaAlien(alien[i]);
		}

		//Movimento do Alien em X
		for (i = 0; i < 20; i++)
		{
			if (direita)
				alien[i].posicaoX += 0.1;
			else
				alien[i].posicaoX -= 0.1;
		}

		if (direita) {
			ponto.pontoX += 0.1;
			ponto.pontoY += 0.1;
		}
		else
		{
			ponto.pontoX -= 0.1;
			ponto.pontoY -= 0.1;
		}

		//Movimento do Alien em Y
		if (desce) {
			for (i = 0; i < 20; i++)
			{
				alien[i].posicaoY -= 0.1;
			}
			desce = false;
		}

		//Movimento da bala
		for (int i = 0; i < 2; i++)
		{
			if (bullet[i].foiAtirada)
			{
				if (bullet[i].translacaoY >= 3.5) {
					bullet[i].foiAtirada = false;
					bullet[i].translacaoY = 0.0;
				}
				else
				{
					DesenhaBala(bullet[i]);
					bullet[i].translacaoY += 0.1;
				}
			}
		}

		if (naveAtingida == 1) // Testa se a nova foi atingida (perdeu)
			telaAtual = 2;

		if (atingidos == 20) // Testa se matou todos aliens (venceu)
			telaAtual = 3;
	}

	if (telaAtual == 2) {
		EscrevePontuacaoGeral();
		EscrevePerdedor();
		EscreveMenuAuxiliar();
	}

	if (telaAtual == 3) {
		EscrevePontuacaoGeral();
		EscreveGanhou();
		EscreveMenuAuxiliar();
	}

	glPopMatrix();
	glutSwapBuffers();
}

void Teclas(unsigned char tecla, int x, int y) {

	// Escolhe se reinicia ou sai do jogo.
 	if (telaAtual == 2 || telaAtual == 3) {
		if (tecla == 122 || tecla == 90) { //Se apertar Z
			Inicio();
			telaAtual = 1;
			naveAtingida = 0;
			contadorPontuacao = 0;
		}
		if (tecla == 120 || tecla == 88) { //Se apertar X
			exit(0);
		}
	}

	//Verifica os tiros
	if (tecla == 32) {
		for (x = 0; x < 2; x++) {
			if (bullet[x].foiAtirada == false) {
				bullet[x].foiAtirada = true;
				bullet[x].translacaoX = translacaoNaveX;
				break;
			}

		}
	}

	glutPostRedisplay();
}

void TeclasDirecionais(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_RIGHT)
		translacaoNaveX += 0.1;

	if (tecla == GLUT_KEY_LEFT)
		translacaoNaveX -= 0.1;

	glutPostRedisplay();
}

void Anima(int valor) {
	if (ponto.pontoY >= 2.0) {
		direita = false;
		desce = true;
	}
	else if (ponto.pontoX <= -1.54) {
		direita = true;
		desce = true;
	}

	//Colis�o do alien com bala
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (-0.66 >= 0.38 + alien[j].posicaoY && -0.66 <= 0.7 + alien[j].posicaoY){
				naveAtingida = 1;
			}

			if (-0.66 + bullet[i].translacaoY >= 0.38 + alien[j].posicaoY && -0.66 + bullet[i].translacaoY <= 0.7 + alien[j].posicaoY && bullet[i].foiAtirada == true) {
				if (-0.0125 + bullet[i].translacaoX >= -0.48 + alien[j].posicaoX && -0.0125 + bullet[i].translacaoX <= -0.02 + alien[j].posicaoX && bullet[i].foiAtirada == true) {
					alien[j].atingido = true;
					atingidos++;
					contadorPontuacao += 100;
					alien[j].posicaoX = 50;
					alien[j].posicaoY = 50;
					bullet[i].foiAtirada = false;
					bullet[i].translacaoY = 0.0;
				}
			}
			else {
				if (-0.66 + bullet[i].translacaoY >= 0.38 + alien[j].posicaoY && -0.66 + bullet[i].translacaoY <= 0.7 + alien[j].posicaoY && bullet[i].foiAtirada == true) {
					if (0.0125 + bullet[i].translacaoX >= -0.48 + alien[j].posicaoX && 0.0125 + bullet[i].translacaoX <= -0.02 + alien[j].posicaoX && bullet[i].foiAtirada == true) {
						alien[j].atingido = true;
						atingidos++;
						contadorPontuacao += 100;
						alien[j].posicaoX = 50;
						alien[j].posicaoY = 50;
						bullet[i].foiAtirada = false;
						bullet[i].translacaoY = 0.0;
					}
				}
				else {
					if (-0.76 + bullet[i].translacaoY >= 0.38 + alien[j].posicaoY && -0.76 + bullet[i].translacaoY <= 0.7 + alien[j].posicaoY && bullet[i].foiAtirada == true) {
						if (-0.0125 + bullet[i].translacaoX >= -0.48 + alien[j].posicaoX && -0.0125 + bullet[i].translacaoX <= -0.02 + alien[j].posicaoX && bullet[i].foiAtirada == true) {
							alien[j].atingido = true;
							atingidos++;
							contadorPontuacao += 100;
							alien[j].posicaoX = 50;
							alien[j].posicaoY = 50;
							bullet[i].foiAtirada = false;
							bullet[i].translacaoY = 0.0;
						}
					}
					else {
						if (-0.76 + bullet[i].translacaoY >= 0.38 + alien[j].posicaoY && -0.76 + bullet[i].translacaoY <= 0.7 + alien[j].posicaoY && bullet[i].foiAtirada == true) {
							if (0.0125 + bullet[i].translacaoX >= -0.48 + alien[j].posicaoX && 0.0125 + bullet[i].translacaoX <= -0.02 + alien[j].posicaoX && bullet[i].foiAtirada == true) {
								alien[j].atingido = true;
								atingidos++;
								contadorPontuacao += 100;
								alien[j].posicaoX = 50;
								alien[j].posicaoY = 50;
								bullet[i].foiAtirada = false;
								bullet[i].translacaoY = 0.0;
							}
						}
					}
				}
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(50, Anima, 1);
}

Scene::Scene(int argc, char **argv, string title, int width, int height)
{
	glutInit(&argc, argv);
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	// Cria uma janela com o titulo especificado
	glutCreateWindow(title.c_str());

	Inicio();
	glutSpecialFunc(TeclasDirecionais);
	glutKeyboardFunc(Teclas);
	glutDisplayFunc(DesenhaCena);

	glutTimerFunc(50, Anima, 1);

	// Dispara a maquina de estados da OpenGL
	glutMainLoop();
}

Scene::~Scene()
{
}
