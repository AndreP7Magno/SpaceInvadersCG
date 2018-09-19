#include "Scene.h"
#include "Bullet.h"
#include "Alien.h"
#include "Ponto.h"
#include <stdio.h>

Scene::Scene(int argc, char **argv, string title, int width, int height)
{
	Scene::SetTipoTela(Scene::TipoTela::Inicial); //TENTAR MUDAR O LUGAR DISSO

	glutInit(&argc, argv);
	// Indica que deve ser usado um unico buffer para armazenamento da imagem e representacao de cores RGB
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
	// Cria uma janela com o titulo especificado
	glutCreateWindow(title.c_str());

	Inicio();
	//glutSpecialFunc(spteclas);
	//glutKeyboardFunc(teclas);
	glutDisplayFunc(DesenhaCena);

	//glutTimerFunc(50, Anima, 1);

	// Dispara a maquina de estados da OpenGL
	glutMainLoop();
}


void Scene::Inicio() {

	//Valores iniciais para Aliens
	for (int aux = 0; aux < 20; aux++)
	{
		alien[aux].atingido = alien[aux].desenhado = false;
		alien[aux].posicaoX = -1.5;
		alien[aux].posicaoY = 2.0;
	}

	//Valores iniciais para Balas
	for (int aux = 0; aux < 2; aux++) {
		bullet[aux].posicaoX = bullet[aux].translacaoY = 0.0;
		bullet[aux].foiAtirada = false;
	}

	//CONTINUAR A LÓGICA DE INICIO DEPOIS
}

void Scene::DesenhaCena(void) {
	direita = true;
	desce = false;
	Scene::TipoTela telaAtual = Scene::GetTipoTela();

	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//xmin, xmax, ymin, ymax
	//gluOrtho2D(-2, 2, -1.2, 2.8);

	if (telaAtual == Scene::TipoTela::Inicial) {
		glClearColor(0.0, 0.0, 0.0, 0.0);
		DesenhaNave();
		EscreveTelaInicial();
		PontoColisao(ponto);

		//Desenha Aliens
		for (int i = 0; i < 20; i++)
		{
			if (!alien[i].atingido)
				DesenhaAlien(alien[i]);
		}

		//Movimento do Alien em X
		for (int i = 0; i < 20; i++)
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

		//Movimento do Y do Alien
		if (desce) {
			for (int i = 0; i < 20; i++)
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
					Desbala(bullet[i]);
					bullet[i].translacaoY += 0.1;
				}
			}
		}

		if (at == 1)
		{
			Scene::SetTipoTela(Scene::TipoTela::Perdedor);
			telaAtual = Scene::GetTipoTela();
		}

		if (Atingidos == 20) {
			Scene::SetTipoTela(Scene::TipoTela::Ganhador);
			telaAtual = Scene::GetTipoTela();
		}
	}

	telaAtual = Scene::GetTipoTela();
	if (telaAtual == Scene::TipoTela::Ganhador) {

	}

	telaAtual = Scene::GetTipoTela();
	if (telaAtual == Scene::TipoTela::Perdedor) {

	}

	glPopMatrix();
	glutSwapBuffers();
}

#pragma region Desenhos e Textos

void Scene::DesenhaNave() {
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

void Scene::EscreveTelaInicial() {
	char texto[11] = "Pontuacao:";
	char textoPontuacao[20];

	sprintf_s(textoPontuacao, "%.0f", contadorPontuacao);

	glColor3ub(255, 255, 255);
	glRasterPos3f(0.7, -1.0, 0.0);

	for (int aux = 0; aux <= strlen(texto); aux++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, texto[aux]);

	for (int aux = 0; aux <= strlen(textoPontuacao); aux++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, textoPontuacao[aux]);
}

void PontoColisao(Ponto ponto) {
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.48 + ponto.pontoX, 0.7 + 2.0);
	glVertex2f(-0.48 + ponto.pontoX, 0.38 + 2.0);
	glVertex2f(-0.02 + ponto.pontoY, 0.38 + 2.0);
	glVertex2f(-0.02 + ponto.pontoY, 0.7 + 2.0);
	glEnd();
}

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

void Desbala(Bullet bullet) {
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.0125 + bullet.posicaoX, -0.76 + bullet.translacaoY);
	glVertex2f(-0.0125 + bullet.posicaoX, -0.66 + bullet.translacaoY);
	glVertex2f(0.0125 + bullet.posicaoX, -0.66 + bullet.translacaoY);
	glVertex2f(0.0125 + bullet.posicaoX, -0.76 + bullet.translacaoY);
	glEnd();
}

#pragma endregion

Scene::~Scene()
{
}
