#pragma once
#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include "UIElement.h"
#include <list>

namespace userinterface 
{
	class UIObject;

	class UIFrame : public userinterface::UIElement
	{
	public:

		UIFrame(const char* p_pathToTex);
		UIFrame(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour);
		virtual ~UIFrame();
		
		void addToFrame(UIObject* p_uioToAdd);
		void removeFromFrame(UIObject* p_uioToRemove);
	
	protected:

		void onDisabled() ;
		void onEnabled();
		std::list<UIObject*> m_innerObjects;

	};
}
