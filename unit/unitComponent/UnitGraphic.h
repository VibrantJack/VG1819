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
	private:
		puppy::Material* m_mat;

		static puppy::VertexEnvironment* sm_vao;
		puppy::Texture* m_tex;
		std::vector<puppy::TexturedVertex> m_verts;

	public:
		UnitGraphic(const UnitSize p_size, const char* p_pathToTexture = nullptr);
		~UnitGraphic();
		void setTexture(const char* p_pathToTex);
		void render(const glm::mat4& p_viewProj) override;
	};

}
