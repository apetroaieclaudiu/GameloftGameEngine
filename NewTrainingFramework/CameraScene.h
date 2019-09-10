#pragma once
#include "../Utilities/utilities.h"

class CameraScene
{
public:
	int id;
	Vector3 position, target, up;
	GLfloat translationSpeed, rotationSpeed, Fov, Near, Far;

	CameraScene();
	~CameraScene();
};

