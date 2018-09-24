#include "Transform.h"

namespace kitten
{

	Transform::Transform() : m_forward(0,0,1), m_matTranslation(glm::translate(0,0,0)), m_matScale(glm::scale(1,1,1)), m_translation(0,0,0), m_scale(1,1,1),
		m_parent(nullptr), m_ignoresParent(true)
	{

	}

	const glm::mat4& Transform::getWorldTransform()
	{
		if (m_isDirty)
		{
			m_matWorldNoScale = m_matTranslation * glm::mat4_cast(m_quatRotation);
			m_matWorld = m_matWorldNoScale * m_matScale;
			m_isDirty = false;
		}

		return m_matWorld;
	}

	const glm::mat4& Transform::getWorldTransformNoScale()
	{
		if (m_isDirty)
		{
			m_matWorldNoScale = m_matTranslation * glm::mat4_cast(m_quatRotation);
			m_matWorld = m_matWorldNoScale * m_matScale;
			m_isDirty = false;
		}

		return m_matWorldNoScale;
	}

	void Transform::move2D(const float xUnits, const float yUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;

		notifyPositionListeners();
	}

	void Transform::move(const float xUnits, const float yUnits, const float zUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_translation[2] += zUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;

		notifyPositionListeners();
	}

	void Transform::place2D(const float x, const float y)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_matTranslation = glm::translate(x, y, 0.0f);
		m_isDirty = true;

		notifyPositionListeners();
	}

	void Transform::place(const float x, const float y, const float z)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_translation[2] = z;
		m_matTranslation = glm::translate(x, y, z);
		m_isDirty = true;

		notifyPositionListeners();
	}

	void Transform::scale2D(const float xScale, const float yScale)
	{
		m_matScale = glm::scale(xScale, yScale, 1.0f);
		m_isDirty = true;

		notifyScaleListeners();
	}

	void Transform::scaleAbsolute(const float xScale, const float yScale, const float zScale)
	{
		m_scale = glm::vec3(xScale, yScale, zScale);

		m_matScale = glm::scale(m_scale);
		m_isDirty = true;

		notifyScaleListeners();
	}

	void Transform::scaleRelative(const float xScale, const float yScale, const float zScale)
	{
		m_scale += glm::vec3(xScale, yScale, zScale);
		m_matScale = glm::scale(m_scale);
		m_isDirty = true;

		notifyScaleListeners();
	}

	//NOT FUNCTIONAL ANYMORE!!
	void Transform::rotate2D(const float deg)
	{
		m_rotateDeg += deg;
		m_matRotation = glm::rotate(m_rotateDeg, glm::vec3(0.0f, 0.0f, 1.0f));
		m_isDirty = true;
	}

	void Transform::rotateRelative(const glm::vec3& rot)
	{
		m_quatRotation = glm::quat(rot * (float)DEG_TO_RAD_FACTOR) * m_quatRotation;
		m_forward = glm::vec3(0, 0, 1) * m_quatRotation;

		m_isDirty = true;

		notifyRotationListeners();
	}

	void Transform::rotateAbsolute(const glm::vec3& rot)
	{
		m_quatRotation = glm::quat(rot * (float)DEG_TO_RAD_FACTOR);
		m_forward = glm::vec3(0, 0, 1) * m_quatRotation;

		m_isDirty = true;

		notifyRotationListeners();
	}

	const glm::vec3& Transform::getTranslation() const
	{
		return m_translation;
	}

	const glm::quat& Transform::getRotation() const
	{
		return m_quatRotation;
	}

	const glm::vec3& Transform::getForward() const
	{
		return m_forward;
	}

	const glm::vec3& Transform::getScale() const
	{
		return m_scale;
	}

	bool Transform::getIgnoreParent() const
	{
		return m_ignoresParent;
	}

	void Transform::setIgnoreParent(bool p_ignores)
	{
		m_ignoresParent = p_ignores;
	}

	void Transform::setParent(Transform* p_parent)
	{
		m_parent = p_parent;
	}

	void Transform::addChild(Transform* p_child)
	{
		m_children.push_back(p_child);
	}

	bool Transform::removeChild(const Transform* p_child)
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (p_child == *it)
			{
				m_children.erase(it);
				return true;
			}
		}

		return false;
	}

	void Transform::addPositionListener(TransformPositionListener* p_toAdd)
	{
		m_positionListeners.push_back(p_toAdd);
	}

	void Transform::addScaleListener(TransformScaleListener* p_toAdd)
	{
		m_scaleListeners.push_back(p_toAdd);
	}

	void Transform::addRotationListener(TransformRotationListener* p_toAdd)
	{
		m_rotationListeners.push_back(p_toAdd);
	}


	void Transform::removePositionListener(TransformPositionListener* p_toRemove)
	{
		auto end = m_positionListeners.cend();
		for (auto it = m_positionListeners.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_positionListeners.erase(it);
				return;
			}
		}
	}

	void Transform::removeScaleListener(TransformScaleListener* p_toRemove)
	{
		auto end = m_scaleListeners.cend();
		for (auto it = m_scaleListeners.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_scaleListeners.erase(it);
				return;
			}
		}
	}

	void Transform::removeRotationListener(TransformRotationListener* p_toRemove)
	{
		auto end = m_rotationListeners.cend();
		for (auto it = m_rotationListeners.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_rotationListeners.erase(it);
				return;
			}
		}
	}

	void Transform::notifyScaleListeners()
	{
		auto end = m_scaleListeners.cend();
		for (auto it = m_scaleListeners.begin(); it != end; ++it)
		{
			(*it)->onScaleChanged(m_scale);
		}
	}

	void Transform::notifyPositionListeners()
	{
		auto end = m_positionListeners.cend();
		for (auto it = m_positionListeners.begin(); it != end; ++it)
		{
			(*it)->onPosChanged(m_translation);
		}
	}

	void Transform::notifyRotationListeners()
	{
		auto end = m_rotationListeners.cend();
		for (auto it = m_rotationListeners.begin(); it != end; ++it)
		{
			(*it)->onRotationChanged(m_quatRotation);
		}
	}
}