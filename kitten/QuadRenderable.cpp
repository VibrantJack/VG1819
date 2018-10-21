#include "QuadRenderable.h"
#include "puppy\P_Common.h"
#include "puppy\StaticRenderables.h"
#include "puppy\Renderer.h"
#include "K_ComponentManager.h"

namespace kitten
{
	puppy::VertexEnvironment* QuadRenderable::sm_vao = nullptr;
	int QuadRenderable::sm_instances = 0;

	QuadRenderable::QuadRenderable(const char* p_pathToTexture, bool p_isStatic) 
		: 
		m_isStatic(p_isStatic),
		m_colorTint(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
	{
		if (!p_isStatic)
		{
			m_mat = new puppy::Material(puppy::ShaderType::colorTint_alphaTest);
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
				sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::colorTint_alphaTest), 6);
			}
			++sm_instances;
			
			puppy::Renderer::getInstance()->addToRender(this);
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

			if (m_isEnabled)
			{
				puppy::Renderer::getInstance()->removeFromRender(this);
			}
		}
		else
		{
			if (m_isEnabled)
			{
				puppy::StaticRenderables::getInstance()->removeFromRender(this, m_tex);
			}
			
			delete m_tex;
		}
	}

	void QuadRenderable::addToStaticRender()
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

		puppy::StaticRenderables::getInstance()->addToRender(this, m_tex, verts, 6);
	}

	void QuadRenderable::start()
	{
		if (m_isStatic)
		{
			addToStaticRender();
		}
	}

	void QuadRenderable::onDisabled()
	{
		if (m_isStatic)
		{
			puppy::StaticRenderables::getInstance()->removeFromRender(this, m_tex);
		}
		else
		{
			puppy::Renderer::getInstance()->removeFromRender(this);
		}
	}

	void QuadRenderable::onEnabled()
	{
		if (m_isStatic)
		{
			addToStaticRender();
		}
		else
		{
			puppy::Renderer::getInstance()->addToRender(this);
		}
	}

	void QuadRenderable::setTexture(const char* p_pathToTex)
	{
		if (!m_isStatic)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else if(!m_hasStarted)
		{
			delete m_tex;
			m_tex = new puppy::Texture(p_pathToTex);
		}
	}

	void QuadRenderable::setColorTint(const glm::vec4& p_vec4)
	{
		m_colorTint = p_vec4;
	}

	//Only called if not static
	void QuadRenderable::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();
		
		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//Set color tint
		//m_colorTint = glm::vec4(0.0f, 0.0f, 0.5f, 1.0f);
		m_mat->setUniform(COLOR_TINT_UNIFORM_NAME, m_colorTint);

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}