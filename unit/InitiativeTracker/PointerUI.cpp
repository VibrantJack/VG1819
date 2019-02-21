#include "PointerUI.h"
#include "puppy/Renderer.h"

puppy::VertexEnvironment* userinterface::PointerUI::sm_vao = nullptr;
int userinterface::PointerUI::sm_instances = 0;

userinterface::PointerUI::PointerUI()
{
	m_mat = new puppy::Material(puppy::ShaderType::alphaTest);
	m_mat->setTexture("textures/ui/ArrowPointer.tga");

	if (sm_instances < 1)
	{
		puppy::TexturedVertex verts[] =
		{
		{ 0.0, 0.0, 0, 0.0, 0.0 },
		{ 0.0, 1.0, 0, 0.0, 1.0 },
		{ 1.0, 1.0, 0, 1.0, 1.0 },

		{ 1.0, 1.0, 0, 1.0, 1.0 },
		{ 1.0, 0.0, 0, 1.0, 0.0 },
		{ 0.0, 0.0, 0, 0.0, 0.0 },
		};
		sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);

		++sm_instances;
	}
}

userinterface::PointerUI::PointerUI(nlohmann::json & p_json) : kitten::K_UIRenderable(p_json)
{
	m_mat = new puppy::Material(puppy::ShaderType::alphaTest);
	m_mat->setTexture(LOOKUPSTRDEF("texture","textures/ui/ArrowPointer.tga").c_str());

	if (sm_instances < 1)
	{
		puppy::TexturedVertex verts[] =
		{
		{ 0.0, 0.0, 0, 0.0, 0.0 },
		{ 0.0, 1.0, 0, 0.0, 1.0 },
		{ 1.0, 1.0, 0, 1.0, 1.0 },

		{ 1.0, 1.0, 0, 1.0, 1.0 },
		{ 1.0, 0.0, 0, 1.0, 0.0 },
		{ 0.0, 0.0, 0, 0.0, 0.0 },
		};
		sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);

		++sm_instances;
	}
}

userinterface::PointerUI::~PointerUI()
{
	delete m_mat;
	if (--sm_instances == 0)
	{
		delete sm_vao;
	}

	if (m_isEnabled)
	{
		removeFromDynamicUIRender();
	}
}

void userinterface::PointerUI::start()
{
	addToDynamicUIRender();
}

void userinterface::PointerUI::onEnabled()
{
	addToDynamicUIRender();
}

void userinterface::PointerUI::onDisabled()
{
	removeFromDynamicUIRender();
}

void userinterface::PointerUI::uiRender(kitten::Camera* p_cam)
{
	m_mat->apply();

	glm::mat4 wvp = p_cam->getOrtho() * getTransform().getWorldTransform();
	m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

	sm_vao->drawArrays(GL_TRIANGLES);
}
