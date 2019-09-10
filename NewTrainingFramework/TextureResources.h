#pragma once
#include <string>
#include "../Utilities/utilities.h"

using namespace std;

class TextureResources
{
	
public:
	GLint id;
	string type;
	string path;
	string minFilter, magFilter;
	string wrapS, wrapT;

	TextureResources();
	~TextureResources();
};

