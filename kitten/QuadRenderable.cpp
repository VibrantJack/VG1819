#include "QuadRenderable.h"
#include "puppy\P_Common.h"
#include "puppy\StaticRenderables.h"
#include "K_ComponentManager.h"

namespace kitten
{
	puppy::VertexEnvironment* QuadRenderable::sm_vao = nullptr;
	int QuadRenderable::sm_instances = 0;

	QuadRenderable::QuadRenderable(const char* p_pathToTexture, bool p_isStatic) : m_isStatic(p_isStatic)
	{
		if (!p_isStatic)
		{
			m_mat = new puppy::Material(puppy::ShaderType::basic);
			if (p_pathToTexture != nullptr)
			{
				m_mat->setTexture(p_pathToTexture);
			}

			//If we have not initialized the vao yet
			if (sm_instances < 1)
			{
				//setup the vao
				puppy::TexturedVertex verts[] =
				{
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
				{ 0.5f, 0.0f, 0.5f,			0.0f, 1.0f },
				{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
				{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
				{ -0.5f, 0.0f,-0.5f,		1.0f, 0.0f },
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
				};
				sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 36);
			}
			++sm_instances;
		}
		else
		{
			m_tex = new puppy::Texture(p_pathToTexture);
		}
	}

	QuadRenderable::~QuadRenderable()
	{
		if (!m_isStatic)
		{
			delete m_mat;
			if (--sm_instances == 0)
			{
				delete sm_vao;
			}
		}
	}

	void QuadRenderable::start()
	{
		if (m_isStatic)
		{
			puppy::TexturedVertex verts[] =
			{
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			{ 0.5f, 0.0f, 0.5f,			0.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
			{ -0.5f, 0.0f,-0.5f,		1.0f, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			};

			//Transform into world space
			puppy::StaticRenderables::putInWorldSpace(verts, 6, getTransform().getWorldTransform());

			puppy::StaticRenderables::getInstance()->addToRender(m_tex, verts, 6);
			K_ComponentManager::getInstance()->destroyComponent(this);
		}
		
	}

	void QuadRenderable::setTexture(const char* p_pathToTex)
	{
		if (!m_isStatic)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else
		{
			delete m_tex;
			m_tex = new puppy::Texture(p_pathToTex);
		}
	}

	//Only called if not static
	void QuadRenderable::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();
		
		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}