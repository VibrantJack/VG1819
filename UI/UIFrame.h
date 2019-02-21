#pragma once
#include "kitten\K_UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include "UIElement.h"
#include <list>
#include "UIObject.h"

namespace userinterface 
{
	class UIFrame : public userinterface::UIElement
	{
	public:

		UIFrame(const char* p_pathToTex);
		UIFrame(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour);
		UIFrame(nlohmann::json& p_json);
		virtual ~UIFrame();
		
		void addToFrame(UIObject* p_uioToAdd);
		void removeFromFrame(UIObject* p_uioToRemove);
		void setInnerObjectsEnabled(bool p_enabled);

	protected:

		void onDisabled() ;
		void onEnabled();
		std::list<UIObject*> m_innerObjects;

	};
}
