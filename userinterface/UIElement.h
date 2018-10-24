#pragma once

#include "kitten/UIRenderable.h"
#include "kitten/UIFrame.h"
//austin's UI element :)

namespace userinterface
{
	class UIElement : kitten::UIRenderable
	{
	public:
		UIElement();
		virtual ~UIElement();
		void start();
		void render(const glm::mat4& p_ortho);
		void setTexture(const char* p_pathToTex);
		//TODO add updates 
		//bool hasUpdate() { return true; };
		//void update();

	protected:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;
		textureBehaviour m_texBehaviour;
		pivotType m_pivotType;
		//TODO add method for ADD UIElement
		//void addUIElement(...);

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	};
}
