#include "CubeFieldCreator.h"
#include "../SceneManagement/SceneManager.h"

#include <sstream>

#define SQRT_OF_3 1.73205080757

namespace shapes
{
	CubeFieldCreator::CubeFieldCreator(const char* p_pathToTexture)
	{
		m_pathToTex = p_pathToTexture;
	}

	CubeFieldCreator::~CubeFieldCreator()
	{

	}

	void CubeFieldCreator::generateEvenly(int p_space, const glm::vec2& p_topLeft, const glm::vec2& p_bottomRight)
	{
		//X axis
		for (int i = p_topLeft[0]; i < p_bottomRight[0]; i += p_space)
		{
			//Z axis
			for (int n = p_topLeft[1]; n < p_bottomRight[1]; n += p_space)
			{
				Cube* toPlace = new Cube(m_pathToTex.c_str());
				toPlace->setBoundingRadius(0.5f);
				toPlace->place(i, 0.5f, n);

				scene::SceneManager::Instance()->addRenderableNode(toPlace);
			}
		}
	}

	void CubeFieldCreator::generateRandomly(int p_numCubes,float p_maxScale, const glm::vec2& p_topLeft, const glm::vec2& p_bottomRight)
	{
		for (int i = 0; i < p_numCubes; ++i)
		{
			float xPos = p_topLeft[0] + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (p_bottomRight[0] - p_topLeft[0])));
			float zPos = p_topLeft[1] + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (p_bottomRight[1] - p_topLeft[1])));
			float scale = 0.5f +  static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / p_maxScale - 0.5f));

			Cube* toPlace = new Cube(m_pathToTex.c_str());
			std::ostringstream ss;
			ss << "RandomCube # " << i;
			toPlace->setName(ss.str());

			toPlace->scaleAbsolute(scale, scale, scale);

			toPlace->setBoundingRadius((scale*SQRT_OF_3)/2.0f);
			toPlace->place(xPos, scale/2.0f, zPos);

			scene::SceneManager::Instance()->addRenderableNode(toPlace);
		}
	}
}