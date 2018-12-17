#pragma once
#include "kitten/mouse picking/ClickableFrame.h"
#include "kitten\Renderable.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Material.h"

class ClickableFrameRender: public kitten::Renderable
{
private:
	virtual void start() override;
	virtual void onEnabled() override;
	virtual void onDisabled() override;

	puppy::VertexEnvironment* m_vao;
	puppy::Material* m_mat;
public:
	ClickableFrameRender();
	~ClickableFrameRender();

	virtual void render(const glm::mat4& p_viewProj);
};
