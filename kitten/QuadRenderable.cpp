#include "QuadRenderable.h"
#include "puppy\P_Common.h"
#include "puppy\StaticRenderables.h"
#include "puppy\Renderer.h"
#include "K_ComponentManager.h"

namespace kitten
{
	puppy::VertexEnvironment* QuadRenderable::sm_vao = nullptr;
	int QuadRenderable::sm_instances = 0;

	QuadRenderable::QuadRenderable(const char* p_pathToTexture, bool p_isStatic) : m_isStatic(p_isStatic)
	{
		if (!p_isStatic)
		{
			m_mat = new puppy::TextureBlendMaterial();
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
				removeFromDynamicRender();
			}
		}
		else
		{
			if (m_isEnabled)
			{
				removeFromStaticRender(m_tex);
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

		Renderable::addToStaticRender(m_tex, verts, 6);
	}

	void QuadRenderable::addTexture(const char* p_pathToTex, const float& p_weight)
	{
		m_mat->addTexture(p_pathToTex, p_weight);
	}

	void QuadRenderable::removeTexture(const char* p_pathToTex)
	{
		m_mat->removeTexture(p_pathToTex);
	}

	void QuadRenderable::changeWeight(const char* p_pathToTex, const float& p_weight)
	{
		m_mat->changeWeight(p_pathToTex, p_weight);
	}

	void QuadRenderable::start()
	{
		if (m_isStatic)
		{
			addToStaticRender();
		}
		else
		{
			addToDynamicRender();
		}
	}

	void QuadRenderable::onDisabled()
	{
		if (m_isStatic)
		{
			removeFromStaticRender(m_tex);
		}
		else
		{
			removeFromDynamicRender();
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
			addToDynamicRender();
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