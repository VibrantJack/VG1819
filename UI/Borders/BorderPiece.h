#pragma once
#include "UI\UIElement.h"
namespace userinterface
{
	class BorderPiece : public UIElement
	{
	public:
		
		~BorderPiece();

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
		void setFramedObject(kitten::K_GameObject* p_GO);
		BorderPiece(BorderPlacement p_bp);

	protected:
		void defineVerts() override;
		BorderPlacement m_borderPlacement;
		void start() override;
		kitten::K_GameObject* m_framedObject;
		std::map<pivotType, puppy::VertexEnvironment*> sm_vao;
		std::map<pivotType, int> sm_instances;
		virtual void uiRender(kitten::Camera* p_cam) override;
	};
}

