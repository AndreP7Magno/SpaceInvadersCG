#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <vector>
using namespace std;

class Scene
{
	int width;
	int height;
	string title;

public:
	
	static float translacaoNaveX;
	static float contadorPontuacao;
	static Ponto ponto;
	static vector<Alien> alien;
	static vector<Bullet> bullet;
	static bool direita;
	static bool desce;
	static int at;
	static float Atingidos;

	enum TipoTela
	{
		Inicial,
		Ganhador,
		Perdedor		
	};

	static void Scene::SetTipoTela(Scene::TipoTela tipoTela)
	{
		_tipoTela = tipoTela;
	}

	static Scene::TipoTela Scene::GetTipoTela()
	{
		return _tipoTela;
	}

	static Scene::TipoTela _tipoTela;

	Scene(int argc, char **argv, string title, int width, int height);
	void Inicio();
	static void DesenhaCena(void);
	static void DesenhaNave();
	static void EscreveTelaInicial();
	~Scene();

private:
	
};


