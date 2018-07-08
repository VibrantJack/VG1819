#include "RenderableNode.h"

namespace puppy
{
	const glm::mat4& RenderableNode::getDerivedTransform()
	{
		//@TODO: implement / finish
		RenderableNode* parent = m_parent;
		while (parent != nullptr)
		{
			parent = parent->m_parent;
		}

		return this->getWorldTransform();
	}

	void RenderableNode::setBoundingRadius(float p_radius)
	{
		//Check if this radius is larger than child's radius
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if ((*it)->getBoundingRadius() >= p_radius)
			{
				return;
			}
		}

		m_boundingRadius = p_radius;
	}

	void RenderableNode::renderFamily(const glm::mat4& p_viewProj)
	{
		if (!m_wasRendered)
		{
			this->render(p_viewProj);
			m_wasRendered = true;

			//Not sure if a situation exists where a root node could be rendered but not its children
			for (auto it = m_children.begin(); it != m_children.end(); ++it)
			{
				(*it)->renderFamily(p_viewProj);
			}
		}
		
		
	}

	void RenderableNode::updateFamily(float p_deltaTime)
	{
		this->update(p_deltaTime);

		m_wasRendered = false; //Assumes update is always called before render (as it should be)

		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			(*it)->updateFamily(p_deltaTime);
		}
	}
}