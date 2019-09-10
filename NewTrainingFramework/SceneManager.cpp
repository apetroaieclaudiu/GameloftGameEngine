#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}


SceneManager* SceneManager::spInstance = NULL;
SceneManager* SceneManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new SceneManager();
	}
	return spInstance;
}
void SceneManager::metodaInstanta() {
	//nitel cod
}

void passValues(Terrain* target, ObjectScene object)
{
	target->id = object.id;
	target->modelId = object.modelId;
	target->shaderId = object.shaderId;
	target->type = object.type;
	target->blend = object.blend;
	target->name = object.name;
	target->textureIds = object.textureIds;
	target->position = object.position;
	target->rotation = object.rotation;
	target->scale = object.scale;
}

void SceneManager::Init()
{
	using namespace rapidxml;
	xml_document<> doc;
	ifstream file("../Resources/sceneManager.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();

	xml_node<> *pNode = pRoot->first_node("backgroundColor")->first_node();
	bgColor.x = atof(pNode->value());

	pNode = pNode->next_sibling();
	bgColor.y = atof(pNode->value());

	pNode = pNode->next_sibling();
	bgColor.z = atof(pNode->value());

	for (xml_node<> *pNode = pRoot->first_node("cameras")->first_node("camera"); pNode; pNode = pNode->next_sibling("camera"))
	{
		CameraScene camera;

		xml_attribute<> *pAttr = pNode->first_attribute();
		camera.id = atoi(pAttr->value());

		xml_node<> *currentNode = pNode->first_node("position");
		xml_node<> *currentNodeVector = currentNode->first_node();
		camera.position.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.position.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.position.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("target");
		currentNodeVector = currentNode->first_node();
		camera.target.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.target.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.target.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("up");
		currentNodeVector = currentNode->first_node();
		camera.up.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.up.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		camera.up.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("translationSpeed");
		camera.translationSpeed = atof(currentNode->value());

		currentNode = pNode->first_node("rotationSpeed");
		camera.rotationSpeed = atof(currentNode->value());

		currentNode = pNode->first_node("fov");
		camera.Fov = atof(currentNode->value());

		currentNode = pNode->first_node("near");
		camera.Near = atof(currentNode->value());

		currentNode = pNode->first_node("far");
		camera.Far = atof(currentNode->value());

		cameras.push_back(camera);

	}

	for (xml_node<> *pNode = pRoot->first_node("objects")->first_node("object"); pNode; pNode = pNode->next_sibling("object"))
	{
		//ObjectScene* object = new ObjectScene();
		ObjectScene* object;
		vector<int> textureIds;

		xml_attribute<> *pAttr = pNode->first_attribute();

		xml_node<> *currentNode = pNode->first_node("type");
		string type = currentNode->value();

		if (type == "terrain")
		{
			Terrain* terrain = new Terrain();

			terrain->id = atoi(pAttr->value());

			currentNode = pNode->first_node("number");
			terrain->nrCells = atoi(currentNode->value());

			currentNode = pNode->first_node("dimension");
			terrain->dimCells = atof(currentNode->value());

			currentNode = pNode->first_node("offset");
			terrain->offsetY = atof(currentNode->value());

			objects.insert(pair<int, Terrain*>(terrain->id, terrain));

			object = (ObjectScene*)terrain;

		}
		else if (type == "normal")
		{
			object = new ObjectScene();
			object->id = atoi(pAttr->value());
			objects.insert(pair<int, ObjectScene*>(object->id, object));

		}

		object->type = type;


		currentNode = pNode->first_node("model");
		object->modelId = atoi(currentNode->value());

		currentNode = pNode->first_node("shader");
		object->shaderId = atoi(currentNode->value());

		

		if (pNode->first_node("wired/"))
		{

		}

		currentNode = pNode->first_node("blend");
		object->blend = currentNode->value();

		currentNode = pNode->first_node("name");
		object->name = currentNode->value();

		if (pNode->first_node("color"))
		{
			currentNode = pNode->first_node("color");
			xml_node<> *currentNodeVector = currentNode->first_node();
			object->colors.x = atof(currentNodeVector->value());

			currentNodeVector = currentNodeVector->next_sibling();
			object->colors.y = atof(currentNodeVector->value());

			currentNodeVector = currentNodeVector->next_sibling();
			object->colors.z = atof(currentNodeVector->value());

		}

		currentNode = pNode->first_node("textures");
		for (xml_node<> *currentNodeVector = currentNode->first_node("texture"); currentNodeVector; currentNodeVector = currentNodeVector->next_sibling("texture"))
		{
			int textureId = atoi(currentNodeVector->first_attribute()->value());
			textureIds.push_back(textureId);
		}

		object->textureIds = textureIds;

		currentNode = pNode->first_node("position");
		xml_node<> *currentNodeVector = currentNode->first_node();
		object->position.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->position.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->position.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("rotation");
		currentNodeVector = currentNode->first_node();
		object->rotation.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->rotation.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->rotation.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("scale");
		currentNodeVector = currentNode->first_node();
		object->scale.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->scale.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object->scale.z = atof(currentNodeVector->value());

		
		/*if (object->type == "terrain")
		{
			Terrain* terrain = new Terrain();
			terrain = (Terrain*)object;

			currentNode = pNode->first_node("number");
			terrain->nrCells = atoi(currentNode->value());

			currentNode = pNode->first_node("dimension");
			terrain->dimCells = atof(currentNode->value());

			currentNode = pNode->first_node("offset");
			terrain->offsetY = atof(currentNode->value());

			//passValues(terrain, object);

			objects.insert(pair<int, Terrain*>(terrain->id, terrain));
		}
		else
		{
			objects.insert(pair<int, ObjectScene*>(object->id, object));
		}*/

	}

	activeCamera = atoi(pRoot->first_node("activeCamera")->value());

}

void SceneManager::Draw(ESContext *esContext, Matrix mr, Vector3 position)
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	for (int i=0; i<objects.size(); i++)
	{
		ObjectScene* it = objects[i];
		it->Draw(mr);
	}*/
	for (map<int, ObjectScene*>::iterator it = objects.begin(); it != objects.end(); it++) {
		it->second->Draw(mr);
	}
	/*for (std::vector<Terrain>::iterator it = terrains.begin(); it != terrains.end(); ++it)
	{
		it->Draw(mr);
	}*/


	//eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void SceneManager::Update(Vector3 position)
{
	for (map<int, ObjectScene*>::iterator it = objects.begin(); it != objects.end(); it++) {
		if (it->second->type == "terrain")
		{
			((Terrain*)(it->second))->Update(position);
		}
	}
}
