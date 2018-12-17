#pragma once
#include "UI/UIFrame.h"
#include "kitten\UIRenderable.h"

//Rock
//inherite from UIFrame
//Change shader to alpha test type
//change vao to avoid repeating

namespace userinterface
{
	class PointerUI : public kitten::UIRenderable
	{
	public:
		PointerUI();
		~PointerUI();

		void uiRender(const glm::mat4& p_ortho);

	private:
		puppy::Material* m_mat;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		virtual void start() override;
		virtual void onEnabled() override;
		virtual void onDisabled() override;
	};
}
