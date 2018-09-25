#pragma once
#include "unit/unitComponent/UnitGraphic.h"
#include "puppy\ShaderManager.h"
#include "kitten/K_CameraList.h"

//Rock
//a component with unit, it handle the unit's texture and animation

namespace unit
{
	puppy::VertexEnvironment* UnitGraphic::sm_vao = nullptr;

	UnitGraphic::UnitGraphic(UnitSize p_size,const char* p_pathToTexture)
	{
		puppy::Renderer::getInstance()->addToRender(this);

		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTexture != nullptr)
		{
			m_mat->setTexture(p_pathToTexture);
		}

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
		default:
			height = 1.0f;
			width = 1.0f;
			break;
		}

		float x = -0.5f;
		float y = -0.5f;
		float z = 3.0f;
		// Front
		m_verts.push_back({ x, y, z,		0.0f, 0.0f });
		m_verts.push_back({ x,  y+height, z,		0.0f, 1.0f });
		m_verts.push_back({ x + width,  y + height, z,		1.0f, 1.0f });
		m_verts.push_back({ x + width,  y + height, z,		1.0f, 1.0f });
		m_verts.push_back({ x + width, y, z,		1.0f, 0.0f });
		m_verts.push_back({ x, y, z,		0.0f, 0.0f });

		//setup the vao
		sm_vao = new puppy::VertexEnvironment(&m_verts[0], puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), m_verts.size());

	}

	UnitGraphic::~UnitGraphic()
	{
		delete m_mat;
		delete sm_vao;
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
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}
