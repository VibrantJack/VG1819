#include "QuadRenderableBB.h"

namespace kitten
{
	puppy::VertexEnvironment* QuadRenderableBB::sm_vao = nullptr;
	unsigned int QuadRenderableBB::sm_instances = 0;


	QuadRenderableBB::QuadRenderableBB(const char* p_pathToTexture) : m_mat(puppy::ShaderType::billboarded_alphaTest)
	{
		if (sm_instances == 0)
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

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::billboarded_alphaTest), 6);
		}

		++sm_instances;

		if (p_pathToTexture != nullptr)
		{
			m_mat.setTexture(p_pathToTexture);
		}
	}

	QuadRenderableBB::~QuadRenderableBB()
	{
		--sm_instances;

		if (sm_instances == 0)
		{
			delete sm_vao;
			sm_vao = nullptr;
		}

		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void QuadRenderableBB::setTexture(const char* p_pathToTexture)
	{
		m_mat.setTexture(p_pathToTexture);
	}

	void QuadRenderableBB::start()
	{
		onEnabled();
	}

	void QuadRenderableBB::onEnabled()
	{
		addToDynamicRender();
	}

	void QuadRenderableBB::onDisabled()
	{
		removeFromDynamicRender();
	}

	void QuadRenderableBB::render(kitten::Camera* p_cam)
	{
		auto& transform = getTransform();

		glm::vec3 centerPos = transform.getTranslation();
		centerPos.x += 0.5f * transform.getLocalScale().x;

		m_mat.apply();

		m_mat.setUniform("mView", p_cam->getView());
		m_mat.setUniform("centerPos", centerPos);
		m_mat.setUniform("mViewProj", p_cam->getViewProj());
		m_mat.setUniform("size", (glm::vec2)transform.getLocalScale());

		sm_vao->drawArrays(GL_TRIANGLES);
	}
}