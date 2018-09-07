#pragma once
#include "puppy\P_Common.h"
#include "Cube.h"
#include <string>

namespace shapes
{
	class CubeFieldCreator
	{
	private:
		std::string m_pathToTex;
	public:
		CubeFieldCreator(const char* p_pathToTexture);
		~CubeFieldCreator();

		void generateEvenly(int p_space, const glm::vec2& p_topLeft, const glm::vec2& p_bottomRight);
		void generateRandomly(int p_numCubes, float p_maxScale, const glm::vec2& p_topLeft, const glm::vec2& p_bottomRight);
	};
}