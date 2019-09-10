#include "stdafx.h"
#include "ObjectScene.h"

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
		glBindTexture(GL_TEXTURE_2D, texture[i]->textureId);
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

	if (type == "normal")
	{
		if (shader->textureUniform[0] != -1)
		{
			glUniform1i(shader->textureUniform[0], 0);
		}
	}
	else
	{
		for (int i = 0; i < texture.size(); i++)
		{
			if (shader->textureUniform[i] != -1)
			{
				glUniform1i(shader->textureUniform[i], 0);
			}
		}
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
	glBindTexture(GL_TEXTURE_2D, 0);

}

void ObjectScene::Update()
{

}
