#include "Rectangle.h"
#include "puppy\ShaderManager.h"

namespace shapes
{

	puppy::VertexEnvironment* Rectangle::sm_vao = nullptr;

	Rectangle::Rectangle(const char* p_pathToTexture)
	{
		if (sm_vao == nullptr) //if we haven't setup the vao yet
		{
			puppy::TexturedVertex verts[] = 
			{
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
				{ 0.5f, 0.0f, 0.5f,			0.0f, 1.0f },
				{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
				{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
				{ -0.5f, 0.0f,-0.5f,		1.0f, 0.0f },
				{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			};

			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
		}

		m_tex = new puppy::Texture(p_pathToTexture);
	}

	Rectangle::~Rectangle()
	{
		delete m_tex;
	}

	void Rectangle::render(const glm::mat4& p_viewProj)
	{
		//Apply shader
		puppy::ShaderManager::applyShader(puppy::ShaderType::basic);

		//Apply uniforms
		const glm::mat4& world = getWorldTransform();
		GLint place = puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME);
		glUniformMatrix4fv(place, 1, GL_FALSE, glm::value_ptr(p_viewProj * world));

		//Apply Texture
		m_tex->apply();

		//Render
		sm_vao->drawArrays(GL_TRIANGLES);

		/*
		puppy::TexturedVertex* verts = (puppy::TexturedVertex*) sm_vao->map(GL_READ_WRITE);
		
		puppy::TexturedVertex v = verts[0];
		v = verts[1];
		v = verts[2];
		v = verts[3];
		v = verts[4];
		v = verts[5];

		GLenum result = sm_vao->unmap();
		*/
	}

	void Rectangle::update(float p_deltaTime)
	{
		//Don't need
	}
}