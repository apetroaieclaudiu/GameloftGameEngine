#pragma once
#include <string>
#include <vector>
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "../Utilities/utilities.h"


using namespace std;

class ObjectScene
{
public:
	GLint id, modelId, shaderId;
	string type, blend, name;
	vector<int> textureIds;
	Vector3 colors, position, rotation, scale;
	Vector3 followingCamera;
	Vector3 offset;
	ModelManager* model;
	vector<TextureManager*> texture;
	ShaderManager* shader;
	bool depthTest;

	void GenerateModel();
	void Draw(Matrix);
	virtual void Update(Vector3);

	ObjectScene();
	~ObjectScene();
};

