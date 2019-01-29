#include "ShaderProgram.h"
#include "../wolf/W_Common.h"

#include "lights\P_LightList.h"

namespace puppy
{
	ShaderProgram::ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_pixelShaderPath, ShaderType p_type) : m_type(p_type), m_hasDirectionalLights(false), m_hasPointLights(false)
	{
		//If I were to write my own shader compiling / loading it would be the same as wolf's.
		m_id = wolf::LoadShaders(p_vertexShaderPath, p_pixelShaderPath);

		if (m_type == basic_directional_light || m_type == solid_color_directional_light) // Not sure what the better way to do this is
		{
			m_hasDirectionalLights = true;
		}

		if (m_type == texture_blend_zero_point_light || m_type == texture_blend_one_point_light || m_type ==  texture_blend_two_point_light ||
			m_type == texture_blend_three_point_light || m_type == texture_blend_four_point_light)
		{
			m_hasPointLights = true;
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteShader(m_id);
	}

	void ShaderProgram::apply()
	{
		glUseProgram(m_id);

		if (m_hasDirectionalLights) // If this _shader_ supports directional lights,
		{
			// Set the lights
			auto lightList = P_LightList::getInstance();
			if (lightList != nullptr)
			{
				auto& directionalLights = lightList->getDirectionalLights();
				if (directionalLights.empty())
				{
					// No light, all we have to do is set color to black and we are fine
					glUniform4fv(getUniformPlace("lightDirectionalColor"), 1, glm::value_ptr(glm::vec4(0, 0, 0, 1)));
					glUniform4fv(getUniformPlace("lightAmbientColor"), 1, glm::value_ptr(glm::vec4(0, 0, 0, 1)));
				}
				else
				{
					auto firstLight = *(directionalLights.begin());

					glUniform4fv(getUniformPlace("lightDirectionalColor"), 1, glm::value_ptr(firstLight->getDirectionalColor()));
					glUniform4fv(getUniformPlace("lightAmbientColor"), 1, glm::value_ptr(firstLight->getAmbientColor()));
					glUniform3fv(getUniformPlace("lightPos"), 1, glm::value_ptr(firstLight->getPosition()));
				}
			}
		}

		if (m_hasPointLights)
		{
			auto lightList = P_LightList::getInstance();
			if (lightList != nullptr)
			{
				auto& pointLights = lightList->getPointLights();
				if (pointLights.empty())
				{
					glUniform1f(getUniformPlace("lightRange"), 0);
					glUniform4fv(getUniformPlace("lightAmbientColor"), 1, glm::value_ptr(glm::vec4(0, 0, 0, 1)));
				}
				else
				{
					auto firstLight = *(pointLights.begin());

					glUniform4fv(getUniformPlace("lightDiffuse"), 1, glm::value_ptr(firstLight->getPointColor()));
					glUniform4fv(getUniformPlace("lightAmbientColor"), 1, glm::value_ptr(firstLight->getAmbientColor()));
					glUniform3fv(getUniformPlace("lightPos"), 1, glm::value_ptr(firstLight->getPosition()));
					glUniform3fv(getUniformPlace("lightAttenuation"), 1, glm::value_ptr(firstLight->getAttenuation()));
					glUniform1f(getUniformPlace("lightRange"), firstLight->getRange());
				}
			}
		}
	}

	int ShaderProgram::getAttrLocation(const char* p_name) const
	{
		return glGetAttribLocation(m_id, p_name);
	}

	int ShaderProgram::getUniformPlace(const std::string& p_name)
	{
#ifdef DEBUG

		return glGetUniformLocation(m_id, p_name.c_str());

#else

		auto& it = m_uniformPlaces.find(p_name);

		if (it == m_uniformPlaces.end())
		{
			int place = glGetUniformLocation(m_id, p_name.c_str());
			m_uniformPlaces.insert(std::make_pair(p_name, place));

			return place;
		}
		else
		{
			return (*it).second;
		}


#endif
	}
}