#pragma once
#include <vector>
#include <string>

#include "Emitter.h"
#include "puppy\P_Common.h"
#include "kitten\Camera.h"
#include "pugixml\pugixml.hpp"

namespace puppy
{

	class Effect
	{
	private:
		enum PlayState {playing, paused, stopped};

		PlayState m_state;
		std::vector<Emitter*> m_emitters;
		
		std::string m_xmlPath;
	public:
		Effect(const char* p_pathToXML);
		virtual ~Effect();

		void refreshXML();

		void update(float p_delta);

		void render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj, const glm::vec3& p_position, const glm::vec3& p_scale);

		void play();
		void pause();
		void stop();
	};
}