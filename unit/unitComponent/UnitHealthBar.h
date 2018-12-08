#pragma once

#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include "kitten\Renderable.h"

#include "unit\UnitCommon.h"
#include "unit\Unit.h"

#define HEALTH_MAT_TEXTURE_PATH "textures/ui/emerald.png"
#define DAMAGE_MAT_TEXTURE_PATH "textures/ui/red_quilt.jpg"

namespace unit
{
	class UnitHealthBar : public kitten::Renderable
	{
	private:
		static puppy::VertexEnvironment* m_backVao;
		static puppy::VertexEnvironment* m_foreVao;
		static puppy::Material* m_healthMat;
		static puppy::Material* m_damageMat;
		static unsigned int instances;

		Unit* m_attachedUnit;
		const glm::mat4 m_offset;


		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	public:
		UnitHealthBar(const glm::vec2& p_offset);
		~UnitHealthBar();

		virtual void render(const glm::mat4& p_viewProj) override;
	};
}