#pragma once

#include "P_Common.h"
#include <string>

namespace puppy
{
	//Objects implement this so they can be rendered
	class Renderable
	{
	public:
		virtual void render(const glm::mat4& p_wvp) = 0;
		virtual const std::string* getTag() const = 0; //For sorting
		virtual const GLuint* getTex() const = 0;  //For sorting


		virtual const glm::vec3 getPos() const = 0; //Could be used for macro culling, but
													//I did not attempt based on the advice in the assignment pdf
													//However, every renderable currently already has this 
													//method implemented thanks to GenShape
	};
}