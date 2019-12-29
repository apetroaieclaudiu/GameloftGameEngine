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
	Matrix placement;
	string trajectoryType;
	string direction;
	bool forward;
	int iterationCount;
	float speed;
	vector<Vector3> points;
	int currentPoint;
	Vector3 lastPosition;
	float radius;
	//float deltaTime;
	float alpha;
	float beta = 0;
	int sign = 1;
	Vector3 offsetPosition;

	void GenerateModel();
	void Draw(Matrix, Vector3);
	virtual void Update(Vector3, float);

	ObjectScene();
	~ObjectScene();
};

