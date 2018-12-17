#include "ClickableFrameRender.h"

void ClickableFrameRender::start()
{
	kitten::ClickableFrame* clickable = m_attachedObject->getComponent<kitten::ClickableFrame>();
	assert(clickable != nullptr);

	const glm::vec2& minPoint = clickable->getOriginalMinPoint();
	const glm::vec2& maxPoint = clickable->getOriginalMaxPoint();

	puppy::TexturedVertex verts[] =
	{
		// Front
		{ minPoint.x, minPoint.y,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y,		0.0f, 0.0f },
		{ minPoint.x,  maxPoint.y,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y,		0.0f, 0.0f },
		{ maxPoint.x,  maxPoint.y,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y,		0.0f, 0.0f },
		{ maxPoint.x, minPoint.y,		0.0f, 0.0f },
		{ minPoint.x, minPoint.y,		0.0f, 0.0f },
	};

	m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 48);

	onEnabled();
}

void ClickableFrameRender::onEnabled()
{
	addToDynamicRender();
}

void ClickableFrameRender::onDisabled()
{
	removeFromDynamicRender();
}

ClickableFrameRender::ClickableFrameRender() :m_vao(nullptr), m_mat(new puppy::Material(puppy::ShaderType::basic))
{
	m_mat->setTexture("textures/crap/cocacola.tga");
}

ClickableFrameRender::~ClickableFrameRender()
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

void ClickableFrameRender::render(const glm::mat4 & p_viewProj)
{
	m_mat->apply();

	m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * getTransform().getWorldTransform());

	m_vao->drawArrays(GL_LINES);
}
