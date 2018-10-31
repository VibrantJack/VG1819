#include "UIFrame.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"

namespace userinterface
{
	puppy::VertexEnvironment* UIFrame::sm_vao = nullptr;
	int UIFrame::sm_instances = 0;

	UIFrame::UIFrame(const char* p_pathToTex)
	{
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTex != nullptr)
		{
			m_mat->setTexture(p_pathToTex);
		}

		if (sm_instances < 1)
		{
			puppy::TexturedVertex verts[] =
			{
			{ 0.0, 0.0, 0, 0.0, 0.0 },
			{ 1.0, 0.0, 0, 2.0, 0.0 },
			{ 1.0, 1.0, 0, 2.0, 2.0 },

			{ 1.0, 1.0, 0, 2.0, 2.0 },
			{ 0.0, 1.0, 0, 2.0, 0.0 },
			{ 0.0, 0.0, 0, 0.0, 0.0 },
			};
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);

			++sm_instances;
		}
	}

	UIFrame::~UIFrame()
	{
		delete m_mat;
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}
		
		if (!m_isEnabled)
		{
			removeFromDynamicRender();
		}	
	}

	void UIFrame::start()
	{
		addToDynamicRender();
	}

	void UIFrame::onDisabled()
	{
		removeFromDynamicRender();
	}

	void UIFrame::onEnabled()
	{
		addToDynamicRender();
	}

	void UIFrame::render(const glm::mat4& p_ortho)
	{
		m_mat->apply();

		glm::mat4 wvp = p_ortho * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		sm_vao->drawArrays(GL_TRIANGLES);
	}

	void UIFrame::setTexture(const char* p_pathToTex)
	{
		//delete m_tex;
		//m_tex = new puppy::Texture(p_pathToTex);

		m_mat->setTexture(p_pathToTex);
	}
}
