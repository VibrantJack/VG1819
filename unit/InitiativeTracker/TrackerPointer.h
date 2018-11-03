#pragma once
#include "kitten/K_Common.h"
#include "userinterface/UIFrame.h"

//Rock
//This class handles the pointer in initiative tracker
//It will vibrate to make current unit more obvious

namespace unit
{
	class TrackerPointer : public kitten::K_Component
	{
	public:
		TrackerPointer();
		~TrackerPointer();

		void start() override;
		bool hasUpdate() const override;
		void update() override;
	private:
		float m_scale = 0.1f;
		float m_maxScale = 0.13f;
		float m_minScale = 0.07f;
		float m_speed = 0.001f;
		float m_y = 0.9f;
		float m_x = -0.35f;
		bool m_scaleUp = true;

		void scale();
	};
}