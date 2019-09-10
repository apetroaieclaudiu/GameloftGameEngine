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

	ModelManager* model = (ModelManager*)malloc(sizeof(ModelManager));

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

	TextureManager* texture = (TextureManager*)malloc(sizeof(TextureManager));

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

	ShaderManager* shader = (ShaderManager*)malloc(sizeof(ShaderManager));

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
