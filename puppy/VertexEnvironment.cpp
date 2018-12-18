	#include "VertexEnvironment.h"

namespace puppy
{
	GLuint VertexEnvironment::m_boundVao = 0;

	void VertexEnvironment::setupCommon()
	{
		m_hasEBO = false;

		//Setup vao
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		m_boundVao = m_vao;

		//Buffer data
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	}

	VertexEnvironment::VertexEnvironment(const TexturedVertex p_data[], const ShaderProgram* p_program, int p_numElements)
	{
		setupCommon();
		m_numVertices = p_numElements;

		glBufferData(GL_ARRAY_BUFFER, SIZE_OF_TEXTURED_VERTEX * p_numElements, p_data, GL_STATIC_DRAW);
		
		//Get attrib locations
		int posAttr = p_program->getAttrLocation("a_position");
		int uvAttr = p_program->getAttrLocation("a_uv1");
		
		//Enable attribs
		glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_TEXTURED_VERTEX, 0); 
		glEnableVertexAttribArray(posAttr);

		glVertexAttribPointer(uvAttr, 2, GL_FLOAT, GL_FALSE, SIZE_OF_TEXTURED_VERTEX, (void*)(SIZE_OF_GLFLOAT*3));
		glEnableVertexAttribArray(uvAttr);
	}

	VertexEnvironment::VertexEnvironment(const NormalVertex p_data[], const ShaderProgram* p_program, int p_numElements)
	{
		setupCommon();
		m_numVertices = p_numElements;
		
		glBufferData(GL_ARRAY_BUFFER, SIZE_OF_NORMAL_VERTEX * p_numElements, p_data, GL_STATIC_DRAW);

		//Get attrib locations
		int posAttr = p_program->getAttrLocation("a_position");
		int uvAttr = p_program->getAttrLocation("a_uv1");
		int normalAttr = p_program->getAttrLocation("a_normal");

		//Enable attribs
		glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, 0);
		glEnableVertexAttribArray(posAttr);
		
		glVertexAttribPointer(normalAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, (void*)(SIZE_OF_GLFLOAT * 3));
		glEnableVertexAttribArray(normalAttr);

		glVertexAttribPointer(uvAttr, 2, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, (void*)(SIZE_OF_GLFLOAT* 6));
		glEnableVertexAttribArray(uvAttr);
	}

	VertexEnvironment::VertexEnvironment(const ParticleVertex p_data[], const ShaderProgram* p_program, int p_numElements)
	{
		setupCommon();
		m_numVertices = p_numElements;

		glBufferData(GL_ARRAY_BUFFER, SIZE_OF_PARTICLE_VERTEX * p_numElements, p_data, GL_DYNAMIC_DRAW);

		//Get attrib locations
		int posAttr = p_program->getAttrLocation("a_position");
		int uvAttr = p_program->getAttrLocation("a_uv1");
		int tintAttr = p_program->getAttrLocation("a_color");

		//Enable attribs
		glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_PARTICLE_VERTEX, 0);
		glEnableVertexAttribArray(posAttr);

		glVertexAttribPointer(uvAttr, 2, GL_FLOAT, GL_FALSE, SIZE_OF_PARTICLE_VERTEX, (void*)(SIZE_OF_GLFLOAT * 3));
		glEnableVertexAttribArray(uvAttr);

		glVertexAttribPointer(tintAttr, 4, GL_FLOAT, GL_FALSE, SIZE_OF_PARTICLE_VERTEX, (void*)(SIZE_OF_GLFLOAT * 5));
		glEnableVertexAttribArray(tintAttr);
	}

	VertexEnvironment::VertexEnvironment(const NormalVertex p_data[], const unsigned int p_indices[], const ShaderProgram* p_program, int p_numVertices, int p_numIndicies) : m_numVertices(p_numVertices), m_numIndices(p_numIndicies)
	{
		setupCommon();
		m_hasEBO = true;

		glBufferData(GL_ARRAY_BUFFER, SIZE_OF_NORMAL_VERTEX * p_numVertices, p_data, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_numIndicies * sizeof(unsigned int), p_indices, GL_STATIC_DRAW);

		//Get attrib locations
		int posAttr = p_program->getAttrLocation("a_position");
		int uvAttr = p_program->getAttrLocation("a_uv1");
		int normalAttr = p_program->getAttrLocation("a_normal");

		//Enable attribs
		glVertexAttribPointer(posAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, 0);
		glEnableVertexAttribArray(posAttr);

		glVertexAttribPointer(normalAttr, 3, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, (void*)(SIZE_OF_GLFLOAT * 3));
		glEnableVertexAttribArray(normalAttr);

		glVertexAttribPointer(uvAttr, 2, GL_FLOAT, GL_FALSE, SIZE_OF_NORMAL_VERTEX, (void*)(SIZE_OF_GLFLOAT * 6));
		glEnableVertexAttribArray(uvAttr);
	}

	VertexEnvironment::~VertexEnvironment()
	{
		glDeleteBuffers(1, &m_vbo);
		if (m_boundVao == m_vao)
		{
			m_boundVao = 0;
		}

		if (m_hasEBO)
		{
			glDeleteBuffers(1, &m_ebo);
		}

		glDeleteVertexArrays(1, &m_vao);
	}

	void VertexEnvironment::drawArrays(GLenum p_mode)
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
		}

		if (m_hasEBO)
		{
			glDrawElements(p_mode, m_numIndices, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(p_mode, 0, m_numVertices);
		}
	}

	void VertexEnvironment::drawArrays(GLenum p_mode, int p_offset, int p_numTriangles)
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
		}

		glDrawArrays(p_mode, p_offset, p_numTriangles);
	}

	void* VertexEnvironment::map(GLenum p_access)
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
			
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo); //bind array buffer

		return glMapBuffer(GL_ARRAY_BUFFER, p_access);
	}

	void* VertexEnvironment::mapRange(GLenum p_access, int p_offset, int p_length)
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo); //bind array buffer
		
		return glMapBufferRange(GL_ARRAY_BUFFER, p_offset, p_length, p_access);
	}

	GLenum VertexEnvironment::unmap()
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
		}

		return glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void VertexEnvironment::unmapRange()
	{
		if (m_boundVao != m_vao)
		{
			glBindVertexArray(m_vao);
			m_boundVao = m_vao;
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}