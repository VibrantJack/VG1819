#pragma once

#include "P_Common.h"
#include "ShaderProgram.h"

#include <string>
#include <unordered_map>

namespace puppy
{
	class ShaderManager
	{
	private:
		//Hide construction methods
		ShaderManager() {}
		ShaderManager(ShaderManager const&); //no need to implement
		void operator =(ShaderManager const&); //no need to implement

		static const ShaderProgram* m_boundShader; //set to max val as default
		static ShaderProgram* m_createdPresetShaders[ShaderType::SHADERTYPE_MAX+1];

		/*
		getShaderPaths() helper method sets two strings to the paths of shaders used for a shader type
		*/
		static bool getShaderPaths(ShaderType p_st, std::string* p_vertexShaderPath, std::string* p_pixelShaderPath);
	public:
		static bool applyShader(ShaderType p_st); //Returns if it was bound (false if already bound)
		static bool applyShader(ShaderProgram* p_sp);

		static ShaderProgram* getShaderProgram(ShaderType p_st);

		static void destroyAllShaders();
	};
}