#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::Load()
{
	int width, height, bpp;
	char* arrayPixel;

	tr->path = "../" + tr->path;
	//tr->path = "D:\\Projects\\Gameloft\\Resources\\Textures\\Croco.tga";
	const char *path = tr->path.c_str();

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	if (tr->minFilter == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else if (tr->minFilter == "NEAREST")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	if (tr->magFilter == "LINEAR")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else if (tr->magFilter == "NEAREST")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	if (tr->wrapS == "CLAMP_TO_EDGE")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	}
	else if (tr->wrapS == "REPEAT")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	}

	if (tr->wrapT == "CLAMP_TO_EDGE")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (tr->wrapT == "REPEAT")
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glEnable(GL_DEPTH_TEST);

	arrayPixel = LoadTGA(path, &width, &height, &bpp);

	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, arrayPixel);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, arrayPixel);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}
