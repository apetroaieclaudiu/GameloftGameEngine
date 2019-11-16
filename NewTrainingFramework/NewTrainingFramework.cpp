// NewTrainingFramework.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "../rapidxml-1.13/rapidxml_utils.hpp"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include "Model.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


GLuint vboId, verticesId, indicesId, textureId;
Shaders myShaders;
GLfloat alpha = 0, pas = 0.01f;
Camera camera;


int nrIndices, width, height, bpp;
char* arrayPixel;
float time;
//const float timeLimit;
ResourceManager* resourceManager;
SceneManager* sceneManager;

/*
void LoadResources()
{
	vector<ModelResources> models;
	vector<ShaderResources> shaders;
	vector<TextureResources> textures;

	resourceManager = ResourceManager::getInstance();

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

	resourceManager->models = models;
	resourceManager->shaders = shaders;
	resourceManager->textures = textures;

}

void LoadScene()
{
	Vector3 bgColor;
	vector<CameraScene> cameras;
	vector<ObjectScene> objects;
	int activeCamera;

	sceneManager = SceneManager::getInstance();

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
		ObjectScene object;
		vector<int> textureIds;

		xml_attribute<> *pAttr = pNode->first_attribute();
		object.id = atoi(pAttr->value());

		xml_node<> *currentNode = pNode->first_node("model");
		object.modelId = atoi(currentNode->value());

		currentNode = pNode->first_node("shader");
		object.shaderId = atoi(currentNode->value());

		currentNode = pNode->first_node("type");
		object.type = currentNode->value();

		if (pNode->first_node("wired/"))
		{

		}

		currentNode = pNode->first_node("blend");
		object.blend = currentNode->value();

		currentNode = pNode->first_node("name");
		object.name = currentNode->value();

		if (pNode->first_node("color"))
		{
			currentNode = pNode->first_node("color");
			xml_node<> *currentNodeVector = currentNode->first_node();
			object.colors.x = atof(currentNodeVector->value());

			currentNodeVector = currentNodeVector->next_sibling();
			object.colors.y = atof(currentNodeVector->value());

			currentNodeVector = currentNodeVector->next_sibling();
			object.colors.z = atof(currentNodeVector->value());

		}

		currentNode = pNode->first_node("textures");
		for (xml_node<> *currentNodeVector = currentNode->first_node("texture"); currentNodeVector; currentNodeVector = currentNodeVector->next_sibling("texture"))
		{
			int textureId = atoi(currentNodeVector->first_attribute()->value());
			textureIds.push_back(textureId);
		}

		object.textureIds = textureIds;

		currentNode = pNode->first_node("position");
		xml_node<> *currentNodeVector = currentNode->first_node();
		object.position.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.position.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.position.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("rotation");
		currentNodeVector = currentNode->first_node();
		object.rotation.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.rotation.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.rotation.z = atof(currentNodeVector->value());

		currentNode = pNode->first_node("scale");
		currentNodeVector = currentNode->first_node();
		object.scale.x = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.scale.y = atof(currentNodeVector->value());

		currentNodeVector = currentNodeVector->next_sibling();
		object.scale.z = atof(currentNodeVector->value());

		objects.push_back(object);

	}

	activeCamera = atoi(pRoot->first_node("activeCamera")->value());

	sceneManager->bgColor = bgColor;
	sceneManager->cameras = cameras;
	sceneManager->objects = objects;
	sceneManager->activeCamera = activeCamera;

}*/

int Init ( ESContext *esContext )
{
	//LoadResources();
	//LoadScene();

	//cout << sceneManager->cameras[0].target.x;
	//cout << sceneManager->objects[0].textureIds[0];
	//cout << sceneManager->objects[0].scale.y;

	resourceManager = ResourceManager::getInstance();
	resourceManager->Init();

	sceneManager = SceneManager::getInstance();
	sceneManager->Init();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	for (map<int, ObjectScene*>::iterator it = sceneManager->objects.begin(); it != sceneManager->objects.end(); it++) {
		if (it->second->type == "normal")
		{
			it->second->model = resourceManager->LoadModel(it->second->modelId);
			TextureManager* texture = resourceManager->LoadTexture(it->second->textureIds[0]);
			it->second->texture.push_back(texture);
			it->second->shader = resourceManager->LoadShader(it->second->shaderId);
		}
		else if (it->second->type == "terrain")
		{
			Terrain* terrain = (Terrain*)it->second;
			terrain->GenerateModel(camera.getPosition());
			for (int i = 0; i < terrain->textureIds.size(); i++)
			{
				TextureManager* texture = resourceManager->LoadTexture(it->second->textureIds[i]);
				it->second->texture.push_back(texture);
			}
			terrain->shader = resourceManager->LoadShader(terrain->shaderId);
			//it->second = (ObjectScene*)it->second;
		}
		
	}
	/*
	for (int i=0; i<sceneManager->objects.size(); i++)
	{
		ObjectScene* it = (ObjectScene*)sceneManager->objects[i]->second;

		if (it->type == "normal")
		{
			it->model = resourceManager->LoadModel(it->modelId);
		}
		else if (it->type == "terrain")
		{
			Terrain* terrain = (Terrain*)it;
			terrain->GenerateModel(camera.getPosition());
			it = (ObjectScene*)it;
		}
		it->texture = resourceManager->LoadTexture(it->textureIds[0]);
		it->shader = resourceManager->LoadShader(it->shaderId);
	}*/
	/*for (std::vector<Terrain>::iterator it = sceneManager->terrains.begin(); it != sceneManager->terrains.end(); ++it)
	{
		Vector3 nullVector;
		nullVector.x = 0; nullVector.y = 0; nullVector.z = 0;
		it->CreateModel(camera.getPosition());
		it->texture = resourceManager->LoadTexture(it->textureIds[0]);
		it->shader = resourceManager->LoadShader(it->shaderId);
	}*/



	/*Model model = Model("../Resources/Models/Croco.nfg");
	nrIndices = model.nrIndices;
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	Vertex2 verticesData[6];
	
	glGenBuffers(1, &verticesId);
	glBindBuffer(GL_ARRAY_BUFFER, verticesId);
	glBufferData(GL_ARRAY_BUFFER, model.nrVertices * sizeof(Vertex), &model.vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indicesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.nrIndices * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glEnable(GL_DEPTH_TEST);

	arrayPixel = LoadTGA("../Resources/Textures/Croco.tga", &width, &height, &bpp);

	if (bpp == 24)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, arrayPixel);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, arrayPixel);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	//creation of shaders and program */
	return myShaders.Init("../Resources/Shaders/ModelShaderVS.vs", "../Resources/Shaders/ModelShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program);


	Matrix mr;
	mr = camera.getViewMatrix() * camera.getPerspectiveMatrix();

	sceneManager->Draw(esContext, mr, camera.getPosition());


	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat*)mr.m);
	}

	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program);

	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, verticesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	//if(myShaders.colorAttribute != -1)
	//{
	//	glEnableVertexAttribArray(myShaders.colorAttribute);
	//	glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3)*4));
	//}

	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 4));
	}

	Matrix mr;
	//mr.SetRotationZ(alpha);
	mr = camera.getViewMatrix() * camera.getPerspectiveMatrix();
	//mr = camera.getViewMatrix();

	if(myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat*)mr.m);
	}

	if (myShaders.textureUniform != -1)
	{
		glUniform1i(myShaders.textureUniform, 0);
	}

	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, nrIndices, GL_UNSIGNED_INT, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );*/
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	camera.updateDeltaTime(deltaTime);
	sceneManager->Update(camera.getPosition());

	alpha += pas;
	//pas *= (-1);
	if (alpha > 2 * PI)
	{
		alpha -= 2*PI;
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	

	switch (key)
	{
	case('w'): 
	case('W'):
		{
			camera.moveOz(-1);
			break;
		}
	case('s'):
	case('S'):
		{
			camera.moveOz(1);
			break;
		}
	case('a'):
	case('A'):
	{
		camera.moveOx(1);
		break;
	}

	case('d'):
	case('D'):
	{
		camera.moveOx(-1);
		break;
	}

	case('q'):
	case('Q'):
	{
		camera.moveOy(-1);
		break;
	}

	case('e'):
	case('E'):
	{
		camera.moveOy(1);
		break;
	}

	case(VK_RIGHT):
	{
		camera.rotateOy(1);
		break;
	}
	case(VK_LEFT):
	{
		camera.rotateOy(-1);
		break;
	}
	case(VK_UP):
	{
		camera.rotateOx(-1);
		break;
	}
	case(VK_DOWN):
	{
		camera.rotateOx(1);
		break;
	}
	case('l'):
	case('L'):
	{
		camera.rotateOz(-1);
		break;
	}
	case('p'):
	case('P'):
	{
		camera.rotateOz(1);
		break;
	}


	}


}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	/*
	using namespace rapidxml;
	xml_document<> doc;
	ifstream file("../exemplu_xml.xml");
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	string content(buffer.str());
	doc.parse<0>(&content[0]);

	xml_node<> *pRoot = doc.first_node();
	cout << pRoot->name() << "\n";

	for (xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
	{
		cout << pNode->name() << " ";

		xml_attribute<> *pAttr = pNode->first_attribute();
		string strValue = pAttr->value();
		cout << strValue << ' ';
		pAttr = pAttr->next_attribute();
		cout << pAttr->value() << "\n";

		for (xml_node<> *pNodeSon = pNode->first_node(); pNodeSon; pNodeSon = pNodeSon->next_sibling())
		{
			cout << pNodeSon->name() << "\n";

			pAttr = pNodeSon->first_attribute();
			string strValue = pAttr->value();
			cout << strValue << "\n";
			cout << pNodeSon->value()<< "\n";
		}



	}*/






	//releasing OpenGL resources
	CleanUp();

	
	printf("Press any key...\n");
	_getch();

	
	return 0;
}

