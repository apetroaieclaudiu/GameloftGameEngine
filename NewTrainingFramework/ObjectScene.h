#pragma once
#include <string>
#include <vector>
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Trajectory.h"
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
	bool circleTrajectory;
	Matrix placement;
	Trajectory* trajectory;
	

	void GenerateModel();
	void Draw(Matrix, Vector3);
	virtual void Update(Vector3, float);

	ObjectScene();
	~ObjectScene();
};

