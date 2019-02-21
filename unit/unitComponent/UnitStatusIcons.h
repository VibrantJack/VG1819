#pragma once

#include "kitten\K_ComponentManager.h"
#include "kitten\QuadRenderableBB.h"
#include "ability\status\Status.h"

#define ICON_SWAP_DELAY 2.0f;

namespace unit
{
	class UnitStatusIcons : public kitten::K_Component
	{
	private:
		kitten::QuadRenderableBB* m_statusIcon = nullptr;

		const glm::vec3 m_offset;
		const float m_rotation;
		float m_timeElapsed = ICON_SWAP_DELAY;

		Unit* m_unit = nullptr;

		int m_numBuffs = 0;
		int m_numDebuffs = 0;
		int m_numShields = 0;

		std::list<std::string> m_iconTexturePaths;
		int m_textureIndex = -1;
		
		virtual void start() override;

		virtual void onEnabled() override;
		virtual void onDisabled() override;

		virtual bool hasUpdate() const override { return true; };
		virtual void update() override;

		void checkActiveStatuses();

	public:
		// Only want to keep track of non-level up statuses
		std::unordered_set<ability::Status*> m_statusList;

		UnitStatusIcons(const glm::vec3& p_offset, float p_rotation = 45);
		~UnitStatusIcons();

		void addStatus(ability::Status* p_status);
		void removeStatus(ability::Status* p_status);
	};
}