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
	Scene(int argc, char **argv, string title, int width = 600, int height = 600);
	~Scene();

};

