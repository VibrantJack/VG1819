#pragma once
#include <vector>
#include <string>

#include "Emitter.h"
#include "puppy\P_Common.h"
#include "CallumMacKenzie_As3\SceneManagement\Camera.h"
#include "CallumMacKenzie_As3\pugixml\pugixml.hpp"

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
		void render(scene::Camera* p_cam);
		void play();
		void pause();
		void stop();
	};
}