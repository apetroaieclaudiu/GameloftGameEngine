#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}


Terrain::~Terrain()
{
}

void Terrain::GenerateModel(Vector3 position)
{
	Vector3 currentPos, pos, norm, binorm, tgt;
	Vector2 uv, uvBlend;

	center.x = position.x;
	center.y = offsetY;
	center.z = position.z;

	pos.y = center.y;
	long int a[100][100], k = 0;


	for (int i = 0; i < nrCells+1; i++)
	{
		currentPos.z = center.z + (nrCells / 2) * dimCells - i * dimCells;

		for (int j = 0; j < nrCells+1; j++)
		{
			currentPos.x = center.x - (nrCells / 2) * dimCells + j * dimCells;

			pos.x = currentPos.x;
			pos.z = currentPos.z;
			norm.x = 0;
			norm.y = 1;
			norm.z = 0;
			binorm.x = 0;
			binorm.y = 1;
			binorm.z = 0;
			tgt.x = 0;
			tgt.y = 1;
			tgt.z = 0;
			uv.x = i;
			uv.y = j;
			uvBlend.x = i / nrCells;
			uvBlend.y = j / nrCells;
			vertices.push_back(Vertex(pos, norm, binorm, tgt, uv, uvBlend));

			a[i][j] = k++;

		}
	}

	for (int i = 0; i < nrCells; i++)
	{
		for (int j = 0; j < nrCells; j++)
		{
			/*pos.x = currentPos.x;
			pos.z = currentPos.z;
			vertices.push_back(Vertex(pos));*/


			indices.push_back(a[i][j]);
			indices.push_back(a[i][j + 1]);
			indices.push_back(a[i + 1][j]);

			indices.push_back(a[i][j + 1]);
			indices.push_back(a[i + 1][j]);
			indices.push_back(a[i + 1][j + 1]);

		}
	}

	model = new ModelManager();
	model->nrVertices = vertices.size();
	model->nrIndices = indices.size();

	glGenBuffers(1, &model->verticesId);
	glBindBuffer(GL_ARRAY_BUFFER, model->verticesId);
	glBufferData(GL_ARRAY_BUFFER, model->nrVertices * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->indicesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->nrIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::Update(Vector3 position)
{
	int i;

	if (abs(position.x - center.x) > dimCells)
	{
		if (position.x > center.x)
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.x += dimCells;
				vertices[i].uvBlend.y += 1 / nrCells;
			}

			center.x += dimCells;
		}
		else
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.x -= dimCells;
				vertices[i].uvBlend.y -= 1 / nrCells;
			}

			center.x -= dimCells;
		}
	}

	if (abs(position.z - center.z) > dimCells)
	{
		if (position.z > center.z)
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.z += dimCells;
				vertices[i].uvBlend.x += 1 / nrCells;
			}

			center.z += dimCells;
		}
		else
		{
			for (i = 0; i < vertices.size(); i++)
			{
				vertices[i].pos.z -= dimCells;
				vertices[i].uvBlend.x -= 1 / nrCells;
			}

			center.z -= dimCells;
		}
	}

	glGenBuffers(1, &model->verticesId);
	glBindBuffer(GL_ARRAY_BUFFER, model->verticesId);
	glBufferData(GL_ARRAY_BUFFER, model->nrVertices * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/*
void Terrain::Draw(Vector3 position)
{
	glUseProgram(shader->program);

	//glBindBuffer(GL_ARRAY_BUFFER, model->verticesId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesId);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);

	

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

	if (shader->textureUniform != -1)
	{
		glUniform1i(shader->textureUniform, 0);
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
}*/
