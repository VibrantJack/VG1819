#pragma once
#include "UI\UIElement.h"
namespace userinterface
{
	class BorderPiece : public UIElement
	{
	public:
		
		~BorderPiece();

		//types
		enum BorderPlacement
		{
			bp_Top,
			bp_Right,
			bp_Bot,
			bp_Left,
			bp_TopLeft,
			bp_TopRight,
			bp_BotRight,
			bp_BotLeft
		};

		//methods
		void setFramedObject(kitten::K_GameObject* p_GO);
		BorderPiece(BorderPlacement p_bp);

	protected:
		//members
		kitten::K_GameObject* m_framedObject;
		puppy::VertexEnvironment* m_vao;
		BorderPlacement m_borderPlacement;
		
		//methods
		void start() override;
		void defineVerts() override;

		virtual void uiRender(kitten::Camera* p_cam) override;
		
	};
}

