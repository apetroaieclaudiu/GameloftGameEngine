#pragma once
#include "ShaderResources.h"
#include "../Utilities/utilities.h"

class ShaderManager
{
public:
	ShaderResources* sr;
	GLint shaderId;
	GLuint program, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint uvAttribute;
	GLint matrixUniform;
	GLint textureUniform[5];

	int Load();

	ShaderManager();
	~ShaderManager();
};

