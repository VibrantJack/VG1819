#pragma once

#include "kitten\K_Common.h"
#include "kitten\K_UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"
#include <map>
#include <iterator>  
//austin's UI element :)
#define DEFAULT_TEXTURE "textures/ui/blankFrame.tga"
namespace userinterface
{
	class UIElement : public kitten::K_UIRenderable
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
		virtual void uiRender(kitten::Camera* p_cam) override;
		virtual void setTexture(const char* p_pathToTex);
		virtual void setTexBehaviour(const textureBehaviour p_tb);
		virtual void setPivotType(const pivotType p_piv);

	    const std::string& getTexturePath() const { return m_texPath; }

	protected:
		static std::map<pivotType, puppy::VertexEnvironment*> sm_vao;
		static std::map<pivotType, int> sm_instances;

		puppy::Material* m_mat;
		puppy::Texture* m_tex;

		textureBehaviour m_texBehaviour;
		pivotType m_pivotType;

		puppy::VertexEnvironment* m_vao;

		std::string m_texPath;
		bool m_hasSetVerts = false, m_hasTransparency = false;
		float m_gAlpha = 1.0;

		virtual void onDisabled() override;
		virtual void onEnabled() override;
		virtual void defineVerts();
	public:
		float getGAlpha() const { return m_gAlpha; }
		void setGAlpha(float p_gAlpha) { m_gAlpha = p_gAlpha; }
		const puppy::Material* getMaterial() const { return m_mat; }
		void setTransparency(bool p_hasTransparency);
	};

	
}
