#pragma once
#include "../rapidxml-1.13/rapidxml_utils.hpp"
#include "CameraScene.h"
#include "Camera.h"
#include "ObjectScene.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "Fire.h"
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
	//vector<CameraScene> cameras;
	vector<Camera*> cameras;
	map<int, ObjectScene*> objects;
	vector<Terrain> terrains;
	float fogLowRadius, fogHighRadius;
	Vector3 fogColor;
	int activeCamera;


	void Init();//initializari - pot fi si in constructor
	void Draw(ESContext*, Matrix, Vector3);
	void Update(Vector3, float);
	static SceneManager* getInstance();
	void metodaInstanta();//o metoda oarecare, nestatica
	Camera* getActiveCamera();
	void setActiveCamera(int);
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor

};

