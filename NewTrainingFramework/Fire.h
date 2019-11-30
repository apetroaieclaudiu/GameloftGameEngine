#pragma once
#include "ObjectScene.h"
#include "time.h"

class Fire :
	public ObjectScene
{
public:
	float dispMax;
	float currentTime = 0;
	float lastTime = 0;
	float time = 0;

	void Update();

	Fire();
	~Fire();
};

