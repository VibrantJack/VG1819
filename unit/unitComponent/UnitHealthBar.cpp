#include "UnitHealthBar.h"

#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten\BarRenderable.h"

namespace unit
{
	puppy::Material* UnitHealthBar::m_healthMat = nullptr;
	puppy::Material* UnitHealthBar::m_damageMat = nullptr;
	unsigned int UnitHealthBar::instances = 0;

	UnitHealthBar::UnitHealthBar(const glm::vec2& p_offset, float p_lerpTimeScalar) : m_attachedUnit(nullptr), m_oldHealthPercent(0.0f), m_lerpTimeScalar(p_lerpTimeScalar)
	{
		if (instances == 0)
		{
			m_healthMat = new puppy::Material(puppy::ShaderType::basic);
			m_healthMat->setTexture(HEALTH_MAT_TEXTURE_PATH);

			m_damageMat = new puppy::Material(puppy::ShaderType::basic);
			m_damageMat->setTexture(DAMAGE_MAT_TEXTURE_PATH);
		}

		++instances;
	}

	UnitHealthBar::~UnitHealthBar()
	{
		--instances;

		if (instances == 0)
		{
			delete m_healthMat;
			m_healthMat = nullptr;

			delete m_damageMat;
			m_damageMat = nullptr;
		}

		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void UnitHealthBar::start()
	{
		m_attachedUnit = m_attachedObject->getComponent<Unit>();
		assert(m_attachedUnit != nullptr);

		// Health bar is made up of a background and a foreground
		kitten::K_GameObject* background = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		kitten::K_GameObject* foreground = kitten::K_GameObjectManager::getInstance()->createNewGameObject();

		background->getTransform().setIgnoreParent(false);
		foreground->getTransform().setIgnoreParent(false);
		background->getTransform().setParent(&getTransform());
		foreground->getTransform().setParent(&getTransform());
		

		foreground->getTransform().move(0, 0, -0.1f);

		auto compMan = kitten::K_ComponentManager::getInstance();

		kitten::BarRenderable* backgroundBar = static_cast<kitten::BarRenderable*>(compMan->createComponent("BarRenderable"));
		backgroundBar->setTexture(DAMAGE_MAT_TEXTURE_PATH);
		background->addComponent(backgroundBar);

		kitten::BarRenderable* foregroundBar = static_cast<kitten::BarRenderable*>(compMan->createComponent("BarRenderable"));
		foregroundBar->setTexture(HEALTH_MAT_TEXTURE_PATH);
		foreground->addComponent(foregroundBar);

		m_foregroundLerpController = static_cast<LerpController*>(compMan->createComponent("LerpController"));
		foreground->addComponent(m_foregroundLerpController);
	}

	void UnitHealthBar::update()
	{
		//@TODO: don't do two map lookups each frame per unit
		int currentHealth = m_attachedUnit->m_attributes[UNIT_HP];
		int maxHealth = m_attachedUnit->m_attributes[UNIT_MAX_HP];

		float percentFull = (float)currentHealth / (float)maxHealth;

		if (percentFull != m_oldHealthPercent)
		{
			//scale foreground
			const glm::vec3& currentScale = getTransform().getScale();
			m_foregroundLerpController->scaleLerp(glm::vec3(percentFull,1.0f,currentScale.z), abs(m_oldHealthPercent - percentFull) * m_lerpTimeScalar);
			m_oldHealthPercent = percentFull;
		}
	}
}