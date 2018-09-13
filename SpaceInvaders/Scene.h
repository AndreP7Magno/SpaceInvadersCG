#pragma once
#include "GL\glew.h"
#include "GL\freeglut.h"
#include <vector>
using namespace std;
using std::string;

class Scene
{
	int width;
	int height;
	string title;

public:

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
	~Scene();

private:
	
};


