#pragma once
#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include <vector>

namespace userinterface 
{
	class UIFrame : public kitten::UIRenderable
	{
	public:

		enum pivotType {
			piv_Left,
			piv_Right,
			piv_Bot,
			piv_Top,
			piv_BotLeft,
			piv_BotRight,
			piv_TopLeft,
			piv_TopRight,
			piv_Center
		};

		enum textureBehaviour {
			tbh_Stretch,
			tbh_Repeat,
			tbh_RepeatMirrored
		};

		UIFrame(const char* p_pathToTex);
		UIFrame(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour);
		virtual ~UIFrame();
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
