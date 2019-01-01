#include "QuadEdgeRenderable.h"

puppy::VertexEnvironment* kitten::QuadEdgeRenderable::sm_vao = nullptr;
int kitten::QuadEdgeRenderable::sm_instances = 0;

void kitten::QuadEdgeRenderable::start()
{
}

void kitten::QuadEdgeRenderable::onEnabled()
{
	addToDynamicRender();
}

void kitten::QuadEdgeRenderable::onDisabled()
{
	removeFromDynamicRender();
}

kitten::QuadEdgeRenderable::QuadEdgeRenderable()
	: m_mat(new puppy::Material(puppy::ShaderType::basic))
{
	m_mat->setTexture(DEFAULT_EDGE_TEXTURE);

	//If we have not initialized the vao yet
	if (sm_instances < 1)
	{
		//setup the vao
		puppy::TexturedVertex verts[] =
		{
		{ -0.5f, 0.01f, 0.5f,		0.0f, 0.0f },
		{ 0.5f, 0.01f, 0.5f,			0.0f, 0.0f },
		{ -0.5f, 0.01f, -0.5f,		0.0f, 0.0f },
		{ 0.5f, 0.01f, -0.5f,		0.0f, 0.0f },
		{ 0.5f, 0.01f, -0.5f,		0.0f, 0.0f },
		{ 0.5f, 0.01f, 0.5f,			0.0f, 0.0f },
		{ -0.5f, 0.01f, -0.5f,		0.0f, 0.0f },
		{ -0.5f, 0.01f, 0.5f,		0.0f, 0.0f },
		};
		sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 8);
	}
	++sm_instances;

	onEnabled();
}

kitten::QuadEdgeRenderable::~QuadEdgeRenderable()
{
	if (m_isEnabled)
	{
		onDisabled();
	}

	if (--sm_instances == 0)
	{
		delete sm_vao;
	}
}

void kitten::QuadEdgeRenderable::render(const glm::mat4 & p_viewProj)
{
	m_mat->apply();

	m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * getTransform().getWorldTransform());

	sm_vao->drawArrays(GL_LINES);
}

void kitten::QuadEdgeRenderable::setTexture(const std::string & p_tex)
{
	m_mat->setTexture(p_tex.c_str());
}
