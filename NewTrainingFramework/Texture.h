#pragma once
#include <string>

using namespace std;

class Texture
{
	int id;
	string path;
	string minFilter, magFilter;
	string wrapS, wrapT;
public:
	Texture();
	~Texture();
};

