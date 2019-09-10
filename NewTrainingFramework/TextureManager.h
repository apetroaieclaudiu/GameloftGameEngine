#pragma once
#include "TextureResources.h"
#include "../Utilities/utilities.h"

class TextureManager
{
public:
	TextureResources* tr;
	GLuint textureId;

	void Load();

	TextureManager();
	~TextureManager();
};

