#pragma once

#include <glm/glm.hpp>

namespace kitten
{
	struct Ray
	{
	public:
		glm::vec3 origin, direction;
	};
}