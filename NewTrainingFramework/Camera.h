#pragma once
#include "../Utilities/utilities.h"

class Camera
{
	Vector3 position, target, up, xAxis, yAxis, zAxis;
	GLfloat moveSpeed, rotateSpeed, Near, Far, fov, deltaTime;
	Matrix viewMatrix, worldMatrix, perspectiveMatrix;
public:
	Camera();
	Camera(Vector3, Vector3);
	~Camera();

	void moveOx(GLfloat);
	void moveOy(GLfloat);
	void moveOz(GLfloat);
	void rotateOx(GLfloat);
	void rotateOy(GLfloat);
	void rotateOz(GLfloat);
	void updateWorldView();
	void updateDeltaTime(float);

	Vector3 getPosition() { return position; }
	Vector3 getTarget() { return target; }
	Vector3 getUp() { return up; }
	Vector3 getXAxis() { return xAxis; }
	Vector3 getYAxis() { return yAxis; }
	Vector3 getZAxis() { return zAxis; }
	GLfloat getMoveSpeed() { return moveSpeed; }
	GLfloat getRotateSpeed() { return rotateSpeed; }
	GLfloat getNear() { return Near; }
	GLfloat getFar() { return Far; }
	GLfloat getFov() { return fov; }
	GLfloat getDeltaTime() { return deltaTime; }
	Matrix getViewMatrix() { return viewMatrix; }
	Matrix getWorldMatrix() { return worldMatrix; }
	Matrix getPerspectiveMatrix() { return perspectiveMatrix; }

	void setPosition(Vector3 position) { this->position = position; }
	void setTarget(Vector3 target) { this->target = target; }
	void setUp(Vector3 up) { this->up = up; }
	void setXAxis(Vector3 xAxis) { this->xAxis = xAxis; }
	void setYAxis(Vector3 yAxis) { this->yAxis = yAxis; }
	void setZAxis(Vector3 zAxis) { this->zAxis = zAxis; }
	void setAxis();
	void setMoveSpeed(GLfloat moveSpeed) { this->moveSpeed = moveSpeed; }
	void setRotateSpeed(GLfloat rotateSpeed) { this->rotateSpeed = rotateSpeed; }
	void setNear(GLfloat Near) { this->Near = Near; }
	void setFar(GLfloat Far) { this->Far = Far; }
	void setFov(GLfloat fov) { this->fov = fov; }
	void setDeltaTime(GLfloat deltaTime) { this->deltaTime = deltaTime; }
	void setViewMatrix(Matrix viewMatrix) { this->viewMatrix = viewMatrix; }
	void setMatrix();
};

