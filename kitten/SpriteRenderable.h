#pragma once
#include "Renderable.h"
#include "puppy\VertexEnvironment.h"
#include <unordered_map>

namespace kitten
{
	class SpriteRenderable : public Renderable
	{
		typedef std::pair<int, int> GridPosition;
	private:
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		int m_sheetWidth, m_sheetHeight;
		int m_characterWidth, m_characterHeight;
		int m_gridWidth, m_gridHeight;

		std::unordered_map<std::string, std::pair<GridPosition, GridPosition>> m_animations;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;

	public:
		SpriteRenderable(const char* p_pathToSheet, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight);
		virtual ~SpriteRenderable();

		void setAnimation(const std::string& p_name, GridPosition p_start, GridPosition p_end);

		virtual void render(const glm::mat4& p_viewProj) override;
	};
}