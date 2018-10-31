#pragma once
#include "P_Common.h"
#include "ShaderProgram.h"

namespace puppy
{

	/*
		This class abstracts a VAO.
	*/
	class VertexEnvironment
	{
	private:
		static GLuint m_boundVao;
		
		GLuint m_vao, m_vbo;
		unsigned int m_numIndices;

		/*
			setupCommon() is a helper method that sets up common elements
			for different vertex data types
		*/
		void setupCommon();
	public:
		//@TODO: don't require seperate constructors for each type of vertex
		VertexEnvironment(const TexturedVertex p_data[], const ShaderProgram* p_program, int p_numElements);
		VertexEnvironment(const NormalVertex p_data[], const ShaderProgram* p_program, int p_numElements);
		VertexEnvironment(const ParticleVertex p_data[], const ShaderProgram* p_program, int p_numElements);
		~VertexEnvironment();

		void drawArrays(GLenum p_mode);
		void drawArrays(GLenum p_mode, int p_offset, int p_numTriangles);

		void* map(GLenum p_access);
		void* mapRange(GLenum p_access, int p_offset, int p_length);
		GLenum unmap();
		void unmapRange();
	};
}