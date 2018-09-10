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
		m_toRender.push_back(p_toAdd);
	}

	void Renderer::removeFromRender(kitten::Renderable* p_toRemove) 
	{
		for (auto it = m_toRender.begin(); it != m_toRender.end(); ++it)
		{
			if (*it == p_toRemove)
			{
				m_toRender.erase(it);
			}
		}
	}

	//public static
	void Renderer::renderAll(const glm::mat4& p_viewProj)
	{
		for (auto it = m_toRender.begin(); it != m_toRender.end(); ++it)
		{
			(*it)->render(p_viewProj);
		}
	}

	//public static
	void Renderer::removeAll()
	{
		m_toRender.clear();
	}
}