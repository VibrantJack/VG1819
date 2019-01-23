#pragma once
//-----------------------------------------------------------------------------
// File:			Renderer.h
// Original Author:	Callum MacKenzie
//-----------------------------------------------------------------------------

#include "kitten\K_ParticleSystem.h"
#include "kitten\Camera.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_RenderNode.h"

#include "P_Common.h"
#include "P_Renderable.h"

#include <unordered_set>

namespace kitten
{
	class K_RenderNode;
}

namespace puppy
{
	class P_Instance;
	class P_Renderable;
	class P_UIRenderable;

	class Renderer
	{
		friend class P_Instance;
		friend class P_Renderable;
		friend class kitten::K_RenderNode;
		friend class kitten::K_ParticleSystem;
	private:
		//Singleton related
		Renderer();
		~Renderer();
		static Renderer* sm_instance;
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new Renderer(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };

		std::unordered_set<P_Renderable*> m_toRender;
		std::unordered_set<kitten::K_RenderNode*> m_uiToRender;
		std::unordered_set<kitten::K_ParticleSystem*> m_particlesToRender;

		void addToRender(P_Renderable* p_toAdd);
		void removeFromRender(P_Renderable* p_toRemove);

		void addUIToRender(kitten::K_RenderNode* p_toAdd);
		void removeUIFromRender(kitten::K_RenderNode* p_toRemove);

		void addParticleToRender(kitten::K_ParticleSystem* p_toAdd);
		void removeParticleFromRender(kitten::K_ParticleSystem* p_toRemove);

		void renderAll(kitten::Camera* p_cam);
		void renderUI(kitten::Camera* p_cam, kitten::K_RenderNode* p_toRender) const; //helper method for recursive rendering
	public:
		static Renderer* getInstance() { return sm_instance; };

		void removeAll();

		void setBlendFunc(GLenum p_sourceFactor, GLenum p_destinationFactor);
		void setBlendEquation(GLenum p_mode) const;
	};
}