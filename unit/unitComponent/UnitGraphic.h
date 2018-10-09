#pragma once
#include "unit/UnitCommon.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include "kitten/Renderable.h"

//Rock
//a component with unit, it handle the unit's texture and animation

namespace unit
{
	enum UnitSize;
	class UnitGraphic : public kitten::Renderable
	{
	public:
		UnitGraphic(const UnitSize p_size, const char* p_pathToTexture = nullptr);
		~UnitGraphic();
		void setTexture(const char* p_pathToTex);
		void render(const glm::mat4& p_viewProj) override;

	private:
		puppy::Material* m_mat;
		puppy::Material* m_mat_shadow;
		unit::UnitSize m_size;
		static std::map<unit::UnitSize, puppy::VertexEnvironment*> sm_vao;
		static std::map<unit::UnitSize, puppy::VertexEnvironment*> sm_vao_shadow;
		static std::map<unit::UnitSize, int> sm_instances;

		void setVaoUnit(const UnitSize p_size);
		void setVaoShadow(const UnitSize p_size);
	};

}
