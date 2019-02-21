#pragma once

#include "kitten\K_Component.h"

#include <unordered_set>

namespace puppy
{
	class Renderer;
}

namespace kitten
{
	class K_UIRenderable;

	class K_RenderNode : public K_Component, public TransformParentListener
	{
		friend class puppy::Renderer;
	private:
		bool m_disabledCalled;
		bool m_isRendering;

		K_RenderNode* m_parentRenderNode;
		std::unordered_set<K_RenderNode*> m_childRenderNodes;
		std::unordered_set<K_UIRenderable*> m_uiRenderables, m_trasparentUIRenderables;

		void addChild(K_RenderNode* p_toAdd);
		void removeChild(K_RenderNode* p_toRemove);

		virtual void start() override;
		virtual void onEnabled() override;
		virtual void onDisabled() override;
	public:
		K_RenderNode();
		~K_RenderNode();

		void addUIRenderable(K_UIRenderable* p_toAdd);
		void removeUIRenderable(K_UIRenderable* p_toRemove);

		void addTransparentUIRenderable(K_UIRenderable* p_toAdd);
		void removeTransparentUIRenderable(K_UIRenderable* p_toRemove);

		virtual void onParentChanged(Transform* p_newParent) override;
	};
}