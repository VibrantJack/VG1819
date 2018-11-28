#include "ClickableBoxRenderable.h"
#include "kitten\K_GameObject.h"

ClickableBoxRenderable::ClickableBoxRenderable() : m_vao(nullptr), m_mat(new puppy::Material(puppy::ShaderType::basic))
{
	m_mat->setTexture("textures/crap/cocacola.tga"); // Makes the lines red
}

ClickableBoxRenderable::~ClickableBoxRenderable()
{
	if (m_isEnabled)
	{
		onDisabled();
	}

	if (m_vao != nullptr)
	{
		delete m_vao;
	}
}

void ClickableBoxRenderable::start()
{
	kitten::ClickableBox* clickableBox = m_attachedObject->getComponent<kitten::ClickableBox>();
	assert(clickableBox != nullptr);

	const glm::vec3& minPoint = clickableBox->getOriginalMinPoint();
	const glm::vec3& maxPoint = clickableBox->getOriginalMaxPoint();
	
	puppy::TexturedVertex verts[] =
	{
		// Front
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },

		// Back
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },

		// Left
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },

		// Right
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },

		// Top
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y, maxPoint.z,		0.0f, 0.0f },

		// Bottom
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, minPoint.z,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y, maxPoint.z,		0.0f, 0.0f },
	};

	m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 48);

	onEnabled();
}

void ClickableBoxRenderable::onEnabled()
{
	addToDynamicRender();
}

void ClickableBoxRenderable::onDisabled()
{
	removeFromDynamicRender();
}

void ClickableBoxRenderable::render(const glm::mat4& p_viewProj)
{
	m_mat->apply();

	m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * getTransform().getWorldTransform());

	m_vao->drawArrays(GL_LINES);
}