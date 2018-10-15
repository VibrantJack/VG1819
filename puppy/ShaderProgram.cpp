#include "ShaderProgram.h"
#include "../wolf/W_Common.h"

namespace puppy
{
	

	ShaderProgram::ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_pixelShaderPath)
	{
		//If I were to write my own shader compiling / loading it would be the same as wolf's.
		m_id = wolf::LoadShaders(p_vertexShaderPath, p_pixelShaderPath);
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteShader(m_id);
	}

	void ShaderProgram::apply() const
	{
		glUseProgram(m_id);
	}

	int ShaderProgram::getAttrLocation(const char* p_name) const
	{
		return glGetAttribLocation(m_id, p_name);
	}

	int ShaderProgram::getUniformPlace(const std::string& p_name)
	{
		auto it = m_uniformPlaces.find(p_name.c_str());

		if (it == m_uniformPlaces.end())
		{
			m_uniformPlaces.insert(std::make_pair(p_name, glGetUniformLocation(m_id, p_name.c_str())));
		}

		return m_uniformPlaces[p_name];
	}
}