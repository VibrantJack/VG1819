#include "Renderer.h"


namespace puppy
{
	Renderer* Renderer::sm_instance = nullptr;

	Renderer::Renderer()
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::addToRender(kitten::Renderable* p_toAdd) 
	{	
		m_toRender.insert(p_toAdd);
	}

	void Renderer::removeFromRender(kitten::Renderable* p_toRemove) 
	{
		m_toRender.erase(p_toRemove);
	}

	void Renderer::addUIToRender(kitten::UIRenderable* p_toAdd)
	{
		m_uiToRender.insert(p_toAdd);
	}

	void Renderer::removeUIFromRender(kitten::UIRenderable* p_toRemove)
	{
		m_uiToRender.erase(p_toRemove);
	}

	void Renderer::renderAll(kitten::Camera* p_cam)
	{
		const glm::mat4& viewProj = p_cam->getViewProj();

		auto end = m_toRender.end();
		for (auto it = m_toRender.begin(); it != end; ++it)
		{
			(*it)->render(viewProj);
		}

		//UI

		const glm::mat4& ortho = p_cam->getOrtho();

		auto uiEnd = m_uiToRender.end();
		for (auto it = m_uiToRender.begin(); it != uiEnd; ++it)
		{
			(*it)->render(ortho);
		}
	}

	void Renderer::removeAll()
	{
		m_toRender.clear();
		m_uiToRender.clear();
	}
}