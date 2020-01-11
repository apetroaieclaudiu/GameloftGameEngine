#include "stdafx.h"
#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}


ResourceManager* ResourceManager::spInstance = NULL;
ResourceManager* ResourceManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}
void ResourceManager::metodaInstanta() {
	//nitel cod
}

void ResourceManager::Init()
{

	using namespace rapidxml;
	xml_document<> doc;
	ifstream file("../Resources/resourceManager.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();

	for (xml_node<> *pNode = pRoot->first_node("models")->first_node("model"); pNode; pNode = pNode->next_sibling("model"))
	{
		ModelResources model;

		xml_attribute<> *pAttr = pNode->first_attribute();
		model.id = atoi(pAttr->value());
		string path = pNode->first_node()->value();
		model.path = path;

		models.push_back(model);

	}

	for (xml_node<> *pNode = pRoot->first_node("shaders")->first_node("shader"); pNode; pNode = pNode->next_sibling("shader"))
	{
		ShaderResources shader;

		xml_attribute<> *pAttr = pNode->first_attribute();
		shader.id = atoi(pAttr->value());
		xml_node<> *firstNode = pNode->first_node();
		string path = firstNode->value();
		shader.fileVS = path;
		firstNode = firstNode->next_sibling();
		path = firstNode->value();
		shader.fileFS = path;

		shaders.push_back(shader);

	}

	for (xml_node<> *pNode = pRoot->first_node("textures")->first_node("texture"); pNode; pNode = pNode->next_sibling("texture"))
	{
		TextureResources texture;

		xml_attribute<> *pAttr = pNode->first_attribute();
		texture.id = atoi(pAttr->value());
		pAttr = pAttr->next_attribute();
		texture.type = pAttr->value();

		xml_node<> *currentNode = pNode->first_node();
		string strValue = currentNode->value();
		texture.path = strValue;

		currentNode = currentNode->next_sibling();
		strValue = currentNode->value();
		texture.minFilter = strValue;

		currentNode = currentNode->next_sibling();
		strValue = currentNode->value();
		texture.magFilter = strValue;

		currentNode = currentNode->next_sibling();
		strValue = currentNode->value();
		texture.wrapS = strValue;

		currentNode = currentNode->next_sibling();
		strValue = currentNode->value();
		texture.wrapT = strValue;

		textures.push_back(texture);

	}

	for (xml_node<> *pNode = pRoot->first_node("sounds")->first_node("sound"); pNode; pNode = pNode->next_sibling("sound"))
	{
		SoundResources sound;

		xml_attribute<> *pAttr = pNode->first_attribute();
		sound.id = atoi(pAttr->value());
		string path = pNode->first_node()->value();
		sound.path = path;

		sounds.push_back(sound);

	}

	if (FMOD::System_Create(&fmodSystem) != FMOD_OK) {
		printf("No sounds\n");
	}
	else
	{
		fmodSystem->init(36, FMOD_INIT_NORMAL, NULL);
	}

}

ModelManager* ResourceManager::LoadModel(int id)
{
	int i;

	for (i = 0; i < loadedModels.size(); i++)
	{
		if (loadedModels[i]->mr->id == id)
		{
			return loadedModels[i];
		}
	}

	ModelManager* model = new ModelManager();

	for (i = 0; i < models.size(); i++)
	{
		if (id == models[i].id)
		{
			model->mr = &models[i];
			model->Load();
			loadedModels.push_back(model);

			return model;
		}
	}

	return NULL;
}

TextureManager* ResourceManager::LoadTexture(int id)
{
	int i;

	for (i = 0; i < loadedTextures.size(); i++)
	{
		if (loadedTextures[i]->tr->id == id)
		{
			return loadedTextures[i];
		}
	}

	TextureManager* texture = new TextureManager();

	for (i = 0; i < textures.size(); i++)
	{
		if (id == textures[i].id)
		{
			texture->tr = &textures[i];
			texture->Load();
			loadedTextures.push_back(texture);

			return texture;
		}
	}

	return NULL;
}

ShaderManager* ResourceManager::LoadShader(int id)
{
	int i;

	for (i = 0; i < loadedShaders.size(); i++)
	{
		if (loadedShaders[i]->sr->id == id)
		{
			return loadedShaders[i];
		}
	}

	ShaderManager* shader = new ShaderManager();

	for (i = 0; i < shaders.size(); i++)
	{
		if (id == shaders[i].id)
		{
			shader->sr = &shaders[i];
			shader->Load();
			loadedShaders.push_back(shader);

			return shader;
		}
	}

	return NULL;
}

SoundManager* ResourceManager::LoadSound(int id)
{
	int i;

	for (i = 0; i < loadedSounds.size(); i++)
	{
		if (loadedSounds[i]->sr->id == id)
		{
			return loadedSounds[i];
		}
	}

	SoundManager* soundManager = new SoundManager();

	for (i = 0; i < sounds.size(); i++)
	{
		if (id == sounds[i].id)
		{
			soundManager->sr = &sounds[i];
			//sound->Load();
			soundManager->sr->path = "../" + soundManager->sr->path;

			char pathArray[50];

			strcpy(pathArray, soundManager->sr->path.c_str());

			fmodSystem->createSound(pathArray, FMOD_LOOP_OFF, 0, &soundManager->sound);
			loadedSounds.push_back(soundManager);

			return soundManager;
		}
	}

	return NULL;
}

void ResourceManager::PlaySound(int id)
{
	for (int i = 0; i < loadedSounds.size(); i++)
	{
		if (loadedSounds[i]->soundId == id)
		{
			fmodSystem->playSound(loadedSounds[i]->sound, 0, false, 0);
		}
	}
}
