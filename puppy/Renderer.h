#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//-----------------------------------------------------------------------------

#include "kitten\Renderable.h"
#include "kitten\K_ParticleSystem.h"
#include "kitten\UIRenderable.h"
#include "kitten\Camera.h"

#include "P_Common.h"

#include <unordered_set>

namespace puppy
{
	class P_Instance;

	class Renderer
	{
		friend class P_Instance;
		friend class kitten::Renderable;
		friend class kitten::UIRenderable;
		friend class kitten::K_ParticleSystem;
	private:
		//Singleton related
		Renderer();
		~Renderer();
		static Renderer* sm_instance;
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new Renderer(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_set<kitten::Renderable*> m_toRender;
		std::unordered_set<kitten::UIRenderable*> m_uiToRender;
		std::unordered_set<kitten::K_ParticleSystem*> m_particlesToRender;

		void addToRender(kitten::Renderable* p_toAdd);
		void removeFromRender(kitten::Renderable* p_toRemove);

		void addUIToRender(kitten::UIRenderable* p_toAdd);
		void removeUIFromRender(kitten::UIRenderable* p_toRemove);

		void addParticleToRender(kitten::K_ParticleSystem* p_toAdd);
		void removeParticleToRender(kitten::K_ParticleSystem* p_toRemove);

		void renderAll(kitten::Camera* p_cam);
	public:
		static Renderer* getInstance() { return sm_instance; };

		void removeAll();

		void setBlendFunc(GLenum p_sourceFactor, GLenum p_destinationFactor);
		void setBlendEquation(GLenum p_mode) const;
	};
}