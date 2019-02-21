#pragma once

#include "kitten\K_Component.h"
#include <glm/glm.hpp>
#include <unordered_set>
#include "kitten\event_system\EventManager.h"

namespace kitten
{
	class Clickable;

	class ClickableBox : public K_Component, public TransformScaleListener
	{
	private:
		glm::vec3 m_minPoint, m_maxPoint;
		glm::vec3 m_originalMinPoint, m_originalMaxPoint;

		std::unordered_set<Clickable*> m_listeners;

		void onEnabled() override;
		void onDisabled() override;

		bool m_gamePaused;
	public:
		ClickableBox(nlohmann::json& p_json);
		ClickableBox(const glm::vec3& p_minPoint, const glm::vec3& p_maxPoint);
		~ClickableBox();

		void start() override;
		

		virtual void onScaleChanged(const glm::vec3& p_newScale) override;

		void addClickable(Clickable* p_toAdd);
		void removeClickable(Clickable* p_toRemove);

		const glm::vec3& getMinPoint() const { return m_minPoint; };
		const glm::vec3& getMaxPoint() const { return m_maxPoint; };

		const glm::vec3& getOriginalMaxPoint() const { return m_originalMaxPoint; };
		const glm::vec3& getOriginalMinPoint() const { return m_originalMinPoint; };

		void onHoverStart();
		void onClick();
		void onHoverEnd();

		void toggleGamePausedListener(kitten::Event::EventType p_type, kitten::Event* p_data);
	};
}