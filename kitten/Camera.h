#pragma once
#include "puppy\P_Common.h"
#include "K_Component.h"
#include "Frustum.h"

namespace kitten
{
	/*
		Callum MacKenzie
		Camera Interface
	*/

	class Camera : public kitten::K_Component
	{
	protected:
		bool m_isProjDirty = true;

		float m_fov;
		float m_nearClip, m_farClip;
		int m_winWidth, m_winHeight;

		glm::mat4 m_proj, m_view;
		glm::mat3 m_viewInverse;

		//Frustum information
		float m_nearRectHeight, m_nearRectWidth, m_farRectHeight, m_farRectWidth;

		//Helper methods
		glm::mat4& getProj(); //cannot be const because of calculating when dirty
		scene::Frustum computeViewFrustum(const glm::vec3& p_cameraPos, const glm::vec3& p_look, const glm::vec3& p_up) const;

	public:
		Camera();
		~Camera();

		virtual bool hasUpdate() const override { return true; }

		virtual void update();

		virtual void setFOV(float p_fov);
		virtual void setNearClip(float p_near);
		virtual void setFarClip(float p_far);
		virtual void setWinWidth(int p_width);
		virtual void setWinHeight(int p_height);

		virtual float getFOV() const;

		virtual glm::mat4 getViewProj();
		virtual const glm::mat3& getViewInverse() const;
	};
}
