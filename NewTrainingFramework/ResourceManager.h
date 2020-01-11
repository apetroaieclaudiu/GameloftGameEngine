#pragma once
#include "../rapidxml-1.13/rapidxml_utils.hpp"
#include "ModelResources.h"
#include "ShaderResources.h"
#include "TextureResources.h"
#include "SoundResources.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "SoundManager.h"
/*#include "Fmod/fmod.h"
#include "Fmod/fmod.hpp"
#include "Fmod/fmod_codec.h"
#include "Fmod/fmod_common.h"
#include "Fmod/fmod_dsp.h"
#include "Fmod/fmod_dsp_effects.h"
#include "Fmod/fmod_errors.h"
#include "Fmod/fmod_output.h"
#include "Fmod/fmod_uwp.h"*/
#include "Fmod/fmod_studio.hpp"
#include "Fmod/fmod.hpp"
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class ResourceManager
{
private:
	static ResourceManager* spInstance;
	ResourceManager();
public:
	~ResourceManager();

	vector<ModelResources> models;
	vector<ShaderResources> shaders;
	vector<TextureResources> textures;
	vector<SoundResources> sounds;
	vector<ModelManager*> loadedModels;
	vector<TextureManager*> loadedTextures;
	vector<ShaderManager*> loadedShaders;
	vector<SoundManager*> loadedSounds;

	ModelManager* LoadModel(int);
	TextureManager* LoadTexture(int);
	ShaderManager* LoadShader(int);
	SoundManager* LoadSound(int);
	void PlaySound(int);

	FMOD::System *fmodSystem;


	
	void Init();//initializari - pot fi si in constructor
	static ResourceManager* getInstance();
	void metodaInstanta();//o metoda oarecare, nestatica
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor

};

