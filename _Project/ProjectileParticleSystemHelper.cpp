#include "ProjectileParticleSystemHelper.h"
#include "UniversalPfx.h"

ProjectileParticleSystemHelper::ProjectileParticleSystemHelper(const std::string& p_effectName) : m_effectName(p_effectName), m_disabledOnce(false)
{

}

ProjectileParticleSystemHelper::~ProjectileParticleSystemHelper()
{

}

void ProjectileParticleSystemHelper::onDisabled()
{
	if (!m_disabledOnce)
	{
		m_disabledOnce = true;
		return;
	}

	UniversalPfx::getInstance()->playEffect(m_effectName, getTransform().getTranslation());
}
