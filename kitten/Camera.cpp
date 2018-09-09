#include "Camera.h"

namespace kitten
{
	Camera::Camera() : m_fov(45.0f), m_nearClip(0.1f), m_farClip(1000.0f), m_winWidth(1280.0f), m_winHeight(720.0f)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::setFOV(float p_fov)
	{
		m_isProjDirty = true;
		m_fov = p_fov;
	}

	void Camera::setNearClip(float p_near)
	{
		m_isProjDirty = true;
		m_nearClip = p_near;
	}

	void Camera::setFarClip(float p_far)
	{
		m_isProjDirty = true;
		m_farClip = p_far;
	}

	void Camera::setWinWidth(int p_width)
	{
		m_isProjDirty = true;
		m_winWidth = p_width;
	}

	void Camera::setWinHeight(int p_height)
	{
		m_isProjDirty = true;
		m_winHeight = p_height;
	}

	glm::mat4& Camera::getProj()
	{
		if (m_isProjDirty)
		{
			float screenRatio = (float)m_winWidth / m_winHeight;

			m_proj = glm::perspective(m_fov, screenRatio, m_nearClip, m_farClip);

			//view frustum calculations
			float tang = (float)tan((PI/180.0f) * m_fov * 0.5f);
			m_nearRectHeight = m_nearClip * tang;
			m_nearRectWidth = m_nearRectHeight * screenRatio;
			m_farRectHeight = m_farClip * tang;
			m_farRectWidth = m_farRectHeight * screenRatio;

			m_isProjDirty = false;
		}

		return m_proj;
	}

	//@TODO: Finish this
	const glm::mat4& Camera::getViewProj()
	{
		Transform& transform = getTransform();
		const glm::vec3& pos = transform.getTranslation();
		glm::vec3 upVector;
		glm::vec3 lookDirection;
		glm::mat4 view = glm::lookAt(pos, pos + lookDirection, upVector);

		return view;
	}

	//@TODO: Finish this
	const glm::mat3& Camera::getViewInverse()
	{
		return glm::mat3();
	}

	//From: http://www.lighthouse3d.com/tutorials/view-frustum-culling/geometric-approach-extracting-the-planes/

	scene::Frustum Camera::computeViewFrustum(const glm::vec3& p_cameraPos, const glm::vec3& p_look, const glm::vec3& p_up) const
	{
		scene::Frustum toReturn;

		glm::vec3 z = p_cameraPos - p_look;
		z = glm::normalize(z);

		glm::vec3 x = glm::cross(p_up, z);
		x = glm::normalize(x);

		glm::vec3 y = glm::cross(z, x);
	
		glm::vec3 nc = p_cameraPos - z * m_nearClip;
		glm::vec3 fc = p_cameraPos - z * m_farClip;

		glm::vec3 yNear = y * m_nearRectHeight, xNear = x * m_nearRectWidth,
			yFar = y * m_farRectHeight, xFar = x * m_farRectWidth;

		glm::vec3 ntl = nc + yNear - xNear;
		glm::vec3 ntr = nc + yNear + xNear;
		glm::vec3 nbl = nc - yNear - xNear;
		glm::vec3 nbr = nc - yNear + xNear;

		// compute the 4 corners of the frustum on the far plane
		glm::vec3 ftl = fc + yFar - xFar;
		glm::vec3 ftr = fc + yFar + xFar;
		glm::vec3 fbl = fc - yFar - xFar;
		glm::vec3 fbr = fc - yFar + xFar;

		//Top 
		toReturn.planes[0] = scene::computePlane(ntr, ntl, ftl);
		//Bottom
		toReturn.planes[1] = scene::computePlane(nbl, nbr, fbr);
		//Left
		toReturn.planes[2] = scene::computePlane(ntl, nbl, fbl);
		//Right
		toReturn.planes[3] = scene::computePlane(nbr, ntr, fbr);
		//Near
		toReturn.planes[4] = scene::computePlane(ntl, ntr, nbr);
		//Far
		toReturn.planes[5] = scene::computePlane(ftr, ftl, fbl);

		return toReturn;
	}
}