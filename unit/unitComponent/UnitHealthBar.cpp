#include "UnitHealthBar.h"
#include "kitten\K_GameObject.h"

namespace unit
{
	puppy::VertexEnvironment* UnitHealthBar::m_backVao = nullptr;
	puppy::VertexEnvironment* UnitHealthBar::m_foreVao = nullptr;
	puppy::Material* UnitHealthBar::m_healthMat = nullptr;
	puppy::Material* UnitHealthBar::m_damageMat = nullptr;
	unsigned int UnitHealthBar::instances = 0;

	UnitHealthBar::UnitHealthBar(const glm::vec2& p_offset) : m_attachedUnit(nullptr), m_offset(glm::translate(glm::vec3(p_offset.x, p_offset.y, 0)))
	{
		if (instances == 0)
		{
			m_healthMat = new puppy::Material(puppy::ShaderType::basic);
			m_healthMat->setTexture(HEALTH_MAT_TEXTURE_PATH);

			m_damageMat = new puppy::Material(puppy::ShaderType::basic);
			m_damageMat->setTexture(DAMAGE_MAT_TEXTURE_PATH);

			puppy::TexturedVertex verts[] =
			{
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f },
				{ 0.0f,  0.5f, 0.0f,		0.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f,  0.5f, 0.0f,		1.0f, 1.0f },
				{ 1.0f, -0.5f, 0.0f,		1.0f, 0.0f },
				{ 0.0f, -0.5f, 0.0f,		0.0f, 0.0f }
			};

			m_backVao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);

			puppy::TexturedVertex foreVerts[] =
			{
				{ 0.0f, -0.5f, 0.01f,		0.0f, 0.0f },
				{ 0.0f,  0.5f, 0.01f,		0.0f, 1.0f },
				{ 1.0f,  0.5f, 0.01f,		1.0f, 1.0f },
				{ 1.0f,  0.5f, 0.01f,		1.0f, 1.0f },
				{ 1.0f, -0.5f, 0.01f,		1.0f, 0.0f },
				{ 0.0f, -0.5f, 0.01f,		0.0f, 0.0f }
			};

			m_backVao = new puppy::VertexEnvironment(foreVerts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
		}

		++instances;
	}

	UnitHealthBar::~UnitHealthBar()
	{
		--instances;

		if (instances == 0)
		{
			delete m_backVao;
			m_backVao = nullptr;

			delete m_foreVao;
			m_foreVao = nullptr;

			delete m_healthMat;
			m_healthMat = nullptr;

			delete m_damageMat;
			m_damageMat = nullptr;
		}

		if (m_isEnabled)
		{
			onDisabled();
		}
	}

	void UnitHealthBar::start()
	{
		m_attachedUnit = m_attachedObject->getComponent<Unit>();
		assert(m_attachedUnit != nullptr);

		onEnabled();
	}

	void UnitHealthBar::onEnabled()
	{
		addToDynamicRender();
	}

	void UnitHealthBar::onDisabled()
	{
		removeFromDynamicRender();
	}

	void UnitHealthBar::render(const glm::mat4& p_viewProj)
	{
		//@TODO: don't do two map lookups each frame per unit
		int currentHealth = m_attachedUnit->m_attributes[UNIT_HP];
		int maxHealth = m_attachedUnit->m_attributes[UNIT_MAX_HP];

		float percentFull = (float)currentHealth / (float)maxHealth;
		glm::mat4 healthScale = glm::scale(glm::vec3(percentFull, 1, 1));

		//@TODO: split these up into different game objects to minimize multiplication

		//Render background(damage) bar
		m_damageMat->apply();
		m_damageMat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * m_offset * getTransform().getWorldTransform());

		m_backVao->drawArrays(GL_TRIANGLES);

		//Render foreground(health) bar
		m_healthMat->apply();
		m_healthMat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, p_viewProj * m_offset * (getTransform().getWorldTransform() * healthScale));

		m_foreVao->drawArrays(GL_TRIANGLES);
	}
}