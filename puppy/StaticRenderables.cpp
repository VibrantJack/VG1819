#include "StaticRenderables.h"
#include "ShaderManager.h"

namespace puppy
{
	StaticRenderables* StaticRenderables::sm_instance = nullptr;

	StaticRenderables::StaticRenderables()
	{

	}

	StaticRenderables::~StaticRenderables()
	{

	}

	void StaticRenderables::addToRender(const void* p_owner, const Texture* p_texNeeded, TexturedVertex p_data[], int p_numElements)
	{
		auto found = m_texturedData.find(*p_texNeeded->getTex());

		std::vector<TexturedVertex> toInsert(p_data, p_data + p_numElements);

		if (found != m_texturedData.end())
		{
			//add to existing map
			auto& map = found->second.first;
			
			toInsert.insert(toInsert.begin(), p_data, p_data + p_numElements);

			map.insert(std::make_pair(p_owner, toInsert));

			//mark dirty
			found->second.second = true;
		}
		else
		{
			//make new map
			std::unordered_map<const void*, std::vector<TexturedVertex>> newMap;
			newMap.insert(std::make_pair(p_owner, toInsert));

			//insert map into data
			m_texturedData.insert(std::make_pair(*p_texNeeded->getTex(), std::make_pair(newMap, true)));

			//Create copy of texture
			puppy::Texture* tex = new puppy::Texture(p_texNeeded->getPath());
			m_idToTex.insert(std::make_pair(*tex->getTex(), tex));
		}
	}

	void StaticRenderables::removeFromRender(const void* p_owner, const Texture* p_tex)
	{
		//Search for texture
		auto found = m_texturedData.find(*p_tex->getTex());
		if (found != m_texturedData.end())
		{
			//Search for owner in texture's map
			auto& vecMap = (*found).second.first;
			auto ownerFound = vecMap.find(p_owner);
			if (ownerFound != vecMap.end())
			{
				vecMap.erase(ownerFound);
				//set dirty
				(*found).second.second = true;
			}
		}
	}

	void StaticRenderables::constructRenderable(GLuint p_where)
	{
		//get vector to create buffer from
		auto found = m_texturedData.find(p_where);
		auto map = found->second.first;

		//Get size of vector needed
		
		auto it = map.begin();
		auto end = map.cend();
		if (it != end)
		{
			std::vector<TexturedVertex>::size_type sum = (*it).second.size();

			while (it != end)
			{
				sum += (*it).second.size();
				++it;
			}

			//allocate in one go
			std::vector<TexturedVertex> createdData;
			createdData.reserve(sum);

			//insert into vector
			for (auto it = map.begin(); it != end; ++it)
			{
				auto vec = (*it).second;
				createdData.insert(createdData.end(), vec.begin(), vec.end());
			}

			//construct single buffer from data
			VertexEnvironment* toRender = new VertexEnvironment(createdData.data(),
				ShaderManager::getShaderProgram(ShaderType::basic), createdData.size());

			auto foundRender = m_toRender.find(m_idToTex[p_where]);
			if (foundRender != m_toRender.end())
			{
				delete foundRender->second;
				foundRender->second = toRender;
			}
			else
			{
				m_toRender.insert(std::make_pair(m_idToTex[p_where], toRender));
			}
		}
		

		//clean dirty flag
		found->second.second = false;
	}

	void StaticRenderables::render(const glm::mat4& p_viewProj)
	{
		//Check for dirty data
		auto texEnd = m_texturedData.cend();
		for (auto it = m_texturedData.begin(); it != texEnd; ++it)
		{
			if (it->second.second)
			{
				constructRenderable(it->first);
			}
		}

		for (auto renderIt = m_toRender.begin(); renderIt != m_toRender.end(); ++renderIt)
		{
			//apply shaderProgram
			ShaderManager::applyShader(ShaderType::basic);

			//apply tex
			renderIt->first->apply();
			
			//apply uniform (don't need a world matrix since everything should already be in world space)
			glUniformMatrix4fv(ShaderManager::getShaderProgram(ShaderType::basic)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME), 1, GL_FALSE, glm::value_ptr(p_viewProj));

			//Draw!
			renderIt->second->drawArrays(GL_TRIANGLES);
		}
	}

	void StaticRenderables::clearAllData()
	{
		//Delete all existing renderables
		for (auto it = m_toRender.begin(); it != m_toRender.end(); it = m_toRender.erase(it))
		{
			delete (*it).first;
			delete (*it).second;
		}

		//Clear everything else
		m_texturedData.clear();
		m_idToTex.clear();
	}

	//Static method for putting vertices in world space
	void StaticRenderables::putInWorldSpace(TexturedVertex p_toTransform[], int p_numElements, const glm::mat4& p_worldMat)
	{
		glm::vec4 tempVec(0,0,0,1);
		for (int i = 0; i < p_numElements; ++i)
		{
			TexturedVertex& currentVert = p_toTransform[i];
			tempVec.x = currentVert.x;
			tempVec.y = currentVert.y;
			tempVec.z = currentVert.z;
			
			tempVec = p_worldMat * tempVec;
			
			currentVert.x = tempVec.x;
			currentVert.y = tempVec.y;
			currentVert.z = tempVec.z;
		}
	}
}