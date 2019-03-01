#include "ReloadObjectOnKeyPress.h"

ReloadObjectOnKeyPress::ReloadObjectOnKeyPress(char p_key, const std::string& p_pathToJson, bool p_replaceTransform) : m_key(p_key), 
	m_pathToJson(p_pathToJson), m_replaceTransform(p_replaceTransform), m_inputMan(nullptr)
{

}

ReloadObjectOnKeyPress::~ReloadObjectOnKeyPress()
{

}

void ReloadObjectOnKeyPress::start()
{
	m_inputMan = input::InputManager::getInstance();
	assert(m_inputMan != nullptr);
}

void ReloadObjectOnKeyPress::update()
{
	if (m_inputMan->keyDown(m_key) && !m_inputMan->keyDownLast(m_key))
	{
		auto newGameObj = kitten::K_GameObjectManager::getInstance()->createNewGameObject(m_pathToJson);

		const glm::vec3& translation = getTransform().getTranslation();
		const glm::vec3& scale = getTransform().getScale();
		const glm::quat& rot = getTransform().getRotation();

		newGameObj->getTransform().setIgnoreParent(false);
		newGameObj->getTransform().setParent(getTransform().getParent());

		if (m_replaceTransform)
		{
			auto& newTransform = newGameObj->getTransform();
			newTransform.place(translation.x, translation.y, translation.z);
			newTransform.scaleAbsolute(scale.x, scale.y, scale.z);
			newTransform.rotateAbsQuat(rot);
		}

		

		kitten::K_GameObjectManager::getInstance()->destroyGameObject(m_attachedObject);
	}
}