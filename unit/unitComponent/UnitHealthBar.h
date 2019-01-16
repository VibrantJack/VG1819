#pragma once

#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "kitten\K_Component.h"
#include "_Project\LerpController.h"
#include "kitten\BarRenderable.h"
#include "kitten\K_GameObject.h"

#include "unit\UnitCommon.h"

#define HEALTH_MAT_P1_TEXTURE_PATH "textures/ui/saphire.png"
#define HEALTH_MAT_P2_TEXTURE_PATH "textures/ui/topaz.png"

#define DAMAGE_MAT_TEXTURE_PATH "textures/ui/healthbar_back.png"

#define BAR_X_SCALE 0.85f
#define BAR_Y_SCALE 0.10f

#define BACKGROUND_BAR_X_DIFFERENCE 0.05f
#define BACKGROUND_BAR_Y_DIFFERENCE 0.05f

#define BACKGROUND_BAR_X_SCALE (BAR_X_SCALE + BACKGROUND_BAR_X_DIFFERENCE)
#define BACKGROUND_BAR_Y_SCALE (BAR_Y_SCALE + BACKGROUND_BAR_Y_DIFFERENCE)

namespace unit
{
	class Unit;
	class UnitHealthBar : public kitten::K_Component
	{
	private:
		puppy::Material m_healthMat;
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

		LerpController* getForegroundBarLerpController() const;
	};
}