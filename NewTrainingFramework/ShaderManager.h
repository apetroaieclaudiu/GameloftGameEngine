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
	GLint uvBlendAttribute;
	GLint matrixUniform;
	GLint Uniform;
	GLint heightUniform;
	GLint lowRadiusUniform;
	GLint highRadiusUniform;
	GLint cameraPositionUniform;
	GLint scenePositionUniform;
	GLint timeUniform;
	GLint dispMaxUniform;
	GLint fogColorUniform;
	GLint textureUniform[5];

	int Load();

	ShaderManager();
	~ShaderManager();
};

