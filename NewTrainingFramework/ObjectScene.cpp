#include "stdafx.h"
#include "ObjectScene.h"
#include "Terrain.h"

ObjectScene::ObjectScene()
{
}


ObjectScene::~ObjectScene()
{
}

void ObjectScene::GenerateModel()
{

}

void ObjectScene::Draw(Matrix mr)
{

	int i;

	glUseProgram(shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, model->verticesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesId);

	for (i = 0; i < texture.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		if (texture[i]->tr->type == "2d")
		{
			glBindTexture(GL_TEXTURE_2D, texture[i]->textureId);
		}
		else if (texture[i]->tr->type == "cube")
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, texture[i]->textureId);
		}
		

		if (shader->textureUniform[i] != -1)
		{
			glUniform1i(shader->textureUniform[i], i);
		}
	}

	if (shader->heightUniform != -1)
	{
		GLfloat height[3];
		height[0] = ((Terrain*)this)->heights.x;
		height[1] = ((Terrain*)this)->heights.y;
		height[2] = ((Terrain*)this)->heights.z;
		glUniform3fv(shader->heightUniform, 1, (GLfloat*)height);
	}

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 4));
	}

	if (shader->uvBlendAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvBlendAttribute);
		glVertexAttribPointer(shader->uvBlendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 4 + sizeof(Vector2)));
	}


	


	Matrix placement, rotX, rotY, rotZ, scaleMatrix, transMatrix;

	rotX.SetRotationX(rotation.x);
	rotY.SetRotationY(rotation.y);
	rotZ.SetRotationZ(rotation.z);
	transMatrix.SetTranslation(position.x, position.y, position.z);
	scaleMatrix.SetScale(scale.x, scale.y, scale.z);

	placement = scaleMatrix * rotX * rotY * rotZ * transMatrix * mr;

	if (shader->matrixUniform != -1)
	{
		glUniformMatrix4fv(shader->matrixUniform, 1, GL_FALSE, (GLfloat*)placement.m);
	}
	
	glDrawElements(GL_TRIANGLES, model->nrIndices, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (texture[0]->tr->type == "2d")
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (texture[0]->tr->type == "cube")
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

}

void ObjectScene::Update(Vector3 cameraPosition)
{
	bool follow = true;

	if (followingCamera.x == 0 && followingCamera.y == 0 && followingCamera.z == 0)
	{
		follow = false;
	}

	if (follow = true)
	{
		if (followingCamera.x == 1)
		{
			position.x = cameraPosition.x + offset.x;
		}

		if (followingCamera.y == 1)
		{
			position.y = cameraPosition.y + offset.y;
		}

		if (followingCamera.z == 1)
		{
			position.z = cameraPosition.z + offset.z;
		}
		
	}
}
