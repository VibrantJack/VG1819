#pragma once
#include "UI/UIFrame.h"
#include "kitten\K_UIRenderable.h"

//Rock
//inherite from UIFrame
//Change shader to alpha test type
//change vao to avoid repeating

namespace userinterface
{
	class PointerUI : public kitten::K_UIRenderable
	{
	public:
		PointerUI();
		PointerUI(nlohmann::json& p_json);
		~PointerUI();

		void uiRender(kitten::Camera* p_cam) override;

	private:
		puppy::Material* m_mat;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;

		virtual void start() override;
		virtual void onEnabled() override;
		virtual void onDisabled() override;
	};
}
