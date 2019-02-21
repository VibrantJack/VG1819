#pragma once
#include "kitten/K_Common.h"
#include "UI/UIFrame.h"

//Rock
//This class handles the pointer in initiative tracker
//It will vibrate to make current unit more obvious

namespace unit
{
	class TrackerPointer : public kitten::K_Component
	{
	public:
		TrackerPointer();
		TrackerPointer(nlohmann::json& p_json);
		~TrackerPointer();

		void start() override;
		bool hasUpdate() const override;
		void update() override;
	private:
		const float m_originalX = 700.0f;
		const float m_originalY = 500.0f;
		float m_scale = 0.1f;
		const float m_maxScale = 0.13f;
		const float m_minScale = 0.07f;
		const float m_speed = 0.001f;
		const float m_y = 666.0f;
		const float m_x = 410.0f;
		bool m_scaleUp = true;

		void scale();
	};
}