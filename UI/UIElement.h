#pragma once

#include "kitten\K_Common.h"
#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
//austin's UI element :)

namespace userinterface
{
	class UIElement : public kitten::UIRenderable
	{
	public:

		UIElement(const char* p_pathToTex);

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

		UIElement(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour);
		
		virtual ~UIElement();
		virtual void start() override;
		virtual void render(const glm::mat4& p_ortho);
		virtual void setTexture(const char* p_pathToTex);
		virtual void setTexBehaviour(const textureBehaviour p_tb);
		virtual void setPivotType(const pivotType p_piv);

	protected:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;

		textureBehaviour m_texBehaviour;
		pivotType m_pivotType;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		bool m_isEnabled;

		virtual void onDisabled() override;
		virtual void onEnabled() override;
	};
}
