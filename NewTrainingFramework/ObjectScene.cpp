#include "stdafx.h"
#include "ObjectScene.h"
#include "Terrain.h"
#include "SceneManager.h"

ObjectScene::ObjectScene()
{
}


ObjectScene::~ObjectScene()
{
}

void ObjectScene::GenerateModel()
{

}

void ObjectScene::Draw(Matrix mr, Vector3 camPos)
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
		glUniform3f(shader->heightUniform, height[0], height[1], height[2]);
	}
	
	if (shader->lowRadiusUniform != -1)
	{
		GLfloat lowRadius = SceneManager::getInstance()->fogLowRadius;
		glUniform1f(shader->lowRadiusUniform, lowRadius);
	}

	if (shader->highRadiusUniform != -1)
	{
		GLfloat highRadius = SceneManager::getInstance()->fogHighRadius;
		glUniform1f(shader->highRadiusUniform, highRadius);
	}

	if (shader->timeUniform != -1)
	{
		GLfloat time = ((Fire*)this)->time;
		glUniform1f(shader->timeUniform, time);
	}

	if (shader->dispMaxUniform != -1)
	{
		GLfloat dispMax = ((Fire*)this)->dispMax;
		glUniform1f(shader->dispMaxUniform, dispMax);
	}
	
	if (shader->fogColorUniform != -1)
	{
		GLfloat fogColor[3];
		fogColor[0] = SceneManager::getInstance()->fogColor.x;
		fogColor[1] = SceneManager::getInstance()->fogColor.y;
		fogColor[2] = SceneManager::getInstance()->fogColor.z;
		glUniform3f(shader->fogColorUniform, fogColor[0], fogColor[1], fogColor[2]);
	}

	if (shader->cameraPositionUniform != -1)
	{
		GLfloat cameraPosition[3];
		cameraPosition[0] = camPos.x;
		cameraPosition[1] = camPos.y;
		cameraPosition[2] = camPos.z;
		glUniform3f(shader->cameraPositionUniform, cameraPosition[0], cameraPosition[1], cameraPosition[2]);
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


	


	Matrix scenePosition, rotX, rotY, rotZ, scaleMatrix, transMatrix;

	rotX.SetRotationX(rotation.x);
	rotY.SetRotationY(rotation.y);
	rotZ.SetRotationZ(rotation.z);
	transMatrix.SetTranslation(position.x, position.y, position.z);
	scaleMatrix.SetScale(scale.x, scale.y, scale.z);


	scenePosition = scaleMatrix * rotX * rotY * rotZ * transMatrix;

	if (shader->scenePositionUniform != -1)
	{
		glUniformMatrix4fv(shader->scenePositionUniform, 1, GL_FALSE, (GLfloat*)scenePosition.m);
	}

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

void ObjectScene::Update(Vector3 cameraPosition, float deltaTime)
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

	if (trajectoryType != "none" && iterationCount != 0)
	{
		if (trajectoryType == "linear" || trajectoryType == "line_strip" || trajectoryType == "line_loop")
		{
			Vector3 distance;
			int nextPoint;

			if (forward == true)
			{
				nextPoint = currentPoint + 1;
				distance = points[nextPoint] - points[currentPoint];
			}
			else
			{
				nextPoint = currentPoint - 1;
				distance = points[nextPoint] - points[currentPoint];
			}

			Vector3 move = distance.Normalize() * speed * deltaTime;
			position += move;
			//rotation = Vector3(distance.Normalize().x, distance.Normalize().y, 0);

			float pointDistance = (points[nextPoint].x - points[currentPoint].x) * (points[nextPoint].x - points[currentPoint].x);
			pointDistance += (points[nextPoint].y - points[currentPoint].y) * (points[nextPoint].y - points[currentPoint].y);
			pointDistance += (points[nextPoint].z - points[currentPoint].z) * (points[nextPoint].z - points[currentPoint].z);

			float positionDistance = (position.x - points[currentPoint].x) * (position.x - points[currentPoint].x);
			positionDistance += (position.y - points[currentPoint].y) * (position.y - points[currentPoint].y);
			positionDistance += (position.z - points[currentPoint].z) * (position.z - points[currentPoint].z);

			if (positionDistance > pointDistance)
			{
				if (iterationCount > 0)
				{
					iterationCount--;
				}

				position = points[nextPoint];
				currentPoint = nextPoint;

				if (currentPoint == 0 || currentPoint == points.size() - 1)
				{
					if (direction == "normal")
					{
						currentPoint = 0;
						position = points[currentPoint];
					}
					else
					{
						forward = !forward;
					}
				}
			}
		}
		else if (trajectoryType == "circle")
		{
			
			alpha += speed * deltaTime;
			rotation.y = -alpha - 135;
			position.x = radius * cos(alpha) + offsetPosition.x;
			position.z = radius * sin(alpha) + offsetPosition.z;
			
			/*
			alpha += speed * deltaTime;
			float xAxis = 90.0f / points[1].x;
			beta += speed / xAxis * deltaTime * sign;

			if (beta > 3.14f / xAxis) {
				sign = -1;
			}
			if (beta < 0) {
				sign = 1;
			}

			printf("%f ", beta);

			

			
			rotation.y = -alpha - 135;
			position.x = radius * cos(alpha) + offsetPosition.x;
			position.z = radius * sin(alpha) + offsetPosition.z;
			position.y = radius * cos(beta) + offsetPosition.y;
			*/
		}
	}
}
