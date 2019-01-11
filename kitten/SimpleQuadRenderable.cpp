#include "SimpleQuadRenderable.h"
#include "puppy\StaticRenderables.h"

puppy::VertexEnvironment* kitten::SimpleQuadRenderable::sm_vao = nullptr;
int kitten::SimpleQuadRenderable::sm_instances = 0;

puppy::VertexEnvironment* kitten::SimpleQuadRenderable::sm_upRightVao = nullptr;
int kitten::SimpleQuadRenderable::sm_upRightInstances = 0;

void kitten::SimpleQuadRenderable::addToStaticRender()
{
	/*
	if (m_mat.getNumberOfTextures() == 1)
	{
		puppy::TexturedVertex verts[] =
		{
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
			{ 0.5f, 0.0f, 0.5f,			0.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 1.0f },
			{ -0.5f, 0.0f,-0.5f,		1.0f, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f, 0.0f },
		};

		//Transform into world space
		puppy::StaticRenderables::putInWorldSpace(verts, 6, getTransform().getWorldTransform());

		m_staticTex = m_mat.getOwnedTexture();

		K_Renderable::addToStaticRender(m_staticTex, verts, 6);
	}
	*/
}

void kitten::SimpleQuadRenderable::start()
{
	if (m_isStatic)
	{
		m_isRenderingStatic = true;
		addToStaticRender();
	}
	else
	{
		addToDynamicRender();
	}
}

void kitten::SimpleQuadRenderable::onDisabled()
{
	if (m_isStatic)
	{
		removeFromStaticRender(*m_mat);
	}
	else
	{
		removeFromDynamicRender();
	}
}

void kitten::SimpleQuadRenderable::onEnabled()
{
	if (m_isStatic)
	{
		addToStaticRender();
	}
	else
	{
		addToDynamicRender();
	}
}

kitten::SimpleQuadRenderable::SimpleQuadRenderable(const std::string & p_texPath, bool p_isStatic, bool p_upRight)
	: m_isStatic(p_isStatic), m_isUpright(p_upRight)
{
	m_mat = new puppy::Material(puppy::ShaderType::alphaTest);

	if (!p_texPath.empty())
	{
		m_mat->setTexture(p_texPath.c_str());
	}

	if (!p_upRight)
	{
		//If we have not initialized the vao yet
		if (sm_instances < 1)
		{
			//setup the vao
			puppy::TexturedVertex verts[] =
			{
			{ -0.5f, 0.0f, 0.5f,		0.0f, 1.0f },
			{ 0.5f, 0.0f, 0.5f,			1.0f, 1.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 0.0f },
			{ 0.5f, 0.0f,-0.5f,			1.0f, 0.0f },
			{ -0.5f, 0.0f,-0.5f,		0.0f, 0.0f },
			{ -0.5f, 0.0f, 0.5f,		0.0f, 1.0f },
			};
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}
		++sm_instances;
	}
	else
	{
		if (sm_upRightInstances < 1)
		{
			//setup the vao
			puppy::TexturedVertex verts[] =
			{
				{ -0.5f, -0.5f, 0.0f,		0.0f, 0.0f },
				{ -0.5f,  0.5f, 0.0f,		0.0f, 1.0f },
				{ 0.5f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 0.5f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 0.5f, -0.5f, 0.0f,		1.0f, 0.0f },
				{ -0.5f, -0.5f, 0.0f,		0.0f, 0.0f },
			};
			sm_upRightVao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}
		++sm_upRightInstances;
	}
}

kitten::SimpleQuadRenderable::~SimpleQuadRenderable()
{
	if (!m_isUpright)
	{
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}
	}
	else
	{
		if (--sm_upRightInstances == 0)
		{
			delete sm_upRightVao;
		}
	}
	
	if (!m_isStatic)
	{
		if (m_isEnabled)
		{
			removeFromDynamicRender();
		}
	}
	else
	{
		if (m_isEnabled && m_isRenderingStatic)
		{
			removeFromStaticRender(*m_mat);
		}
		else if (m_isEnabled)
		{
			removeFromDynamicRender();
		}
	}
}

void kitten::SimpleQuadRenderable::setTexture(const char * p_pathToTex)
{
	m_mat->setTexture(p_pathToTex);

	if (m_isStatic && m_isEnabled)
	{
		m_isRenderingStatic = true;
		addToStaticRender(); //Started, but we were not added to static render because we had no texture
	}
}

void kitten::SimpleQuadRenderable::render(const glm::mat4 & p_viewProj)
{
	m_mat->apply();

	//Set world matrix
	glm::mat4 wvp = p_viewProj * getTransform().getWorldTransform();
	m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

	//render
	if (!m_isUpright)
	{
		sm_vao->drawArrays(GL_TRIANGLES);
	}
	else
	{
		sm_upRightVao->drawArrays(GL_TRIANGLES);
	}
}
