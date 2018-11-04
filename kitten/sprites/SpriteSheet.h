#pragma once
#include <unordered_map>

namespace sprites
{
	class SpriteSheet
	{
	public:
		typedef std::pair<int, int> GridPosition;

		struct AnimationData
		{
		public:
			GridPosition startPosition;
			GridPosition endPosition;
			float time;
		};

	private:
		std::unordered_map<std::string, AnimationData> m_animations;
		const std::string m_characterName;

		const int m_sheetWidth, m_sheetHeight;
		const int m_characterWidth, m_characterHeight;
		const int m_gridWidth, m_gridHeight;

	public:
		SpriteSheet(const std::string& p_characterName, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight);
		~SpriteSheet();

		const std::string& getCharacterName();

		void setAnimation(const std::string& p_name, const AnimationData& p_data);
		const AnimationData& getAnimation(const std::string& p_name);
	};
}