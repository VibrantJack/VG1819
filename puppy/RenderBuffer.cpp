#include "RenderBuffer.h"
namespace puppy
{
	GLuint RenderBuffer::m_boundBuffer = 0;

	RenderBuffer::RenderBuffer(GLenum p_internalFormat, int p_width, int p_height)
	{
		glGenRenderbuffers(1, &m_id);
		glBindRenderbuffer(GL_RENDERBUFFER, m_id);
		m_boundBuffer = m_id;

		glRenderbufferStorage(GL_RENDERBUFFER, p_internalFormat, p_width, p_height);
	}

	RenderBuffer::~RenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_id);
	}

	void RenderBuffer::apply()
	{
		if (m_boundBuffer != m_id)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, m_id);
			m_boundBuffer = m_id;
		}
	}
}