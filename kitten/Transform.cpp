#include "Transform.h"

namespace kitten
{

	Transform::Transform() : m_forward(0,0,1), m_matTranslation(glm::translate(0,0,0)), m_matScale(glm::scale(1,1,1))
	{

	}

	const glm::mat4& Transform::getWorldTransform()
	{
		if (m_isDirty)
		{
			m_matWorld = m_matTranslation * glm::mat4_cast(m_quatRotation) * m_matScale;
			m_isDirty = false;
		}

		return m_matWorld;
	}

	void Transform::move2D(const float xUnits, const float yUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;
	}

	void Transform::move(const float xUnits, const float yUnits, const float zUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_translation[2] += zUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;
	}

	void Transform::place2D(const float x, const float y)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_matTranslation = glm::translate(x, y, 0.0f);
		m_isDirty = true;
	}

	void Transform::place(const float x, const float y, const float z)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_translation[2] = z;
		m_matTranslation = glm::translate(x, y, z);
		m_isDirty = true;
	}

	void Transform::scale2D(const float xScale, const float yScale)
	{
		m_matScale = glm::scale(xScale, yScale, 1.0f);
		m_isDirty = true;
	}

	void Transform::scaleAbsolute(const float xScale, const float yScale, const float zScale)
	{
		m_xScale = xScale;
		m_yScale = yScale;
		m_zScale = zScale;
		m_matScale = glm::scale(xScale, yScale, zScale);
		m_isDirty = true;
	}

	void Transform::scaleRelative(const float xScale, const float yScale, const float zScale)
	{
		m_xScale *= xScale;
		m_yScale *= yScale;
		m_zScale *= zScale;
		m_matScale = glm::scale(m_xScale, m_yScale, m_zScale);
		m_isDirty = true;
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
		m_forward = m_quatRotation * glm::vec3(0,0,1);
		
		m_isDirty = true;
	}

	void Transform::rotateAbsolute(const glm::vec3& rot)
	{
		m_quatRotation = glm::quat(rot * (float)DEG_TO_RAD_FACTOR);
		m_forward = m_quatRotation * glm::vec3(0, 0, 1);

		m_isDirty = true;
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
}