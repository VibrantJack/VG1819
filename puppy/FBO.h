#pragma once
#include "P_Common.h"
#include "puppy\Texture.h"
#include "puppy\RenderBuffer.h"
namespace puppy
{
	class FBO
	{
	private:
		static GLuint m_boundBuffer;
		GLuint m_id;
	public:
		FBO();
		~FBO();

		void setTexture2D(GLenum p_attachment, const puppy::Texture* p_tex, int p_mipMapLevel);
		void setRenderBuffer(GLenum p_attachment, const puppy::RenderBuffer* p_buffer);
		void apply();
		GLenum getFrameBufferStatus();
		void printFrameBufferStatus();

		static void bindDefault();
	};
}