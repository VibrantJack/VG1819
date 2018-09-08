#include "CubeRenderable.h"
#include "puppy\P_Common.h"

namespace kitten
{
	puppy::VertexEnvironment* CubeRenderable::sm_vao = nullptr;
	int CubeRenderable::sm_instances = 0;

	CubeRenderable::CubeRenderable(const char* p_pathToTexture = nullptr)
	{
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTexture != nullptr)
		{
			m_mat->setTexture(p_pathToTexture);
		}

		//If we have not initialized the vao yet
		if (sm_instances < 1)
		{
			//setup the vao
			puppy::TexturedVertex verts[] =
			{
				// Front
				{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
			{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
			{ 0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
			{ 0.5f,  0.5f, 0.5f,		1.0f, 1.0f },
			{ 0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
			{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },

			// Back
			{ 0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
			{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
			{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ -0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
			{ 0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

			// Left
			{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },
			{ -0.5f,  0.5f, 0.5f,		0.0f, 1.0f },
			{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
			{ -0.5f, -0.5f, 0.5f,		1.0f, 1.0f },
			{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
			{ -0.5f,  0.5f,-0.5f,		0.0f, 0.0f },

			// Right
			{ 0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
			{ 0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
			{ 0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f, -0.5f, 0.5f,		1.0f, 0.0f },
			{ 0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

			// Top
			{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },
			{ -0.5f,  0.5f,-0.5f,		0.0f, 1.0f },
			{ 0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f,  0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f,  0.5f, 0.5f,		1.0f, 0.0f },
			{ -0.5f,  0.5f, 0.5f,		0.0f, 0.0f },

			// Bottom
			{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
			{ 0.5f, -0.5f, 0.5f,		0.0f, 1.0f },
			{ 0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ 0.5f, -0.5f,-0.5f,		1.0f, 1.0f },
			{ -0.5f, -0.5f,-0.5f,		1.0f, 0.0f },
			{ -0.5f, -0.5f, 0.5f,		0.0f, 0.0f },
			};
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 36);
		}
		++sm_instances;
	}

	CubeRenderable::~CubeRenderable()
	{
		delete m_mat;
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}
	}

	void CubeRenderable::render(const glm::mat4& p_viewProj)
	{
		m_mat->apply();
		
		//Set world matrix
		glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		//render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}