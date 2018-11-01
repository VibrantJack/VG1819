#pragma once

#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include "UIElement.h"

namespace userinterface
{

	//austin's UI object

	class UIFrame;

	class UIObject : public userinterface::UIElement
	{
	public:
		UIObject(const char* p_pathToTex);
		UIObject(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBahaviour);
		virtual ~UIObject();

		UIFrame* getParentFrame();

	protected:
		void onDisabled();
		void onEnabled();

		UIFrame* m_parentFrame;
	
	};
}
