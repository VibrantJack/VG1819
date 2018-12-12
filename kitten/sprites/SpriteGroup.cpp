#include "SpriteGroup.h"
#include "kitten/K_GameObjectManager.h"
#include "kitten/K_ComponentManager.h"

sprites::SpriteGroup::SpriteGroup(const std::string & p_spriteName, int p_num)
	:m_spriteName(p_spriteName),
	m_spriteNum(p_num),
	m_scaleX(1),
	m_scaleY(1),
	m_scaleZ(0),
	m_rotation(glm::vec3(45, 0, 0))
{
}

sprites::SpriteGroup::~SpriteGroup()
{
}

void sprites::SpriteGroup::setScale(float p_x, float p_y, float p_z)
{
	m_scaleX = p_x;
	m_scaleY = p_y;
	m_scaleZ = p_z;
}

void sprites::SpriteGroup::setRotation(const glm::vec3& p_rot)
{
	m_rotation = p_rot;
}

void sprites::SpriteGroup::start()
{
	createSpriteGO();
}

void sprites::SpriteGroup::createSpriteGO()
{
	kitten::K_GameObjectManager* gm = kitten::K_GameObjectManager::getInstance();
	kitten::K_ComponentManager* cm = kitten::K_ComponentManager::getInstance();

	for (int i = 0; i < m_spriteNum && i<m_maxNum; i++)
	{
		kitten::K_GameObject* go = gm->createNewGameObject();

		go->addComponent(cm->createComponent("SpriteRenderable"));

		SpriteAnimator* animator = static_cast<SpriteAnimator*>(cm->createComponent("SpriteAnimator"));
		animator->setSpriteSheet(m_spriteName);
		go->addComponent(animator);

		kitten::Transform tr = go->getTransform();
		tr.setIgnoreParent(false);
		tr.setParent(&m_attachedObject->getTransform());
		tr.scaleAbsolute(m_scaleX, m_scaleY, m_scaleZ);
		tr.rotateAbsolute(m_rotation);

		glm::vec3 pos = getSubTranslation(i);
		tr.place(pos.x, pos.y, pos.z);
	}
}

const glm::vec3 sprites::SpriteGroup::getSubTranslation(int p_n)
{
	switch (m_spriteNum)
	{
	case 1:
		return glm::vec3(0, 0, 0);
	case 2:
		switch (p_n)
		{
		case 0:
			return glm::vec3(0.5, 0, 0.5);
		case 1:
			return glm::vec3(-0.5, 0, -0.5);
		}
	case 3:
		switch (p_n)
		{
		case 0:
			return glm::vec3(0.5, 0, 0.5);
		case 1:
			return glm::vec3(-0.5, 0, 0.5);
		case 2:
			return glm::vec3(0, 0, -0.5);
		}
	case 4:
		switch (p_n)
		{
		case 0:
			return glm::vec3(0.5, 0, 0.5);
		case 1:
			return glm::vec3(-0.5, 0, 0.5);
		case 2:
			return glm::vec3(0.5, 0, -0.5);
		case 3:
			return glm::vec3(-0.5, 0, -0.5);
		}
	}
}
