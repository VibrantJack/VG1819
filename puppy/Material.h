#pragma once

#include "P_Common.h"
#include "puppy\ShaderProgram.h"
#include "puppy\Texture.h"
#include "puppy\ShaderManager.h"

#include <string>

namespace puppy
{
	class Material
	{
	private:
		//Member variables
		std::string m_name;

		puppy::Texture* m_tex;

	protected:
		puppy::ShaderProgram* m_shader;

	public:
		Material(ShaderType p_shaderType);
		~Material();

		void setTexture(const char* p_pathToTex);
		puppy::Texture* getTexture() const;

		//Uniform will be set every time the material is applied
		void memorizeUniform(const std::string& p_name, const glm::mat4& p_mat4);
		void memorizeUniform(const std::string& p_name, const glm::mat3& p_mat3);
		void memorizeUniform(const std::string& p_name, const glm::vec4& p_vec4);
		void memorizeUniform(const std::string& p_name, const glm::vec3& p_vec3);
		void memorizeUniform(const std::string& p_name, const GLfloat& p_float);
		void memorizeUniform(const std::string& p_name, const GLint& p_int);

		//One-time set
		void setUniform(const std::string& p_name, const glm::mat4& p_mat4);
		void setUniform(const std::string& p_name, const glm::vec4& p_vec4);
		void setUniform(const std::string& p_name, const glm::vec2& p_vec2);

		int getUniformPlace(const std::string& p_name);

		virtual void apply();
	};
}