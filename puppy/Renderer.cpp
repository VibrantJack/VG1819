#include "Renderer.h"

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
			(*it)->render(viewProj);
		}

		//Particles
		
		glEnable(GL_BLEND);
		//glDisable(GL_DEPTH_TEST);

		glm::mat4 viewInverse = (glm::mat4)p_cam->getMat3ViewInverse();

		auto particlesEnd = m_particlesToRender.cend();
		for (auto it = m_particlesToRender.cbegin(); it != particlesEnd; ++it)
		{
			(*it)->render(viewInverse, viewProj);
		}

		//blend off
		glDisable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);

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