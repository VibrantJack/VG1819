#include "UI_ElementComponent.h"

namespace userinterface
{
	puppy::VertexEnvironment* UI_ElementComponent::sm_vao = nullptr;
	int UI_ElementComponent::sm_instances = 0;

	UI_ElementComponent::UI_ElementComponent()
	{
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		
		m_mat->setTexture("textures\tiles\MISSING.tga");

		if (sm_instances < 1)
		{
			puppy::TexturedVertex verts[] =
			{
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				{ 1.0f, 0.0f, 1.0f, 0.0f },
				{ 1.0f, 1.0f, 1.0f, 1.0f },

				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f, 0.0f, 1.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			};
		}
	}

	UI_ElementComponent::~UI_ElementComponent()
	{
		delete m_mat;
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}
	}

	void UI_ElementComponent::setTexture(const char* p_pathToTex)
	{
		m_mat->setTexture(p_pathToTex);
	}

	void UI_ElementComponent::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();

		//set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);
		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}