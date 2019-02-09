#include "BarRenderable.h"

namespace kitten
{
	puppy::VertexEnvironment* BarRenderable::sm_vao = nullptr;
	unsigned int BarRenderable::instances = 0;


	BarRenderable::BarRenderable(const char* p_pathToTexture, bool p_isHealthBar) : m_isHealthBar(p_isHealthBar), m_mat(puppy::ShaderType::billboarded_u_scale)
	{
		if (instances == 0)
		{
			puppy::TexturedVertex verts[] =
			{
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f },
				{ 0.0f,  0.5f, 0.0f,		0.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f, -0.5f, 0.0f,		1.0f, 0.0f },
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f }
			};

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::healthbar), 6);
		}

		++instances;

		if (p_pathToTexture != nullptr)
		{
			m_mat.setTexture(p_pathToTexture);
		}
		
		if (p_isHealthBar)
		{
			m_mat = puppy::Material(puppy::ShaderType::healthbar);
		}
	}

	BarRenderable::~BarRenderable()
	{
		--instances;

		if (instances == 0)
		{
			delete sm_vao;
			sm_vao = nullptr;
		}

		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void BarRenderable::setIsHealthBar(bool p_isHealthBar)
	{
		m_isHealthBar = p_isHealthBar;

		if (p_isHealthBar)
		{
			m_mat = puppy::Material(puppy::ShaderType::healthbar);
		}
	}

	void BarRenderable::setTexture(const char* p_pathToTexture)
	{
		m_mat.setTexture(p_pathToTexture);
	}

	void BarRenderable::start()
	{
		onEnabled();
		m_startXScale = getTransform().getLocalScale().x;
	}

	void BarRenderable::onEnabled()
	{
		addToDynamicRender();
	}

	void BarRenderable::onDisabled()
	{
		removeFromDynamicRender();
	}

	void BarRenderable::render(kitten::Camera* p_cam)
	{
		auto& transform = getTransform();
		
		glm::vec3 centerPos = transform.getTranslation();
		if (m_isHealthBar)
		{
			centerPos.x += 0.5f * m_startXScale;
		}
		else
		{
			centerPos.x += 0.5f * transform.getLocalScale().x;
		}

		m_mat.apply();
		
		m_mat.setUniform("mView", p_cam->getView());
		m_mat.setUniform("centerPos", centerPos);
		m_mat.setUniform("mViewProj", p_cam->getViewProj());

		if (m_isHealthBar)
		{
			glm::vec2 size(m_startXScale, transform.getLocalScale().y);
			m_mat.setUniform("size", size);
		}
		else
		{
			m_mat.setUniform("size", (glm::vec2)transform.getLocalScale());
		}
		

		if (m_isHealthBar)
		{
			m_mat.setUniform("healthPercent", getTransform().getLocalScale().x / m_startXScale);
		}

		sm_vao->drawArrays(GL_TRIANGLES);
	}
}