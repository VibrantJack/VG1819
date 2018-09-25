#include "Texture.h"

namespace puppy
{

	GLuint Texture::sm_boundTexture = 0;
	std::map<std::string, std::pair<GLuint, int>> Texture::sm_loadedTextures;

	int Texture::sm_boundWrapMode = 0;
	int Texture::sm_boundMagFiltering = 0;
	int Texture::sm_boundMinFiltering = 0;

	Texture::Texture(const std::string& p_texName)
	{
		Texture::m_minFiltering = GL_NEAREST_MIPMAP_LINEAR;
		Texture::m_magFiltering = GL_LINEAR;
		Texture::m_wrapMode = GL_REPEAT;
		Texture::m_name = p_texName;

		if (Texture::sm_loadedTextures.find(p_texName) == Texture::sm_loadedTextures.end()) //If this texture has not already been loaded
		{
			//Generate the texture
			glGenTextures(1, &(Texture::m_tex));
			glBindTexture(GL_TEXTURE_2D, Texture::m_tex);
			Texture::sm_boundTexture = Texture::m_tex;

			GLFWimage img;
			glfwReadImage(p_texName.c_str(), &img, 0);
			glTexImage2D(GL_TEXTURE_2D, 0, img.Format, img.Width, img.Height, 0, img.Format, GL_UNSIGNED_BYTE, img.Data);
			glfwFreeImage(&img);

			glGenerateMipmap(GL_TEXTURE_2D); //Mipmaps
			
			//Insert this texture into the map, starting with a reference count of 1
			Texture::sm_loadedTextures.insert(std::make_pair(p_texName, std::make_pair(Texture::m_tex, 1)));
			
		}
		else //We have already loaded this texture
		{
			Texture::m_tex = Texture::sm_loadedTextures[p_texName].first;
			Texture::sm_loadedTextures[p_texName].second++;
		}
	}

	Texture::Texture()
	{
		glGenTextures(1, &m_tex);
		Texture::bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	Texture::~Texture()
	{
		sm_loadedTextures[m_name].second--; //subtract from reference count
		if (sm_loadedTextures[m_name].second == 0)
		{
			glDeleteTextures(1, &m_tex);
			sm_loadedTextures.erase(m_name);
		}
	}

	void Texture::apply() const
	{
		Texture::bind();

		//Updating bound texture settings if needed
		if (Texture::sm_boundMinFiltering != Texture::m_minFiltering)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFiltering);
			sm_boundMinFiltering = m_minFiltering;
		}

		if (Texture::sm_boundMagFiltering != Texture::m_magFiltering)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFiltering);
			sm_boundMagFiltering = m_magFiltering;
		}

		if (Texture::sm_boundWrapMode != Texture::m_wrapMode)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapMode);
			sm_boundWrapMode = m_wrapMode;
		}
	}

	void Texture::bind() const
	{
		if (Texture::sm_boundTexture != Texture::m_tex) { //If we aren't using this texture already
			glBindTexture(GL_TEXTURE_2D, Texture::m_tex); //Use this texture
			Texture::sm_boundTexture = Texture::m_tex; //And update what we are using
		}
	}

	void Texture::setWrapping(const int p_mode)
	{
		if (p_mode != Texture::m_wrapMode)
		{
			Texture::m_wrapMode = p_mode;
		}
	}

	void Texture::setMinFiltering(const int p_mode)
	{
		if (p_mode != Texture::m_minFiltering)
		{
			Texture::m_minFiltering = p_mode;
		}
	}

	void Texture::setMagFiltering(const int p_mode)
	{
		if (p_mode != Texture::m_magFiltering)
		{
			Texture::m_magFiltering = p_mode;
		}
	}

	void Texture::removeAll()
	{
		Texture::sm_boundTexture = 0;
		Texture::sm_loadedTextures.clear();
	}

	const GLuint* Texture::getTex() const
	{
		return &(Texture::m_tex);
	}

	const std::string& Texture::getPath() const
	{
		return m_name;
	}
}