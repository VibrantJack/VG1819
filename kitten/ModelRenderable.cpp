#include "ModelRenderable.h"

ModelRenderable::ModelRenderable(const char* p_pathToModel) : m_model(p_pathToModel)
{

}

ModelRenderable::~ModelRenderable()
{
	if (m_isEnabled)
	{
		onDisabled();
	}
}

void ModelRenderable::start()
{
	onEnabled();
}

void ModelRenderable::onEnabled()
{
	addToDynamicRender();
}

void ModelRenderable::onDisabled()
{
	removeFromDynamicRender();
}

void ModelRenderable::render(const glm::mat4& p_viewProj)
{
	m_model.render(p_viewProj * getTransform().getWorldTransform());
}