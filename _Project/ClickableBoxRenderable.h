#pragma once
#include "kitten\mouse picking\ClickableBox.h"
#include "kitten\Renderable.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"

class ClickableBoxRenderable : public kitten::Renderable
{
private:
	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;

	puppy::VertexEnvironment* m_vao;
	puppy::Material* m_mat;
public:
	ClickableBoxRenderable();
	~ClickableBoxRenderable();

	virtual void render(const glm::mat4& p_viewProj);
};