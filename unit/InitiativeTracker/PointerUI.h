#pragma once
#include "userinterface/UIFrame.h"

//Rock
//inherite from UIFrame
//Change shader to alpha test type
//change vao to avoid repeating

namespace userinterface
{
	class PointerUI : public UIFrame
	{
	public:
		PointerUI();
		~PointerUI();
		void start();
		void render(const glm::mat4& p_ortho);

	private:
		puppy::Material* m_mat;
		puppy::Texture* m_tex;

		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	};
}
