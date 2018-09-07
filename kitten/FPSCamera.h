#pragma once
#include "puppy\P_Common.h"
#include "../Shapes/RenderableFrustum.h"
#include "Camera.h"

namespace scene
{
	class FPSCamera : public Camera
	{
	private:
		//Private members
		glm::mat4 m_viewProj;
		glm::mat3 m_viewInverse;

		float m_lookHorizAngle = PI, m_lookVertAngle = 0.5f;
		glm::vec3 m_cameraPos;

		float m_lookSensitivity = 0.02f;
		float m_moveSpeed = 2.5f;

		bool m_newViewproj = true;
		Frustum m_viewFrustum;

	public:
		FPSCamera();
		~FPSCamera();

		void setLookSensitivity(float p_sensitivity);
		void setMoveSpeed(float p_speed);

		virtual const glm::mat4& getViewProj() override;
		virtual const glm::mat3& getViewInverse() const override;
		virtual void update(float p_deltaTime) override;
		void place(const glm::vec3& p_pos) { m_cameraPos = p_pos; }

		virtual const Frustum& getViewFrustum() override;
	};
}