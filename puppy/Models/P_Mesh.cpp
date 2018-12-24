#include "P_Mesh.h"

namespace puppy
{
	P_Mesh::P_Mesh(std::vector<NormalVertex>& p_vertices, std::vector<unsigned int>& p_indices, const char* p_pathToTexture) : m_mat(ShaderType::basic),
		m_vao(p_vertices.data(), p_indices.data(), ShaderManager::getShaderProgram(ShaderType::basic), p_vertices.size(), p_indices.size())
	{
		if (p_pathToTexture != nullptr)
		{
			std::string newTexPath(p_pathToTexture);

			auto lastSlash = newTexPath.find_last_of('/');

			if (lastSlash > newTexPath.length())
			{
				lastSlash = newTexPath.find_last_of('\\');
			}

			if (lastSlash < newTexPath.length())
			{
				newTexPath = newTexPath.substr(lastSlash, newTexPath.length());
			}

			newTexPath = "models/textures/" + newTexPath;
			m_mat.setTexture(newTexPath.c_str());
		}
		else
		{
			m_mat.setTexture("textures/black.bmp");
		}
	}

	P_Mesh::P_Mesh(std::vector<NormalVertex>& p_vertices, std::vector<unsigned int>& p_indices, glm::vec4& p_colour) : m_mat(ShaderType::solid_colour),
		m_vao(p_vertices.data(), p_indices.data(), ShaderManager::getShaderProgram(ShaderType::solid_colour), p_vertices.size(), p_indices.size()), m_usesColour(true),
		m_colour(p_colour)
	{

	}

	P_Mesh::~P_Mesh()
	{

	}

	void P_Mesh::render(const glm::mat4& p_worldViewProj)
	{
		m_mat.apply();
		m_mat.setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_worldViewProj);

		if (m_usesColour)
		{
			m_mat.setUniform("colour", m_colour);
		}

		m_vao.drawArrays(GL_TRIANGLES);
	}
}