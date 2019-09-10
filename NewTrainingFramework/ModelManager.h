#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Vertex.h"
#include "ModelResources.h"

class ModelManager
{
public:
	ModelResources* mr;
	GLuint indicesId, wiredIndicesId, verticesId;
	int nrVertices, nrIndices, nrIndicesWired;

	void Load();


	ModelManager();
	~ModelManager();
};

