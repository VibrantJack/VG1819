#include "Material.h"

namespace puppy
{
	Material::Material(ShaderType p_shaderType) : m_tex(nullptr)
	{
		m_shader = ShaderManager::getShaderProgram(p_shaderType);
	}

	Material::Material(const Material& p_other)
	{
		if (p_other.m_tex != nullptr)
		{
			m_tex = new Texture(p_other.m_tex->getPath());
		}
		else
		{
			m_tex = nullptr;
		}

		m_name = p_other.m_name;
		m_shader = p_other.m_shader;

	}

	Material::~Material()
	{
		if (m_tex != nullptr)
		{
			delete m_tex;
		}
	}
	
	Material& Material::operator=(const Material& p_other)
	{
		if (m_tex != nullptr)
		{
			delete m_tex;
		}

		if (p_other.m_tex != nullptr)
		{
			m_tex = new Texture(p_other.m_tex->getPath());
		}

		m_shader = p_other.m_shader;
		m_name = p_other.m_name;
	}

	bool Material::operator==(const Material& p_other) const
	{
		bool toReturn = false;
		if (m_tex == nullptr && p_other.m_tex == nullptr)
		{
			if (m_shader->getType() == p_other.m_shader->getType())
			{
				return true;
			}
		}
		else if (m_tex != nullptr && p_other.m_tex != nullptr)
		{
			if ((m_tex->getTex() == p_other.m_tex->getTex())
				&& m_shader->getType() == p_other.m_shader->getType())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	void Material::apply() const
	{
		if (m_shader != nullptr)
		{
			ShaderManager::applyShader(m_shader);
		}
		
		if (m_tex != nullptr)
		{
			m_tex->apply();
		}
	}

	void Material::setTexture(const char* p_pathToTex)
	{
		if (m_tex != nullptr)
		{
			delete m_tex;
		}
		m_tex = new Texture(p_pathToTex);
	}

	void Material::setTexture(Texture* p_tex)
	{
		if (m_tex != nullptr)
		{
			delete m_tex;
		}
		m_tex = p_tex;
	}

	Texture* Material::getTexture() const
	{
		return m_tex;
	}

	int Material::getUniformPlace(const std::string& p_name)
	{
		return m_shader->getUniformPlace(p_name);
	}

	void Material::setUniform(const std::string& p_name, const glm::mat4& p_mat4) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniformMatrix4fv(place, 1, GL_FALSE, glm::value_ptr(p_mat4));
	}

	void Material::setUniform(const std::string& p_name, const glm::mat3& p_mat3) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniformMatrix3fv(place, 1, GL_FALSE, glm::value_ptr(p_mat3));
	}

	void Material::setUniform(const std::string& p_name, const glm::vec4& p_vec4) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniform4fv(place, 1, glm::value_ptr(p_vec4));
	}

	void Material::setUniform(const std::string& p_name, const glm::vec3& p_vec3) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniform3fv(place, 1, glm::value_ptr(p_vec3));
	}

	void Material::setUniform(const std::string& p_name, const glm::vec2& p_vec2) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniform2fv(place, 1, glm::value_ptr(p_vec2));
	}

	void Material::setUniform(const std::string& p_name, const float& p_float) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniform1f(place, p_float);
	}

	void Material::setUniform(const std::string& p_name, const int p_int) const
	{
		GLint place = m_shader->getUniformPlace(p_name);
		glUniform1i(place, p_int);
	}
}