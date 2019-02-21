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
	std::map<unit::UnitSize, puppy::VertexEnvironment*> UnitGraphic::sm_vao_shadow;
	std::map<unit::UnitSize, int> UnitGraphic::sm_instances;

	UnitGraphic::UnitGraphic(UnitSize p_size,const char* p_pathToTexture)
	{
		m_size = p_size;
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		m_pathToTex = p_pathToTexture;
		if (p_pathToTexture != nullptr)
		{
			m_mat->setTexture(p_pathToTexture);
		}

		//m_mat_shadow = new puppy::Material(puppy::ShaderType::basic);

		//If we have not initialized the vao yet
		if (sm_instances[p_size] < 1)
		{
			setVaoUnit(p_size);
			//setVaoShadow(p_size);
		}
		++sm_instances[p_size];
	}

	UnitGraphic::UnitGraphic(nlohmann::json & p_json): kitten::K_Renderable(p_json)
	{
		m_pathToTex = LOOKUPSTRDEF("texture", "textures/unit/Default.tga");

		if (JSONHAS("unitsize")) {
			std::string temp = LOOKUPSTR("unitsize");
			if (temp == "point")
				m_size = unit::point;
			else if (temp == "cube")
				m_size = unit::UnitSize::cube;
		}

		m_mat = new puppy::Material(puppy::ShaderType::basic);
		m_mat->setTexture(m_pathToTex.c_str());

		//m_mat_shadow = new puppy::Material(puppy::ShaderType::basic);

		//If we have not initialized the vao yet
		if (sm_instances[m_size] < 1)
		{
			setVaoUnit(m_size);
			//setVaoShadow(p_size);
		}
		++sm_instances[m_size];
	}

	UnitGraphic::~UnitGraphic()
	{
		delete m_mat;
//		delete m_mat_shadow;
		if (--sm_instances[m_size] == 0)
		{
			delete sm_vao[m_size];
			delete sm_vao_shadow[m_size];
		}

		if (m_isEnabled)
		{
			removeFromDynamicRender();
		}
	}

	void UnitGraphic::setTexture(const char * p_pathToTex)
	{
		m_mat->setTexture(p_pathToTex);
		m_pathToTex = p_pathToTex;
	}

	std::string UnitGraphic::getTexturePath()
	{
		return m_pathToTex;
	}

	void UnitGraphic::start()
	{
		addToDynamicRender();
	}

	void UnitGraphic::onEnabled()
	{
		addToDynamicRender();
	}

	void UnitGraphic::onDisabled()
	{
		removeFromDynamicRender();
	}

	void UnitGraphic::render(kitten::Camera* p_cam)
	{
		m_mat->apply();
		
		//Set world matrix
		glm::mat4 wvp = p_cam->getOrtho() * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//render
		sm_vao[m_size]->drawArrays(GL_TRIANGLES);

		//m_mat_shadow->apply();
		//sm_vao_shadow[m_size]->drawArrays(GL_TRIANGLE_FAN);
	}

	void UnitGraphic::setVaoUnit(const UnitSize p_size)
	{
		//setup the vao for unit
		float height, width;
		switch (p_size)
		{
		case unit::point:
			height = 1.6f;
			width = 0.8f;
			break;
		case unit::cube:
			height = 2.8f;
			width = 1.5f;
			break;
		}
		float x = width / 2;
		float y = height / 2;
		float z = 0.0f;
		puppy::TexturedVertex verts[] =
		{
		{ -x, -y, z,		0.0f, 0.0f },
		{ -x, y, z,			0.0f, 1.0f },
		{ x, y, z,			1.0f, 1.0f },
		{ x, y, z,			1.0f, 1.0f },
		{ x, -y, z,		1.0f, 0.0f },
		{ -x, -y, z,		0.0f, 0.0f },
		};

		sm_vao[p_size] = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
	}
	void UnitGraphic::setVaoShadow(const UnitSize p_size)
	{
		std::vector<puppy::NormalVertex> v;
		int segments = 180;
		float r = 0;//radius
		switch (p_size)
		{
		case unit::point:
			r = 0.5f;
			break;
		case unit::cube:
			r = 0.8f;
			break;
		}

		v.push_back({ 0.5f,0,0 });//origin

		for (int i = 0; i < segments; i++)
		{
			float theta = 2.0f * 3.1415926f * float(i) / float(segments);//get the current angle

			float x = r * cosf(theta);//calculate the x component
			float z = r * sinf(theta);//calculate the z component

			v.push_back({ x+0.5f,0,z });
		}

		//sm_vao_shadow[p_size] = new puppy::VertexEnvironment(&v[0], puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), v.size());
	}
}
