#include "QuadRenderable.h"
#include "puppy\P_Common.h"
#include "puppy\StaticRenderables.h"
#include "puppy\Renderer.h"
#include "K_ComponentManager.h"

namespace kitten
{
	puppy::VertexEnvironment* QuadRenderable::sm_vao = nullptr;
	int QuadRenderable::sm_instances = 0;
	std::vector<unsigned int> QuadRenderable::sm_indicies;

	QuadRenderable::QuadRenderable(const std::string& p_texPath, bool p_isStatic) : m_isStatic(p_isStatic), m_isRenderingStatic(false), m_mat(true)
	{
		if (!p_texPath.empty())
		{
			m_mat.setTexture(p_texPath.c_str());
		}

		m_mat.setMatAmbient(glm::vec4(1.0, 1.0, 1.0, 1.0));
		m_mat.setMatDiffuse(glm::vec4(0.4, 0.4, 0.4, 1.0));

		//If we have not initialized the vao yet
		if (sm_instances < 1)
		{
			if (sm_indicies.empty())
			{
				sm_indicies.push_back(0);
				sm_indicies.push_back(1);
				sm_indicies.push_back(2);
				sm_indicies.push_back(2);
				sm_indicies.push_back(3);
				sm_indicies.push_back(0);
			}

			//setup the vao
			puppy::NormalVertex verts[] =
			{
				{ -0.5f, 0.0f, 0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f },
				{ 0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f },
				{ 0.5f, 0.0f,-0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f },
				{ -0.5f, 0.0f,-0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f },
			};
			sm_vao = new puppy::VertexEnvironment(verts, sm_indicies.data(), puppy::ShaderManager::getShaderProgram(puppy::ShaderType::texture_blend_zero), 4, 6);
		}

		++sm_instances;
	}

	QuadRenderable::~QuadRenderable()
	{
		onDisabled();

		if (--sm_instances == 0)
		{
			delete sm_vao;
			sm_indicies.clear();
		}
	}

	void QuadRenderable::addToStaticRender()
	{
		puppy::NormalVertex verts[] =
		{
			{ -0.5f, 0.0f, 0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f },
			{ 0.5f, 0.0f, 0.5f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f },
			{ -0.5f, 0.0f,-0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f },
		};

		//Transform into world space
		puppy::StaticRenderables::putInWorldSpace(verts, 4, getTransform().getWorldTransform(), getTransform().getRotation());

		K_Renderable::addToStaticRender(m_mat, verts, &sm_indicies, 4);
	}

	void QuadRenderable::setTexture(const char* p_pathToTex)
	{
		if (m_isStatic && m_isEnabled)
		{
			if (m_isRenderingStatic)
			{
				removeFromStaticRender(m_mat, true);
			}

			m_mat.setTexture(p_pathToTex);

			addToStaticRender();
			m_isRenderingStatic = true;
		}
		else
		{
			m_mat.setTexture(p_pathToTex);
		}
	}

	void QuadRenderable::addTexture(puppy::Texture* p_tex, const float& p_weight)
	{
		if (m_isStatic && m_isEnabled)
		{
			if (m_isRenderingStatic)
			{
				removeFromStaticRender(m_mat, true);
			}

			m_mat.addTexture(p_tex, p_weight);

			addToStaticRender();
			m_isRenderingStatic = true;
		}
		else
		{
			m_mat.addTexture(p_tex, p_weight);
		}
	}

	void QuadRenderable::removeTexture(puppy::Texture* p_tex)
	{
		if (m_isStatic && m_isEnabled)
		{
			if (m_isRenderingStatic)
			{
				removeFromStaticRender(m_mat, true);
			}

			m_mat.removeTexture(p_tex);

			addToStaticRender();
			m_isRenderingStatic = true;
		}
		else
		{
			m_mat.removeTexture(p_tex);
		}
	}

	void QuadRenderable::changeWeight(puppy::Texture* p_tex, const float& p_weight)
	{
		if (m_isStatic && m_isEnabled)
		{
			if (m_isRenderingStatic)
			{
				removeFromStaticRender(m_mat, true);
			}

			m_mat.changeWeight(p_tex, p_weight);

			addToStaticRender();
			m_isRenderingStatic = true;
		}
		else
		{
			m_mat.changeWeight(p_tex, p_weight);
		}
	}

	void QuadRenderable::start()
	{
		onEnabled();
	}

	void QuadRenderable::onDisabled()
	{
		if (m_isStatic && m_isRenderingStatic)
		{
			removeFromStaticRender(m_mat, true);
			m_isRenderingStatic = false;
		}
		else if (!m_isStatic)
		{
			removeFromDynamicRender();
		}
	}

	void QuadRenderable::onEnabled()
	{
		if (m_isStatic && m_mat.getNumberOfTextures() > 0)
		{
			addToStaticRender();
			m_isRenderingStatic = true;
		}
		else if (!m_isStatic)
		{
			addToDynamicRender();
		}
	}

	//Only called if not static
	void QuadRenderable::render(kitten::Camera* p_cam)
	{
		m_mat.apply();
		
		//Set world matrix
		glm::mat4 wvp = p_cam->getViewProj() * getTransform().getWorldTransform();
		m_mat.setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
		
	}
}