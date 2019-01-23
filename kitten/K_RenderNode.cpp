#include "K_RenderNode.h"
#include "puppy\Renderer.h"
#include "kitten\K_ComponentManager.h"

namespace kitten
{
	K_RenderNode::K_RenderNode() : m_parentRenderNode(nullptr)
	{

	}

	K_RenderNode::~K_RenderNode()
	{

	}

	void K_RenderNode::start()
	{
		auto parent = getTransform().getParent();
		if (parent != nullptr)
		{
			m_parentRenderNode = parent->getAttachedGameObject().getComponent<K_RenderNode>();
			if (m_parentRenderNode == nullptr)
			{
				m_parentRenderNode = static_cast<K_RenderNode*>(K_ComponentManager::getInstance()->createComponent("K_RenderNode"));
				parent->getAttachedGameObject().addComponent(m_parentRenderNode);
			}
		}

		onEnabled();
	}

	void K_RenderNode::onEnabled()
	{
		if (m_parentRenderNode != nullptr)
		{
			m_parentRenderNode->addChild(this);
		}
		else
		{
			puppy::Renderer::getInstance()->addUIToRender(this);
		}
	}

	void K_RenderNode::onDisabled()
	{
		if (m_parentRenderNode != nullptr)
		{
			m_parentRenderNode->removeChild(this);
		}
		else
		{
			puppy::Renderer::getInstance()->removeUIFromRender(this);
		}
	}

	void K_RenderNode::addUIRenderable(puppy::P_UIRenderable* p_toAdd)
	{
		m_uiRenderables.insert(p_toAdd);
	}

	void K_RenderNode::removeUIRenderable(puppy::P_UIRenderable* p_toRemove)
	{
		m_uiRenderables.erase(p_toRemove);
	}

	void K_RenderNode::addChild(K_RenderNode* p_toAdd)
	{
		m_childRenderNodes.insert(p_toAdd);
	}

	void K_RenderNode::removeChild(K_RenderNode* p_toRemove)
	{
		m_childRenderNodes.erase(p_toRemove);
	}
}