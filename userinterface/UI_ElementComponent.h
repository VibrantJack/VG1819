#pragma once
#include "kitten\UIRenderable.h"
#include "puppy\Material.h"
#include "puppy\VertexEnvironment.h"


//@ Austin Roges 
// 09 21 2018

namespace userinterface
{
	class UI_ElementComponent : public kitten::UIRenderable
	{
	public:
		UI_ElementComponent();
		~UI_ElementComponent();
		void render(const glm::mat4& p_viewProj);
		void setTexture(const char* p_pathToTex);
	protected:
		//note that "bound" represents the maximum x and y coord for the origin. 
		//This is used to stop the element from going offscreen, depending on the current resolution, whenever
		//the x and y values are increased.
		glm::vec2 m_bound;
		puppy::Material* m_mat;
		static puppy::VertexEnvironment* sm_vao;
		static int sm_instances;
	};
}