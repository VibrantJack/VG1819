/*
@Rock 12.11
This component will contain a number of game objects.
These game objects only has sprite renderable and sprite animator as components.
*/

#pragma once
#include "SpriteAnimator.h"

namespace sprites
{
	class SpriteGroup : public kitten::K_Component
	{
	public:
		SpriteGroup(const std::string& p_spriteName, int p_num = 1);
		~SpriteGroup();

		void setScale(float p_x, float p_y, float p_z);
		void setRotation(const glm::vec3& p_rot);
		void start() override;
	private:
		const int m_maxNum = 4;

		std::string m_spriteName;
		int m_spriteNum;
		float m_scaleX;
		float m_scaleY;
		float m_scaleZ;

		glm::vec3 m_rotation;

		std::vector<kitten::K_GameObject*> m_spriteGOList;

		void createSpriteGO();
		const glm::vec3 getSubTranslation(int p_n);
	};
}
