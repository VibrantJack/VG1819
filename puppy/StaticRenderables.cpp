#include "StaticRenderables.h"
#include "ShaderManager.h"

namespace puppy
{
	void StaticRenderables::addToRender(const Texture* p_texNeeded, TexturedVertex p_data[])
	{
		auto it = m_texturedData.find(p_texNeeded);
		
		if (it == m_texturedData.end())
		{
			//Construct new vector with data
			std::vector<TexturedVertex> toInsert;
			toInsert.insert(toInsert.begin(), p_data, p_data + (sizeof(p_data) / (sizeof(p_data[0]))));
			
			//Insert into map
			m_texturedData.insert(std::make_pair(p_texNeeded, toInsert));
		}
		else
		{
			//add to existing vector
			auto vec = it->second;
			vec.insert(vec.end(), p_data, p_data + (sizeof(p_data) / (sizeof(p_data[0]))));
		}

		m_texturedDataIsDirty[p_texNeeded] = true;
	}

	void StaticRenderables::constructRenderable(const Texture* p_where)
	{
		//get vector to create buffer from
		auto it = m_texturedData.find(p_where);
		auto vec = it->second;

		//construct single buffer from data

		VertexEnvironment* toRender = new VertexEnvironment(vec.data(), 
			ShaderManager::getShaderProgram(ShaderType::basic), vec.size());

		if (m_toRender[p_where] != nullptr)
		{
			delete m_toRender[p_where];
		}

		//insert into render map
		m_toRender[p_where] = toRender;
		
		//save number of vertices
		m_vertexCount[p_where] = sizeof(vec.data())/sizeof(vec.data()[0]);

		//set dirty bool
		m_texturedDataIsDirty[p_where] = false;
	}

	void StaticRenderables::render(const glm::mat4& p_viewProj)
	{
		//All three iterators will have the same size.
		auto isDirtyIt = m_texturedDataIsDirty.begin(); 
		auto vertexCountIt = m_vertexCount.begin();

		for (auto renderIt = m_toRender.begin(); renderIt != m_toRender.end(); ++renderIt)
		{
			//check if the data is dirty
			if (isDirtyIt->second)
			{
				//it is, have to construct environment for data
				constructRenderable(isDirtyIt->first);
			}

			//apply shaderProgram
			ShaderManager::applyShader(ShaderType::basic);

			//apply tex
			renderIt->first->apply();
			
			//apply uniform (don't need a world matrix since everything should already be in world space)
			glUniformMatrix4fv(ShaderManager::getShaderProgram(ShaderType::basic)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME), 1, GL_FALSE, glm::value_ptr(p_viewProj));

			//Draw!
			renderIt->second->drawArrays(GL_TRIANGLES);

			//advance iterators
			++isDirtyIt;
			++vertexCountIt;
		}
	}
}