#pragma once
#include "unit/unitComponent/UnitGraphic.h"
#include "puppy\ShaderManager.h"
#include "puppy/Renderer.h"
#include "kitten/K_CameraList.h"

//Rock
//a component with unit, it handle the unit's texture and animation

namespace unit
{
	std::map<unit::UnitSize, puppy::VertexEnvironment*> UnitGraphic::sm_vao;
	std::map<unit::UnitSize, int> UnitGraphic::sm_instances;

	UnitGraphic::UnitGraphic(UnitSize p_size,const char* p_pathToTexture)
	{
		m_size = p_size;
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTexture != nullptr)
		{
			m_mat->setTexture(p_pathToTexture);
		}

		//If we have not initialized the vao yet
		if (sm_instances[p_size] < 1)
		{
			//setup the vao
			float height, width;
			switch (p_size)
			{
			case unit::point:
				height = 2.0f;
				width = 1.0f;
				break;
			case unit::cube:
				height = 3.0f;
				width = 2.5f;
				break;
			}
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			puppy::TexturedVertex verts[] =
			{
			{ x, y, z,		0.0f, 0.0f },
			{ x, y + height, z,			0.0f, 1.0f },
			{ x + width, y + height, z,			1.0f, 1.0f },
			{ x + width, y + height, z,			1.0f, 1.0f },
			{ x + width, y, z,		1.0f, 0.0f },
			{ x, y, z,		0.0f, 0.0f },
			};

			sm_vao[p_size] = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
		}
		++sm_instances[p_size];

		puppy::Renderer::getInstance()->addToRender(this);

	}

	UnitGraphic::~UnitGraphic()
	{
		delete m_mat;
		if (--sm_instances[m_size] == 0)
		{
			delete sm_vao[m_size];
		}
		puppy::Renderer::getInstance()->removeFromRender(this);
	}

	void UnitGraphic::setTexture(const char * p_pathToTex)
	{
		m_mat->setTexture(p_pathToTex);
	}

	void UnitGraphic::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();
		
		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//render
		sm_vao[m_size]->drawArrays(GL_TRIANGLES);
	}
}
