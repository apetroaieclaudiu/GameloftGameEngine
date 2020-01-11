#pragma once
#include <string>
#include "../Utilities/utilities.h"

using namespace std;

class SoundResources
{
public:
	GLuint id;
	string path;

	SoundResources();
	~SoundResources();
};

