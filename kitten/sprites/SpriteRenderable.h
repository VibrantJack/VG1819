#pragma once
#include "kitten\Renderable.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"
#include <unordered_map>

namespace sprites
{
	class SpriteAnimator;
}

namespace kitten
{
	class SpriteRenderable : public Renderable
	{
		friend class sprites::SpriteAnimator;
	private:
		puppy::VertexEnvironment* m_vao;
		puppy::Material* m_mat;

		glm::vec2 m_texOffset;

		virtual void start() override;
		virtual void onDisabled() override;
		virtual void onEnabled() override;
	protected:
		void setupRenderable(const float& p_uWidth, const float& p_vHeight, const float& p_characterWidth, const float& p_characterHeight, puppy::Material& p_mat);
		void setTextureOffset(const glm::vec2& p_offset);
	public:
		SpriteRenderable();
		virtual ~SpriteRenderable();

		virtual void render(const glm::mat4& p_viewProj) override;
	};
}