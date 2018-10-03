#include "Scene.h"

#pragma region Structs

struct Bullet
{
	bool foiAtirada;
	bool atingiu;
	double translacaoY;
	double translacaoX;
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
	double pontoX;
	double pontoY;
};

#pragma endregion

#pragma region Variáveis Globais

double translacaoNaveX;
double translacaoX;
double translacaoY;

Bullet bullet[3];
Alien alien[20];
Ponto ponto;

double contadorPontuacao;
int naveAtingida, i, j;
float atingidos, troca;

bool direita = true;
bool desce = false;
int telaAtual = 1;

bool pause = false;

double velocidadeAlien = 0.1;

#pragma endregion

#pragma region Desenhos e Textos

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

	//8 pé esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.36 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.28 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.28 + alien.posicaoX, 0.38 + alien.posicaoY);
	glVertex2f(-0.36 + alien.posicaoX, 0.38 + alien.posicaoY);
	glEnd();

	//9 pé direito
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

	//12 braço esquerdo
	glColor3f(0.0, 1.0, 0.6);
	glBegin(GL_QUADS);
	glVertex2f(-0.44 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.48 + alien.posicaoX, 0.54 + alien.posicaoY);
	glVertex2f(-0.48 + alien.posicaoX, 0.42 + alien.posicaoY);
	glVertex2f(-0.44 + alien.posicaoX, 0.42 + alien.posicaoY);
	glEnd();

	//13 braço direito
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

// Controla a pontuação
void EscrevePontuacaoGeral() {
	char texto[12] = "Pontuacao: ";
	char textoPontuacao[20];
	int k = 0;

	sprintf_s(textoPontuacao, "%.0f", contadorPontuacao);

	glColor3ub(255, 255, 255);
	glRasterPos3f(0.4, 2.6, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[k]);

	for (k = 0; k <= strlen(textoPontuacao); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, textoPontuacao[k]);
}

void EscreveMenuAuxiliar() {
	char texto[50] = "Aperte Z para Reiniciar ou X para Fechar";
	int k = 0;

	glColor3ub(255, 255, 255);
	glRasterPos3f(-1.7, 0.7, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[k]);
}

void EscrevePerdedor() {
	char texto[11] = "PERDEU";
	int k = 0;

	glColor3ub(254, 255, 255);
	glRasterPos3f(-0.5, 1.0, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[k]);
}

void EscreveGanhou() {
	char texto[8] = "GANHOU";
	int k = 0;

	glColor3ub(255, 255, 255);
	glRasterPos3f(-0.5, 1.0, 0.0);

	for (k = 0; k <= strlen(texto); k++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, texto[k]);
}

#pragma endregion

void Inicio() {
	contadorPontuacao, atingidos = 0;
	int aux = 0;

	//Valores iniciais para Balas
	for (aux = 0; aux < 3; aux++) {
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
		//PontoColisao(ponto);

		//Desenha Aliens
		for (i = 0; i < 20; i++)
		{
			if (alien[i].atingido == false) //Verifica se o alien não foi atingido pela bala
				DesenhaAlien(alien[i]);
		}

		//Movimento do Alien em X
		for (i = 0; i < 20; i++)
		{
			if (direita)
				alien[i].posicaoX += velocidadeAlien;
			else
				alien[i].posicaoX -= velocidadeAlien;
		}

		if (direita) {
			ponto.pontoX += velocidadeAlien;
			ponto.pontoY += velocidadeAlien;
		}
		else
		{
			ponto.pontoX -= velocidadeAlien;
			ponto.pontoY -= velocidadeAlien;
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
		for (int i = 0; i < 3; i++) //Número máximo de balas = 2
		{
			if (bullet[i].foiAtirada)
			{
				if (bullet[i].translacaoY >= 3.5) { //Testa se a bala passou para fora da janela
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

		if (naveAtingida == 1) { // Testa se a nova foi atingida (perdeu)
			telaAtual = 2;
		}

		if (atingidos == 20) { // Testa se matou todos aliens (venceu)
			telaAtual = 3;
		}
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
		if (tecla == 122 || tecla == 90) { //Se apertar Z reinicia
			Inicio();
			telaAtual = 1;
			naveAtingida = 0;
			contadorPontuacao = 0;
		}
		if (tecla == 120 || tecla == 88) { //Se apertar X sai
			exit(0);
		}
	}

	//Verifica os tiros
	if (tecla == 32 && !pause) { //Se apertar Espaço atira
		for (x = 0; x < 3; x++) {
			if (bullet[x].foiAtirada == false) {
				bullet[x].foiAtirada = true;
				bullet[x].translacaoX = translacaoNaveX; //Bala sai da mesma posição que a nave
				break;
			}

		}
	}

	if (!pause && tecla == 99)
		pause = tecla == 99;
	else if (pause && tecla != 99)
		pause = true;
	else if (tecla == 99)
		pause = false;
	
	if (!pause)
		glutPostRedisplay();
}

void TeclasDirecionais(int tecla, int x, int y) {
	if (tecla == GLUT_KEY_RIGHT && !pause)
		translacaoNaveX += 0.1; //Nave vai para a direita

	if (tecla == GLUT_KEY_LEFT && !pause)
		translacaoNaveX -= 0.1; //Nave vai para a esquerda

	if (!pause)
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

	//Colisão do alien com bala
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 20; j++)
		{
			if (-0.66 >= 0.38 + alien[j].posicaoY && -0.66 <= 0.7 + alien[j].posicaoY) {
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

	if (!pause)
		glutPostRedisplay();
	glutTimerFunc(50, Anima, 1);
}

Scene::Scene(int argc, char **argv, string title, int width, int height)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitWindowSize(width, height); //Tamanho da janela
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2); //Põe no centro da tela
	glutCreateWindow(title.c_str()); // Cria uma janela com o titulo especificado

	Inicio(); //Define posições iniciais
	glutSpecialFunc(TeclasDirecionais); //Permite trabalhar com o teclado
	glutKeyboardFunc(Teclas); //Permite trabalhar com o teclado
	glutDisplayFunc(DesenhaCena); //Gera a janela e seus artefatos

	glutTimerFunc(50, Anima, 1); //Função timer que executa callback com a função Anima()

	glutMainLoop(); // Dispara a maquina de estados da OpenGL
}

Scene::~Scene()
{
}
