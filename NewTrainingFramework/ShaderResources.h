#pragma once
#include <string>
#include "../Utilities/utilities.h"

using namespace std;

class ShaderResources
{
public:
	GLuint id;
	string fileVS;
	string fileFS;

	ShaderResources();
	~ShaderResources();
};

