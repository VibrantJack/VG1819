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

	void StaticRenderables::addToRender(const Texture* p_texNeeded, TexturedVertex p_data[], int p_numElements)
	{
		auto found = m_texturedData.find(*p_texNeeded->getTex());

		if (found != m_texturedData.end())
		{
			//add to existing vector
			auto& vec = found->second.first;
			vec.insert(vec.end(), p_data, p_data + p_numElements);

			//mark dirty
			found->second.second = true;
		}
		else
		{
			//We need to create a vector for this new texture
			std::vector<TexturedVertex> toInsert(p_data, p_data + p_numElements);

			//Insert into map
			m_texturedData.insert(std::make_pair(*p_texNeeded->getTex(), std::make_pair(toInsert,true)));

			//Create copy of texture
			puppy::Texture* tex = new puppy::Texture(p_texNeeded->getPath());
			m_idToTex.insert(std::make_pair(*tex->getTex(), tex));
		}
	}

	void StaticRenderables::constructRenderable(GLuint p_where)
	{
		//get vector to create buffer from
		auto found = m_texturedData.find(p_where);
		auto vec = found->second.first;

		//construct single buffer from data
		VertexEnvironment* toRender = new VertexEnvironment(vec.data(), 
			ShaderManager::getShaderProgram(ShaderType::basic), vec.size());

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