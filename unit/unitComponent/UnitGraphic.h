#pragma once
#include "unit/UnitCommon.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include "kitten/K_Renderable.h"

//Rock
//a component with unit, it handle the unit's texture and animation

namespace unit
{
	enum UnitSize;
	class UnitGraphic : public kitten::K_Renderable
	{
	public:
		UnitGraphic(const UnitSize p_size, const char* p_pathToTexture = nullptr);
		UnitGraphic(nlohmann::json& p_json);
		~UnitGraphic();

		void setTexture(const char* p_pathToTex);
		void render(kitten::Camera* p_cam) override;
		std::string getTexturePath();
	private:
		puppy::Material* m_mat;
		puppy::Material* m_mat_shadow;
		unit::UnitSize m_size;
		std::string m_pathToTex;
		static std::map<unit::UnitSize, puppy::VertexEnvironment*> sm_vao;
		static std::map<unit::UnitSize, puppy::VertexEnvironment*> sm_vao_shadow;
		static std::map<unit::UnitSize, int> sm_instances;

		void setVaoUnit(const UnitSize p_size);
		void setVaoShadow(const UnitSize p_size);

		virtual void start() override;
		virtual void onEnabled() override;
		virtual void onDisabled() override;
	};

}
