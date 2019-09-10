#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Vertex.h"

using namespace std;

class Model
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	int nrVertices, nrIndices, id;
	void loadNFG(string location);
	Model(string location);
	~Model();
};

