#include "Transformable.h"

namespace puppy
{

	Transformable::Transformable()
	{
		//Initialize normal member variables
		m_rotateDeg = 0.0f;
		m_translation = glm::vec3(0.0f, 0.0f, 0.0f);

		//Setup the matrices
		m_matTranslation = glm::translate(0.0f, 0.0f, 0.0f);
		m_matScale = glm::scale(1.0f, 1.0f, 1.0f);
		m_matRotation = glm::rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	const glm::mat4& Transformable::getWorldTransform()
	{
		if (m_isDirty)
		{
			m_matWorld = m_matTranslation * m_matRotation * m_matScale;
			m_isDirty = false;
		}

		return m_matWorld;
	}

	void Transformable::move2D(const float xUnits, const float yUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;
	}

	void Transformable::move(const float xUnits, const float yUnits, const float zUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_translation[2] += zUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;
	}

	void Transformable::place2D(const float x, const float y)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_matTranslation = glm::translate(x, y, 0.0f);
		m_isDirty = true;
	}

	void Transformable::place(const float x, const float y, const float z)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_translation[2] = z;
		m_matTranslation = glm::translate(x, y, z);
		m_isDirty = true;
	}

	void Transformable::scale2D(const float xScale, const float yScale)
	{
		m_matScale = glm::scale(xScale, yScale, 1.0f);
		m_isDirty = true;
	}

	void Transformable::scaleAbsolute(const float xScale, const float yScale, const float zScale)
	{
		m_xScale = xScale;
		m_yScale = yScale;
		m_zScale = zScale;
		m_matScale = glm::scale(xScale, yScale, zScale);
		m_isDirty = true;
	}

	void Transformable::scaleRelative(const float xScale, const float yScale, const float zScale)
	{
		m_xScale *= xScale;
		m_yScale *= yScale;
		m_zScale *= zScale;
		m_matScale = glm::scale(m_xScale, m_yScale, m_zScale);
		m_isDirty = true;
	}

	void Transformable::rotate2D(const float deg)
	{
		m_rotateDeg += deg;
		m_matRotation = glm::rotate(m_rotateDeg, glm::vec3(0.0f, 0.0f, 1.0f));
		m_isDirty = true;
	}

	void Transformable::rotateRelative(const float deg, const float xAxis, const float yAxis, const float zAxis)
	{
		m_rotateDeg += deg;
		m_matRotation = m_matRotation * glm::rotate(m_rotateDeg, glm::vec3(xAxis, yAxis, zAxis));
		m_isDirty = true;
	}

	void Transformable::rotateAbsolute(const float deg, const float xAxis, const float yAxis, const float zAxis)
	{
		m_rotateDeg = deg;
		m_matRotation = glm::rotate(deg, glm::vec3(xAxis, yAxis, zAxis));
		m_isDirty = true;
	}

	const glm::vec3& Transformable::getTranslation() const
	{
		return m_translation;
	}
}