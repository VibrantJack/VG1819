#include "P_Mesh.h"

namespace puppy
{
	P_Mesh::P_Mesh(std::vector<NormalVertex>& p_vertices, std::vector<unsigned int>& p_indices, const char* p_pathToTexture) : m_mat(ShaderType::basic),
		m_vao(p_vertices.data(), p_indices.data(), ShaderManager::getShaderProgram(ShaderType::basic), p_vertices.size(), p_indices.size())
	{
		std::string newTexPath(p_pathToTexture);
		newTexPath = "models/textures/" + newTexPath;
		m_mat.setTexture(newTexPath.c_str());
	}

	P_Mesh::~P_Mesh()
	{

	}

	void P_Mesh::render(const glm::mat4& p_worldViewProj)
	{
		m_mat.apply();
		m_mat.setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_worldViewProj);

		m_vao.drawArrays(GL_TRIANGLES);
	}
}