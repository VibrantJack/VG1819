#include "Cube.h"
#include "puppy\ShaderManager.h"

namespace shapes
{
	puppy::VertexEnvironment* Cube::sm_vao = nullptr;

	Cube::Cube(const char* p_pathToTexture)
	{
		m_tex = new puppy::Texture(p_pathToTexture);

		//If we have not initialized the vao yet
		if (sm_vao == nullptr)
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

	}

	Cube::~Cube()
	{
		
	}

	//TODO: Change to use Transformable so cube can be moved and changed etc. 
	void Cube::render(const glm::mat4& p_viewProj)
	{
		//Apply shader
		puppy::ShaderManager::applyShader(puppy::ShaderType::basic);
		
		//Apply uniforms

		// CHANGE THESE LINES
		/*const glm::mat4& world = getWorldTransform();
		GLint place = puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME);
		glUniformMatrix4fv(place, 1, GL_FALSE, glm::value_ptr(p_viewProj * world));
		*/
		//Apply Texture
		m_tex->apply();

		//Render
		sm_vao->drawArrays(GL_TRIANGLES);
	}
}