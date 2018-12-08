#pragma once

#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "kitten\K_Component.h"
#include "_Project\LerpController.h"

#include "unit\UnitCommon.h"
#include "unit\Unit.h"

#define HEALTH_MAT_TEXTURE_PATH "textures/ui/emerald.png"
#define DAMAGE_MAT_TEXTURE_PATH "textures/ui/red_quilt.jpg"

namespace unit
{
	class UnitHealthBar : public kitten::K_Component
	{
	private:
		static puppy::Material* m_healthMat;
		static puppy::Material* m_damageMat;
		static unsigned int instances;

		Unit* m_attachedUnit;
		float m_oldHealthPercent;

		float m_lerpTimeScalar = 10.0f;
		LerpController* m_foregroundLerpController;


		virtual void start() override;

		virtual bool hasUpdate() const override { return true; };
		virtual void update() override;
	public:
		UnitHealthBar(const glm::vec2& p_offset, float p_lerpTimeScalar = 10.0f);
		~UnitHealthBar();
	};
}