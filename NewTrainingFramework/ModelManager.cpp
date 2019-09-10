#include "stdafx.h"
#include "ModelManager.h"


ModelManager::ModelManager()
{
}


ModelManager::~ModelManager()
{
}

void ModelManager::Load()
{
	mr->path = "../" + mr->path;
	//mr->path = "D:\\Projects\\Gameloft\\Resources\\Models\\Croco.nfg";
	ifstream modelFile(mr->path);

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	string line;
	Vector3 pos, norm, binorm, tgt;
	Vector2 uv;

	int i = 0, x, indX, indY, indZ;

	std::getline(modelFile, line);
	sscanf(line.c_str(), "NrVertices: %d", &nrVertices);

	while (getline(modelFile, line))
	{
		if (line[0] == 'N')
		{
			sscanf(line.c_str(), "NrIndices: %d", &nrIndices);
			break;
		}
		sscanf(line.c_str(), "   %d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &x, &pos.x, &pos.y, &pos.z, &norm.x, &norm.y, &norm.z, &binorm.x, &binorm.y, &binorm.z, &tgt.x, &tgt.y, &tgt.z, &uv.x, &uv.y);



		vertices.push_back(Vertex(pos, norm, binorm, tgt, uv));
		i++;

	}

	i = 0;

	while (getline(modelFile, line))
	{
		sscanf(line.c_str(), "   %d.    %d,    %d,    %d", &x, &indX, &indY, &indZ);

		indices.push_back(indX);
		indices.push_back(indY);
		indices.push_back(indZ);

		i++;
	}

	modelFile.close();

	glGenBuffers(1, &verticesId);
	glBindBuffer(GL_ARRAY_BUFFER, verticesId);
	glBufferData(GL_ARRAY_BUFFER, nrVertices * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indicesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
