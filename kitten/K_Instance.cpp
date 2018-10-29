#include "K_Instance.h"

namespace kitten
{
	K_Instance* K_Instance::sm_instance = nullptr;

	K_Instance::K_Instance() : m_inputManager(input::InputManager::getInstance()), m_cameraList(K_CameraList::getInstance()),
		m_componentManager(K_ComponentManager::getInstance()), m_gameObjectManager(K_GameObjectManager::getInstance()),
		m_time(K_Time::getInstance()), m_clickables(ActiveClickables::getInstance()), m_eventManager(EventManager::getInstance())
	{

	}

	K_Instance::~K_Instance()
	{
		
	}

	void K_Instance::createInstance()
	{
		assert(sm_instance == nullptr);

		input::InputManager::createInstance();
		K_CameraList::createInstance();
		K_ComponentManager::createInstance();
		K_GameObjectManager::createInstance();
		K_Time::createInstance();
		ActiveClickables::createInstance();
		EventManager::createInstance();
		AudioEngineWrapper::createInstance();	

		sm_instance = new K_Instance();
	}

	void K_Instance::destroyInstance()
	{
		assert(sm_instance != nullptr);

		input::InputManager::destroyInstance();
		K_CameraList::destroyInstance();
		K_ComponentManager::destroyInstance();
		K_GameObjectManager::destroyInstance();
		K_Time::destroyInstance();
		ActiveClickables::destroyInstance();
		EventManager::destroyInstance();
		AudioEngineWrapper::destroyInstance();

		delete sm_instance;
	}

	void K_Instance::update()
	{
		sm_instance->privateUpdate();
	}

	void K_Instance::privateUpdate()
	{
		AudioEngineWrapper::update();
		m_time->updateTime();
		m_inputManager->update();
		m_eventManager->update();

		m_componentManager->updateComponents();
		m_gameObjectManager->deleteQueuedObjects();
	}
}