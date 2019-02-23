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
		
		bool m_hasColour;
		glm::vec4 m_colour; //hacky because adding memorizing uniforms will take a bit and it is not scheduled

		bool m_hasMatLightProperties;
		glm::vec4 m_matAmbient, m_matDiffuse;

		inline void applyMatLightProperties() const
		{
			if (m_hasMatLightProperties)
			{
				setUniform("matAmbient", m_matAmbient);
				setUniform("matDiffuse", m_matDiffuse);
			}
		}

	public:
		Material(ShaderType p_shaderType);
		Material(const Material& p_other);
		~Material();

		virtual bool operator==(const Material& p_other) const;
		virtual Material* clone() const;

		virtual void setTexture(const char* p_pathToTex);
		virtual void setTexture(puppy::Texture* p_tex);
		puppy::Texture* getTexture() const;

		virtual void setColour(const glm::vec4& m_colour); //see above comment
		virtual void setMatAmbient(const glm::vec4& m_ambient);
		virtual void setMatDiffuse(const glm::vec4& m_diffuse);

		virtual bool hasColour() const
		{
			return m_hasColour;
		}

		virtual bool hasMatLightProperties() const
		{
			return m_hasMatLightProperties;
		}

		virtual const glm::vec4& getColour() const
		{
			return m_colour;
		}

		virtual const glm::vec4& getMatAmbient() const
		{
			return m_matAmbient;
		}

		virtual const glm::vec4& getMatDiffuse() const
		{
			return m_matDiffuse;
		}

		//One-time set
		void setUniform(const std::string& p_name, const glm::mat4& p_mat4) const;
		void setUniform(const std::string& p_name, const glm::mat3& p_mat3) const;
		void setUniform(const std::string& p_name, const glm::vec4& p_vec4) const;
		void setUniform(const std::string& p_name, const glm::vec3& p_vec3) const;
		void setUniform(const std::string& p_name, const glm::vec2& p_vec2) const;
		void setUniform(const std::string& p_name, const float& p_float) const;
		void setUniform(const std::string& p_name, const int p_int) const;

		int getUniformPlace(const std::string& p_name);

		virtual puppy::ShaderProgram* getShader() const { return m_shader; }

		virtual void apply() const;

		// Blending related
		GLenum m_modeRGB= GL_FUNC_ADD, m_modeAlpha= GL_FUNC_ADD;
		GLenum m_srcRGB= GL_SRC_ALPHA, m_dstRGB = GL_ONE_MINUS_SRC_ALPHA, m_srcAlpha = GL_ONE, m_dstAlpha = GL_ZERO;

		void applyBlendEquations() 
		{
			glBlendEquationSeparate(m_modeRGB, m_modeAlpha);
		}
		
		void applyBlendFunc() 
		{
			glBlendFuncSeparate(m_srcRGB,m_dstRGB, m_srcAlpha,m_dstAlpha); 
		}
	};
}