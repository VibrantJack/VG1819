#pragma once

//-----------------------------------------------------------------------------
// File:			Texture.h
// Original Author:	Callum MacKenzie
//
// Class that creates and handles binding of textures
// only TGA supported
//-----------------------------------------------------------------------------

#include <map>
#include <string>
#include "P_Common.h"

namespace puppy
{
	class Texture
	{
	private:
		GLuint m_tex; //The member texture
		std::string m_name;

		int m_wrapMode, m_minFiltering, m_magFiltering;
		static int sm_boundWrapMode, sm_boundMinFiltering, sm_boundMagFiltering;

		static std::map<std::string, std::pair<GLuint, unsigned int>> sm_loadedTextures;
		static GLuint sm_boundTexture; //Currently bound tex

		void bind() const;
	public:
		Texture(const std::string& p_texName); //Takes the name of the file
		Texture(); //empty texture

		~Texture();

		void setWrapping(const int p_mode);
		void setMinFiltering(const int p_mode);
		void setMagFiltering(const int p_mode);

		const GLuint* getTex() const;
		const std::string& getPath() const;

		static void removeAll();

		void apply() const;
	};
}