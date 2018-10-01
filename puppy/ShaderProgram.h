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

		int getAttrLocation(const char* p_name) const;

		void apply() const;

	public:
		ShaderProgram(const std::string& p_vertexShaderPath, const std::string& p_pixelShaderPath);
		
		int getUniformPlace(const std::string& p_name);
	};
}