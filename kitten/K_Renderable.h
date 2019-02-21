#pragma once

#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Camera.h"

#include "puppy\Texture.h"
#include "puppy\P_Renderable.h"

// This is basically a shortcut now
// instead of extending the two classes below, can extend this
namespace kitten
{
	class K_Renderable : public K_Component, public puppy::P_Renderable
	{
	protected:
		K_Renderable();
		K_Renderable(nlohmann::json& p_json);
		virtual ~K_Renderable();

	public:		
		virtual void render(Camera* p_cam) override = 0;
	};
}