#include "Camera.h"
#include "K_CameraList.h"

#include "kitten\InputManager.h"

namespace kitten
{
	Camera::Camera() : m_fov(45.0f), m_nearClip(0.1f), m_farClip(1000.0f), m_winWidth(1280.0f), m_winHeight(720.0f), m_rendersUI(true)
	{
		if(K_CameraList::getInstance()->getSceneCamera() == nullptr)
		{
			K_CameraList::getInstance()->setSceneCamera(this);
		}
		
		m_emptyMat4[0][0] = 0;
		m_emptyMat4[1][1] = 0;
		m_emptyMat4[2][2] = 0;
		m_emptyMat4[3][3] = 0;

	}

	Camera::~Camera()
	{
		if (K_CameraList::getInstance()->getSceneCamera() == this)
		{
			K_CameraList::getInstance()->setSceneCamera(nullptr);
		}
	}

	void Camera::update()
	{
		if (K_CameraList::getInstance()->getSceneCamera() == this)
		{
			calcProjAndOrtho();

			Transform& transform = getTransform();
			const glm::vec3& pos = transform.getTranslation();
			glm::vec3 upVector = transform.getUpVector();
			glm::vec3 lookDirection = transform.getForward();

			m_view = glm::lookAt(pos, pos + lookDirection, upVector);
			m_viewInverse4 = glm::inverse(m_view);
			m_viewInverse = (glm::mat3)m_viewInverse4;

			m_viewProj = getProj() * m_view;
		}
	}

	void Camera::setFOV(float p_fov)
	{
		m_isProjDirty = true;
		m_fov = p_fov;
	}

	float Camera::getFOV() const
	{
		return m_fov;
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

	void Camera::setRendersUI(bool p_rendersUI)
	{
		m_rendersUI = p_rendersUI;
	}

	const glm::mat4& Camera::getProj()
	{
		if (m_isProjDirty)
		{
			calcProjAndOrtho();
		}

		return m_proj;
	}

	const glm::mat4& Camera::getOrtho()
	{
		if (!m_rendersUI)
		{
			return m_emptyMat4;
		}
		//else

		if (m_isProjDirty)
		{
			calcProjAndOrtho();
		}
		
		return m_ortho;
	}

	void Camera::calcProjAndOrtho()
	{
		auto inputMan = input::InputManager::getInstance();
		m_winWidth = inputMan->getWindowWidth();
		m_winHeight = inputMan->getWindowHeight();

		float screenRatio = (float)m_winWidth / (float)m_winHeight;

		m_proj = glm::perspective(m_fov, screenRatio, m_nearClip, m_farClip);

		//view frustum calculations
		float tang = (float)tan((PI / 180.0f) * m_fov * 0.5f);
		m_nearRectHeight = m_nearClip * tang;
		m_nearRectWidth = m_nearRectHeight * screenRatio;
		m_farRectHeight = m_farClip * tang;
		m_farRectWidth = m_farRectHeight * screenRatio;

		m_ortho = glm::ortho(0.0f, (float)m_winWidth, 0.0f, (float)m_winHeight, -0.1f, 1.0f);
		//m_ortho = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -0.1f, 1.0f);

		m_isProjDirty = false;
	}

	const glm::mat4& Camera::getViewProj() const
	{
		return m_viewProj;
	}

	const glm::mat4& Camera::getView() const
	{
		return m_view;
	}

	const glm::mat3& Camera::getMat3ViewInverse() const
	{
		return m_viewInverse;
	}

	const glm::mat4& Camera::getMat4ViewInverse() const
	{
		return m_viewInverse4;
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