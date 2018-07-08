#include "Material.h"

namespace puppy
{
	Material::Material()
	{

	}

	Material::~Material()
	{
		delete m_shader;
		delete m_tex;
	}
	
	void Material::apply()
	{
		ShaderManager::applyShader(m_shader);
		m_tex->apply();
		//apply memorized uniforms

	}

	int Material::getUniformPlace(const std::string& p_name)
	{
		return m_shader->getUniformPlace(p_name);
	}

	void Material::memorizeUniform(const std::string& p_name, const glm::mat4& p_mat4)
	{

	}

	void Material::memorizeUniform(const std::string& p_name, const glm::mat3& p_mat3)
	{

	}

	void Material::memorizeUniform(const std::string& p_name, const glm::vec4& p_vec4)
	{

	}
	
	void Material::memorizeUniform(const std::string& p_name, const glm::vec3& p_vec3)
	{

	}

	void Material::memorizeUniform(const std::string& p_name, const GLfloat& p_float)
	{

	}

	void Material::memorizeUniform(const std::string& p_name, const GLint& p_int)
	{

	}
}