#include "Scene.h"
#include "Bullet.h"
#include "Alien.h"

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

	vector<Bullet> bullet = vector<Bullet>();
	vector<Alien> alien = vector<Alien>();

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
	Scene::TipoTela telaAtual = Scene::GetTipoTela();

	// Limpa a janela com a cor especificada como cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//xmin, xmax, ymin, ymax
	//gluOrtho2D(-2, 2, -1.2, 2.8);
	
	if (telaAtual == Scene::TipoTela::Inicial) {

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


Scene::~Scene()
{
}
