#pragma once

#include "P_Common.h"
#include "Transformable.h"

#include <string>
#include <vector>


namespace puppy
{
	class RenderableNode : public Transformable
	{
	private:
		std::vector<RenderableNode*> m_children;
		RenderableNode* m_parent = nullptr;
		bool m_wasRendered = false;

		std::string m_name;
		float m_boundingRadius = 0;
	public:
		void setName(const std::string& p_name) { m_name = p_name; };
		const std::string& getName() { return m_name; }

		virtual const glm::mat4& getDerivedTransform();

		virtual void setBoundingRadius(float p_radius);
		float getBoundingRadius() const { return m_boundingRadius; }

		virtual void renderFamily(const glm::mat4& p_viewProj);
		virtual void updateFamily(float p_deltaTime);

		virtual void render(const glm::mat4& p_viewProj) = 0;
		virtual void update(float p_deltaTime) = 0;
	};
}