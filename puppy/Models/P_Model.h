#pragma once

#include "puppy\P_Common.h"
#include "P_Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include <vector>

// Based on: https://learnopengl.com/Model-Loading/Model

namespace puppy
{
	class P_Model
	{
	private:
		std::vector<P_Mesh*> m_meshes;

		void processNode(aiNode* p_node, const aiScene* p_scene);
		void processMesh(aiMesh* mesh, const aiScene* p_scene);
	public:
		P_Model(const char* p_pathToModel);
		~P_Model();

		virtual void render(const glm::mat4& p_worldViewProj);
	};
}