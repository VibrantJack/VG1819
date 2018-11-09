#pragma once
#include <unordered_map>
#include "puppy\Material.h"

namespace sprites
{
	class SpriteAnimator;

	class SpriteSheet
	{
		friend class SpriteAnimator;
	public:
		typedef std::pair<int, int> GridPosition;

		struct AnimationFrame
		{
		public:
			AnimationFrame(const glm::vec2& p_texOffset, const float& p_time, bool p_isFirstFrame = false, bool p_isLastFrame = false)
				: textureOffset(p_texOffset), time(p_time), isFirstFrame(p_isFirstFrame), isLastFrame(p_isLastFrame) {};
			~AnimationFrame() {};

			const bool isFirstFrame = false;
			bool isLastFrame = false;
			const glm::vec2 textureOffset;
			const float time; //in seconds
			AnimationFrame* next = nullptr;
		};

	private:
		std::unordered_map<std::string, AnimationFrame*> m_animations;
		const std::string m_characterName, m_pathToSheet;

		const int m_sheetWidth, m_sheetHeight;
		const int m_characterWidth, m_characterHeight;
		const int m_gridWidth, m_gridHeight;

		const AnimationFrame* m_defaultAnimation;
		puppy::Material* m_material;

	public:
		SpriteSheet(const std::string& p_characterName, const std::string& p_pathToTex, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight);
		~SpriteSheet();

		const std::string& getCharacterName() const;

		void setAnimation(const std::string& p_name, const GridPosition& startPosition, const GridPosition& endPosition, float p_animationTime);
		void setDefaultAnimation(const std::string& p_name);

		const AnimationFrame* getAnimation(const std::string& p_name) const;
		const AnimationFrame* getDefaultAnimation() const;
	};
}