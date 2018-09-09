#pragma once
#include "puppy\P_Common.h"
/*
	Callum MacKenzie
	Transform component
*/
namespace kitten
{
	class Transform
	{
	protected:
		float m_rotateDeg, m_xScale, m_yScale, m_zScale;
		glm::vec3 m_translation;

		glm::mat4 m_matTranslation;
		glm::mat4 m_matScale;
		glm::mat4 m_matRotation;

		glm::mat4 m_matWorld;

		bool m_isDirty;

	public:
		Transform();

		virtual void move2D(const float xUnits, const float yUnits);
		virtual void move(const float xUnits, const float yUnits, const float zUnits);
		virtual void place2D(const float x, const float y);
		virtual void place(const float x, const float y, const float z);
		virtual void scale2D(const float xScale, const float yScale);
		virtual void scaleAbsolute(const float xScale, const float yScale, const float zScale);
		virtual void scaleRelative(const float xScale, const float yScale, const float zScale);
		virtual void rotate2D(const float deg);
		virtual void rotateRelative(const float deg, const float xAxis, const float yAxis, const float zAxis);
		virtual void rotateAbsolute(const float deg, const float xAxis, const float yAxis, const float zAxis);

		virtual const glm::vec3& getTranslation() const;

		virtual const glm::mat4& getWorldTransform();
	};
}