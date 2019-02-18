#include "Renderer.h"
#include "kitten\K_UIRenderable.h"


#define DEFAULT_BLEND_SOURCE_FACTOR  GL_SRC_ALPHA
#define DEFAULT_BLEND_DESTINATION_FACTOR GL_ONE

namespace puppy
{
	Renderer* Renderer::sm_instance = nullptr;

	Renderer::Renderer()
	{
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(DEFAULT_BLEND_SOURCE_FACTOR, DEFAULT_BLEND_DESTINATION_FACTOR);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::setBlendEquation(GLenum p_mode) const
	{
		glBlendEquation(p_mode);
	}

	void Renderer::setBlendFunc(GLenum p_sourceFactor, GLenum p_destinationFactor)
	{
		glBlendFunc(p_sourceFactor, p_destinationFactor);
	}

	void Renderer::addToRender(P_Renderable* p_toAdd) 
	{	
		m_toRender.insert(p_toAdd);
	}

	void Renderer::removeFromRender(P_Renderable* p_toRemove) 
	{
		m_toRender.erase(p_toRemove);
	}

	void Renderer::addUIToRender(kitten::K_RenderNode* p_toAdd)
	{
		m_uiToRender.insert(p_toAdd);
	}

	bool Renderer::removeUIFromRender(kitten::K_RenderNode* p_toRemove)
	{
		if (m_uiToRender.find(p_toRemove) == m_uiToRender.end())
		{
			return false;
		}
		else
		{
			m_uiToRender.erase(p_toRemove);
			return true;
		}
	}

	void Renderer::addParticleToRender(kitten::K_ParticleSystem* p_toAdd)
	{
		m_particlesToRender.insert(p_toAdd);
	}

	void Renderer::removeParticleFromRender(kitten::K_ParticleSystem* p_toRemove)
	{
		m_particlesToRender.erase(p_toRemove);
	}

	void Renderer::renderAll(kitten::Camera* p_cam)
	{
		const glm::mat4& viewProj = p_cam->getViewProj();

		//3D objects

		auto end = m_toRender.end();
		for (auto it = m_toRender.begin(); it != end; ++it)
		{
			(*it)->render(p_cam);
		}

		//Particles and Transparent UI

		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glm::mat4 viewInverse = (glm::mat4)p_cam->getMat3ViewInverse();

		glBlendFunc(DEFAULT_BLEND_SOURCE_FACTOR, DEFAULT_BLEND_DESTINATION_FACTOR);

		auto particlesEnd = m_particlesToRender.cend();
		for (auto it = m_particlesToRender.cbegin(); it != particlesEnd; ++it)
		{
			(*it)->render(viewInverse, viewProj);
		}

		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

		auto uiEnd = m_uiToRender.end();
		for (auto it = m_uiToRender.begin(); it != uiEnd; ++it)
		{
			renderTransparentUI(p_cam, (*it));
		}

		//blend off
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

		//UI
		const glm::mat4& ortho = p_cam->getOrtho();

		for (auto it = m_uiToRender.begin(); it != uiEnd; ++it)
		{
			renderUI(p_cam, (*it));
		}
	}

	void Renderer::renderUI(kitten::Camera* p_cam, kitten::K_RenderNode* p_toRender) const
	{
		if (p_toRender->isEnabled())
		{
			const auto& uiRenderables = p_toRender->m_uiRenderables;
			if (!uiRenderables.empty())
			{
				auto end = uiRenderables.cend();
				for (auto it = uiRenderables.cbegin(); it != end; ++it)
				{
					(*it)->uiRender(p_cam);
				}
			}

			const auto& childNodes = p_toRender->m_childRenderNodes;
			if (!childNodes.empty())
			{
				auto end = childNodes.cend();
				for (auto it = childNodes.cbegin(); it != end; ++it)
				{
					renderUI(p_cam, (*it));
				}
			}
		}
	}

	void Renderer::renderTransparentUI(kitten::Camera * p_cam, kitten::K_RenderNode * p_toRender) const
	{
		if (p_toRender->isEnabled())
		{
			const auto& uiRenderables = p_toRender->m_trasparentUIRenderables;
			if (!uiRenderables.empty())
			{
				auto end = uiRenderables.cend();
				for (auto it = uiRenderables.cbegin(); it != end; ++it)
				{
					(*it)->uiRender(p_cam);
				}
			}

			const auto& childNodes = p_toRender->m_childRenderNodes;
			if (!childNodes.empty())
			{
				auto end = childNodes.cend();
				for (auto it = childNodes.cbegin(); it != end; ++it)
				{
					renderTransparentUI(p_cam, (*it));
				}
			}
		}
	}

	void Renderer::removeAll()
	{
		m_toRender.clear();
		m_uiToRender.clear();
	}
}