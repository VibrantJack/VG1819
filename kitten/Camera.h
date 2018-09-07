#pragma once
#include "puppy\P_Common.h"
#include "../Shapes/RenderableFrustum.h"
#include "Frustum.h"

namespace scene
{
	/*
		Callum MacKenzie
		Camera Interface
	*/

	class Camera
	{
	protected:
		bool m_isProjDirty = true;

		float m_fov;
		float m_nearClip, m_farClip;
		int m_winWidth, m_winHeight;

		glm::mat4 m_proj;

		//Frustum information
		float m_nearRectHeight, m_nearRectWidth, m_farRectHeight, m_farRectWidth;

		//for testing
		shapes::RenderableFrustum* m_renderFrust;

		//Helper methods
		glm::mat4& getProj(); //cannot be const because of calculating when dirty
		Frustum computeViewFrustum(const glm::vec3& p_cameraPos, const glm::vec3& p_look, const glm::vec3& p_up) const;

	public:
		Camera();
		~Camera();

		virtual void setFOV(float p_fov);
		virtual void setNearClip(float p_near);
		virtual void setFarClip(float p_far);
		virtual void setWinWidth(int p_width);
		virtual void setWinHeight(int p_height);

		virtual void update(float p_deltaTime) = 0;

		virtual const glm::mat4& getViewProj() = 0;
		virtual const glm::mat3& getViewInverse() const = 0;
		virtual const Frustum& getViewFrustum() = 0;

		virtual void renderViewFrustum(const glm::mat4& p_viewProj) const;
	};
}
