#include "P_Model.h"

#include <iostream>

namespace puppy
{
	P_Model::P_Model(const char* p_pathToModel)
	{
		Assimp::Importer importer;
		auto scene = importer.ReadFile(p_pathToModel, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_EmbedTextures | aiProcess_GenUVCoords | aiProcess_OptimizeMeshes | aiProcess_OptimizeGraph);
		
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			assert(false); //load failed
		}

		aiNode* rootNode = scene->mRootNode;
		
		processNode(rootNode, scene);
	}

	P_Model::~P_Model()
	{

	}

	void P_Model::processNode(aiNode* p_node, const aiScene* p_scene)
	{
		for (unsigned int i = 0; i < p_node->mNumMeshes; ++i)
		{
			auto mesh = p_scene->mMeshes[p_node->mMeshes[i]];
			processMesh(mesh, p_scene);
		}

		for (unsigned int i = 0; i < p_node->mNumChildren; ++i)
		{
			processNode(p_node->mChildren[i], p_scene);
		}
	}

	void P_Model::processMesh(aiMesh* p_mesh, const aiScene* p_scene)
	{
		std::vector<NormalVertex> vertices;
		std::vector<unsigned int> indices;
		const char* tex = nullptr;

		// Vertices
		vertices.reserve(p_mesh->mNumVertices);
		for (unsigned int i = 0; i < p_mesh->mNumVertices; ++i)
		{
			//There will always be a position vertex
			const auto& aiVertex = p_mesh->mVertices[i];
			glm::vec3 vertex(aiVertex.x, aiVertex.y, aiVertex.z);

			//Normals and UVs are optional
			glm::vec3 normal(0, 0, 0);
			glm::vec2 uv(0, 0);

			if (p_mesh->HasNormals())
			{
				const auto& aiNormal = p_mesh->mNormals[i];
				normal = glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z);
			}

			if (p_mesh->HasTextureCoords)
			{
				const auto& aiUV = p_mesh->mTextureCoords[0][i];
				uv = glm::vec2(aiUV.x, aiUV.y);
			}

			NormalVertex puppyVertex = 
			{
				//Position
				aiVertex.x, aiVertex.y, aiVertex.z, 
				//Normal
				normal.x, normal.y, normal.z,
				//UV
				uv.x, uv.y
			};

			vertices.push_back(puppyVertex);
		}

		// Indicies
		indices.reserve(p_mesh->mNumFaces);
		for (unsigned int i = 0; i < p_mesh->mNumFaces; ++i)
		{
			const auto& face = p_mesh->mFaces[i];
			
			for(unsigned int n = 0; n < face.mNumIndices; ++n)
			{
				indices.push_back(face.mIndices[n]);
			}
		}

		// Material(s)
		if (p_mesh->mMaterialIndex >= 0)
		{
			auto material = p_scene->mMaterials[p_mesh->mMaterialIndex];

			int numDiffuse = material->GetTextureCount(aiTextureType_DIFFUSE);
			if (numDiffuse > 0)
			{
				if (numDiffuse > 1)
				{
					std::cout << p_mesh->mName.C_Str() << " has more than one diffuse texture! Using the first.." << std::endl;
				}

				aiString texPath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
				tex = texPath.C_Str();
			}
		}

		m_meshes.push_back(new P_Mesh(vertices, indices, tex));
	}

	void P_Model::render(const glm::mat4& p_worldViewProj)
	{
		auto end = m_meshes.cend();
		for (auto it = m_meshes.cbegin(); it != end; ++it)
		{
			(*it)->render(p_worldViewProj);
		}
	}
}