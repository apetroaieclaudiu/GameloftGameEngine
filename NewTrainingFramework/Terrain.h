#pragma once
#include "ObjectScene.h"
#include "Vertex.h"
class Terrain :
	public ObjectScene
{
public:
	int nrCells;
	float dimCells, offsetY;
	Vector3 center;
	vector<Vertex> vertices;
	vector<unsigned int> indices;

	void GenerateModel(Vector3);
	void Update(Vector3);
	//void Draw(Vector3);

	Terrain();
	~Terrain();
};

