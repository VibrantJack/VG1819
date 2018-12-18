#pragma once

#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "kitten\K_Component.h"
#include "_Project\LerpController.h"
#include "kitten\BarRenderable.h"

#include "unit\UnitCommon.h"
#include "unit\Unit.h"

#define HEALTH_MAT_TEXTURE_PATH "textures/ui/emerald.png"
#define DAMAGE_MAT_TEXTURE_PATH "textures/ui/red_quilt.jpg"

#define BAR_X_SCALE 0.85f
#define BAR_Y_SCALE 0.10f

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

		float m_lerpTimeScalar = 4.0f;
		LerpController* m_foregroundLerpController;
		
		kitten::BarRenderable* m_foregroundBar;

		const glm::vec3 m_offset;
		const float m_rotation;

		virtual void start() override;
	public:
		UnitHealthBar(const glm::vec3& p_offset, float p_lerpTimeScalar = 4.0f, float p_rotation = -45);
		~UnitHealthBar();

		void updateBar();
	};
}