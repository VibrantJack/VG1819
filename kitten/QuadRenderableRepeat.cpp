#include "QuadRenderableRepeat.h"
#include "puppy\P_Common.h"
#include "puppy\StaticRenderables.h"
#include "puppy\Renderer.h"
#include "K_ComponentManager.h"

namespace kitten
{
	QuadRenderableRepeat::QuadRenderableRepeat(const std::string& p_texPath, bool p_isStatic, bool p_texRepeat, GLfloat p_uRepeat, GLfloat p_vRepeat)
		:
		m_isStatic(p_isStatic),
		m_isRenderingStatic(false),
		m_texRepeat(p_texRepeat),
		m_uRepeat(p_uRepeat),
		m_vRepeat(p_vRepeat),
		m_mat(puppy::ShaderType::basic_directional_light)
	{
		if (!p_texPath.empty())
		{
			m_staticTex = new puppy::Texture(p_texPath);
			m_mat.setTexture(m_staticTex);
			
		}

		//setup the vao
		puppy::TexturedVertex verts[] =
		{
			{ -0.5f, 0.0f, 0.5f,		0.0f,	   0.0f },
			{ 0.5f, 0.0f, 0.5f,			0.0f,	   m_vRepeat },
			{ 0.5f, 0.0f,-0.5f,			m_uRepeat, m_vRepeat },
			{ 0.5f, 0.0f,-0.5f,			m_uRepeat, m_vRepeat },
			{ -0.5f, 0.0f,-0.5f,		m_uRepeat, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f,	   0.0f },
		};

		m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic_directional_light), 6);
	}

	QuadRenderableRepeat::~QuadRenderableRepeat()
	{
		if (!m_isStatic)
		{
			if (m_isEnabled)
			{
				removeFromDynamicRender();
			}
		} else
		{
			if (m_isEnabled && m_isRenderingStatic)
			{
				removeFromStaticRender(m_staticTex);
			} else if (m_isEnabled)
			{
				removeFromDynamicRender();
			}
		}
	}

	void QuadRenderableRepeat::addToStaticRender()
	{
		puppy::TexturedVertex verts[] =
		{
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			{ 0.5f, 0.0f, 0.5f,			0.0f, m_vRepeat },
			{ 0.5f, 0.0f,-0.5f,			m_uRepeat, m_vRepeat },
			{ 0.5f, 0.0f,-0.5f,			m_uRepeat, m_vRepeat },
			{ -0.5f, 0.0f,-0.5f,		m_uRepeat, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
		};

		//Transform into world space
		puppy::StaticRenderables::putInWorldSpace(verts, 6, getTransform().getWorldTransform());

		K_Renderable::addToStaticRender(m_staticTex, verts, 6);
	}

	void QuadRenderableRepeat::setTexture(const char* p_pathToTex)
	{
		m_mat.setTexture(p_pathToTex);
	}


	void QuadRenderableRepeat::start()
	{
		if (m_isStatic)
		{
			m_isRenderingStatic = true;
			addToStaticRender();
		} 
		else
		{
			addToDynamicRender();
		}
	}

	void QuadRenderableRepeat::onDisabled()
	{
		if (m_isStatic)
		{
			removeFromStaticRender(m_staticTex);
		}
		else
		{
			removeFromDynamicRender();
		}
	}

	void QuadRenderableRepeat::onEnabled()
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
	void QuadRenderableRepeat::render(const glm::mat4& p_viewProj)
	{
		m_mat.apply();

		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat.setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		m_mat.setUniform("matAmbient", glm::vec3(1.0, 1.0, 1.0));
		m_mat.setUniform("worldIT", getTransform().getWorldIT());
		m_mat.setUniform("world", getTransform().getWorldTransform());

		//render
		m_vao->drawArrays(GL_TRIANGLES);

	}
}