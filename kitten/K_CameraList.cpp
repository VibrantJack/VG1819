#include "K_CameraList.h"

namespace kitten
{
	K_CameraList* K_CameraList::sm_instance = nullptr;

	K_CameraList::K_CameraList() : m_sceneCamera(nullptr)
	{

	}

	K_CameraList::~K_CameraList()
	{

	}

	void K_CameraList::setSceneCamera(Camera* p_cam)
	{
		m_sceneCamera = p_cam;
	}

	Camera* K_CameraList::getSceneCamera() const
	{
		return m_sceneCamera;
	}
}