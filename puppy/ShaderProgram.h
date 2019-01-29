#pragma once
#include "P_Common.h"

#include <string>
#include <unordered_map>

namespace puppy
{
	class ShaderProgram
	{
		friend class ShaderManager;
		friend class VertexEnvironment;
	
	private:
		std::unordered_map<std::string, int> m_uniformPlaces;

	protected:
		GLuint m_id;
		ShaderType m_type;
		
		bool m_hasDirectionalLights, m_hasPointLights;

		int getAttrLocation(const char* p_name) const;

		ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_pixelShaderPath, ShaderType p_type);
		~ShaderProgram();

		void apply();

	public:
		int getUniformPlace(const std::string& p_name);
		ShaderType getType() const { return m_type; }
	};
}