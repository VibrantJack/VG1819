#include "UnitHealthBar.h"

#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_ComponentManager.h"

#include "kitten\BarRenderable.h"

namespace unit
{
	UnitHealthBar::UnitHealthBar(const glm::vec3& p_offset, float p_lerpTimeScalar, float p_rotation)
		: m_attachedUnit(nullptr), m_oldHealthPercent(1.0f), m_lerpTimeScalar(p_lerpTimeScalar), m_offset(p_offset), m_rotation(p_rotation),
		m_healthMat(puppy::ShaderType::billboarded_u_scale)
	{

	}

	UnitHealthBar::~UnitHealthBar()
	{
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
		
		background->getTransform().scaleAbsolute(BACKGROUND_BAR_X_SCALE, BACKGROUND_BAR_Y_SCALE, 1.0f);
		foreground->getTransform().scaleAbsolute(BAR_X_SCALE, BAR_Y_SCALE, 1.0f);

		background->getTransform().move(m_offset.x /*- (BACKGROUND_BAR_X_DIFFERENCE/2.0f)*/, m_offset.y,  m_offset.z + -0.001f);
		foreground->getTransform().move(m_offset.x, m_offset.y, m_offset.z + -0.002f);

		background->getTransform().rotateAbsolute(glm::vec3(m_rotation,0,0));
		foreground->getTransform().rotateAbsolute(glm::vec3(m_rotation,0,0));

		auto compMan = kitten::K_ComponentManager::getInstance();

		kitten::BarRenderable* backgroundBar = static_cast<kitten::BarRenderable*>(compMan->createComponent("BarRenderable"));
		backgroundBar->setTexture(DAMAGE_MAT_TEXTURE_PATH);
		background->addComponent(backgroundBar);

		m_foregroundBar = static_cast<kitten::BarRenderable*>(compMan->createComponent("BarRenderable"));

		if (m_attachedUnit->m_clientId)
		{
			m_foregroundBar->setTexture(HEALTH_MAT_P1_TEXTURE_PATH);
		}
		else
		{
			m_foregroundBar->setTexture(HEALTH_MAT_P2_TEXTURE_PATH);
		}
		
		
		m_foregroundBar->setUScale(BAR_X_SCALE);
		foreground->addComponent(m_foregroundBar);

		m_foregroundLerpController = static_cast<LerpController*>(compMan->createComponent("LerpController"));
		foreground->addComponent(m_foregroundLerpController);

		backgroundBar->setUScale(BACKGROUND_BAR_X_SCALE);
	}

	void UnitHealthBar::updateBar()
	{
		int currentHealth = m_attachedUnit->m_attributes[UNIT_HP];
		int maxHealth = m_attachedUnit->m_attributes[UNIT_MAX_HP];

		float percentFull = (float)currentHealth / (float)maxHealth;

		if (percentFull != m_oldHealthPercent)
		{
			//scale foreground
			const glm::vec3& currentScale = getTransform().getScale();
			m_foregroundLerpController->scaleLerp(glm::vec3(BAR_X_SCALE*percentFull, BAR_Y_SCALE, currentScale.z), abs(m_oldHealthPercent - percentFull) * m_lerpTimeScalar);

			m_oldHealthPercent = percentFull;
		}
	}
}