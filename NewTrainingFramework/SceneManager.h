#pragma once
#include "../rapidxml-1.13/rapidxml_utils.hpp"
#include "CameraScene.h"
#include "ObjectScene.h"
#include "Terrain.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>

class SceneManager
{
private:
	static SceneManager* spInstance;
	SceneManager();
public:
	~SceneManager();

	Vector3 bgColor;
	vector<CameraScene> cameras;
	map<int, ObjectScene*> objects;
	vector<Terrain> terrains;
	int activeCamera;


	void Init();//initializari - pot fi si in constructor
	void Draw(ESContext*, Matrix, Vector3);
	void Update(Vector3);
	static SceneManager* getInstance();
	void metodaInstanta();//o metoda oarecare, nestatica
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor

};

