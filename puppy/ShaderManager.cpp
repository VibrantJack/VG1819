#include "ShaderManager.h"
#include "wolf\W_Common.h"

namespace puppy
{
	//initialize static member variables
	const ShaderProgram* ShaderManager::m_boundShader = nullptr;
	ShaderProgram* ShaderManager::m_createdPresetShaders[ShaderType::SHADERTYPE_MAX+1];

	void ShaderManager::applyShader(const ShaderProgram* p_sp)
	{
		//Use shader if it isn't currently being used
		if (m_boundShader != p_sp)
		{
			p_sp->apply();
			m_boundShader = p_sp;
		}
	}

	void ShaderManager::applyShader(ShaderType p_st)
	{
		if (m_boundShader == m_createdPresetShaders[p_st] && m_boundShader != nullptr)
		{
			return; //shader already bound
		}
		//else

		//Check if shader type has already been created
		if (m_createdPresetShaders[p_st] != nullptr)
		{
			//Shader already created, use it.
			m_createdPresetShaders[p_st]->apply();
			m_boundShader = m_createdPresetShaders[p_st];
			return;
		}
		//else

		//We need to create the shadertype specified
		std::string vertexShaderPath, pixelShaderPath;
		if (getShaderPaths(p_st, &vertexShaderPath, &pixelShaderPath))
		{
			m_createdPresetShaders[p_st] = new ShaderProgram(vertexShaderPath, pixelShaderPath);
			//apply 
			m_createdPresetShaders[p_st]->apply();
			m_boundShader = m_createdPresetShaders[p_st];
		}
	}

	bool ShaderManager::getShaderPaths(ShaderType p_st, std::string* p_vertexShaderPath, std::string* p_pixelShaderPath)
	{
		switch (p_st)
		{
		case ShaderType::basic:
			*p_vertexShaderPath = "Shaders/basic.vsh";
			*p_pixelShaderPath = "Shaders/basic.fsh";
			return true;
		case ShaderType::sprite:
			*p_vertexShaderPath = "Shaders/sprite.vsh";
			*p_pixelShaderPath = "Shaders/sprite.fsh";
			return true;
		case ShaderType::alphaTest:
			*p_vertexShaderPath = "Shaders/basic_alphatest.vsh";
			*p_pixelShaderPath = "Shaders/basic_alphatest.fsh";
			return true;
		case ShaderType::colorTint_alphaTest:
			*p_vertexShaderPath = "Shaders/colorTint_alphatest.vsh";
			*p_pixelShaderPath = "Shaders/colorTint_alphatest.fsh";
			return true;
		case ShaderType::particles:
			*p_vertexShaderPath = "Shaders/particles.vsh";
			*p_pixelShaderPath = "Shaders/particles.fsh";
			return true;
		default:
			return false;
		}
	}

	ShaderProgram* ShaderManager::getShaderProgram(ShaderType p_st)
	{
		if (m_createdPresetShaders[p_st] == nullptr)
		{
			std::string vertexShaderPath, pixelShaderPath;
			if (getShaderPaths(p_st, &vertexShaderPath, &pixelShaderPath))
			{
				m_createdPresetShaders[p_st] = new ShaderProgram(vertexShaderPath, pixelShaderPath);
			}
		}

		return m_createdPresetShaders[p_st];
	}

	void ShaderManager::destroyAllShaders()
	{
		for (int i =0; i < SHADERTYPE_MAX+1; ++i)
		{
			if(m_createdPresetShaders[i] != nullptr)
			{
				delete m_createdPresetShaders[i];
			}
		}
	}
}