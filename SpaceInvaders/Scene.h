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
	Scene(int argc, char **argv, string title, int width, int height);
	void Inicio();
	static void DesenhaCena(void);
	~Scene();

};

