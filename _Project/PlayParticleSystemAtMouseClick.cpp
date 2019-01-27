#include "PlayParticleSystemAtMouseClick.h"

// You will notice that I am setting the attached gameobject
// to be enabled instead of just playing the particle system : 
// this is because it is useful on a lot of particle objects
// to disable them after some amount of time.
// Therefore, this component has to receive events even when it is
// disabled, and re-enable the object.
// - Callum

PlayParticleSystemAtMouseClick::PlayParticleSystemAtMouseClick(const glm::vec3& p_offset) : m_offset(p_offset)
{

}

PlayParticleSystemAtMouseClick::~PlayParticleSystemAtMouseClick()
{
	/*
	if (m_isEnabled)
	{
		onDisabled();
	}
	*/

	kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Object_Clicked, this);
}

void PlayParticleSystemAtMouseClick::start()
{
	//onEnabled();
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Object_Clicked,
		this,
		std::bind(&PlayParticleSystemAtMouseClick::onMouseClick, this, std::placeholders::_1, std::placeholders::_2));

	m_particleSystem = m_attachedObject->getComponent<kitten::K_ParticleSystem>();
	assert(m_particleSystem != nullptr);
}

void PlayParticleSystemAtMouseClick::onEnabled()
{
	/*
	kitten::EventManager::getInstance()->addListener(
		kitten::Event::EventType::Object_Clicked,
		this,
		std::bind(&PlayParticleSystemAtMouseClick::onMouseClick, this, std::placeholders::_1, std::placeholders::_2));
		*/
}

void PlayParticleSystemAtMouseClick::onDisabled()
{
	//kitten::EventManager::getInstance()->removeListener(kitten::Event::EventType::Object_Clicked, this);
}

void PlayParticleSystemAtMouseClick::onMouseClick(kitten::Event::EventType p_type, kitten::Event* p_event)
{
	kitten::K_GameObject* gameObj = p_event->getGameObj(OBJECT_CLICKED_OBJ_KEY);

	glm::vec3 newPlace = gameObj->getTransform().getTranslation() + m_offset; 

	getTransform().place(newPlace.x, newPlace.y, newPlace.z);

	m_attachedObject->setEnabled(true);
	m_particleSystem->play();
}
