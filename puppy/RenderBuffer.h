#pragma once
#include "P_Common.h"
namespace puppy
{
	class RenderBuffer
	{
	private:
		static GLuint m_boundBuffer;
		GLuint m_id;

	public:
		RenderBuffer(GLenum p_internalFormat, int p_width, int p_height);
		~RenderBuffer();

		void apply();
		GLuint getId() const { return m_id; }
	};
}