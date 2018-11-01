#pragma once

#include "Camera.h"

namespace kitten
{
	/*
		This class will probably be expanded for the UI,
		that is why it is currently a 'List', but only
		has the one camera right now.
		- Callum

		EDIT: Added UI functionality to the camera.. ??? - Callum
	*/
	
	class K_Instance;

	class K_CameraList
	{
		friend class K_Instance;
	private:
		static K_CameraList* sm_instance;
		K_CameraList();
		~K_CameraList();

		Camera* m_sceneCamera;

		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new K_CameraList(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete(sm_instance); sm_instance = nullptr; };
	public:
		static K_CameraList* getInstance() { return sm_instance; };

		void setSceneCamera(Camera* p_cam);
		Camera* getSceneCamera() const;
	};
}