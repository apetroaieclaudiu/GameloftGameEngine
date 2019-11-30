#include "stdafx.h"
#include "Fire.h"


Fire::Fire()
{
}


Fire::~Fire()
{
}


void Fire::Update()
{
	currentTime = (float)clock() / CLOCKS_PER_SEC / 2;
	time += (currentTime - lastTime);
	lastTime = currentTime;
	if (time > 1)
	{
		time -= 1;
	}
}
