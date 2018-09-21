#pragma once
#include <vector>
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
		float m_rotateDeg;
		glm::vec3 m_scale;
		glm::vec3 m_translation;
		glm::vec3 m_forward;

		glm::mat4 m_matTranslation;
		glm::mat4 m_matScale;
		glm::quat m_quatRotation;
		glm::mat4 m_matRotation;
		glm::mat4 m_matWorld;

		bool m_isDirty;

		bool m_ignoresParent;
		Transform* m_parent;
		std::vector<Transform*> m_children;

	public:
		Transform();

		void move2D(const float xUnits, const float yUnits);
		void move(const float xUnits, const float yUnits, const float zUnits);
		void place2D(const float x, const float y);
		void place(const float x, const float y, const float z);
		void scale2D(const float xScale, const float yScale);
		void scaleAbsolute(const float xScale, const float yScale, const float zScale);
		void scaleRelative(const float xScale, const float yScale, const float zScale);
		void rotate2D(const float deg);
		void rotateRelative(const glm::vec3& rot);
		void rotateAbsolute(const glm::vec3& rot);

		const glm::vec3& getTranslation() const;
		const glm::quat& getRotation() const;
		const glm::vec3& getScale() const;

		const glm::mat4& getWorldTransform();
		const glm::vec3& getForward() const;


		bool getIgnoreParent() const;
		void setIgnoreParent(bool p_ignores);

		void setParent(Transform* p_parent);
		void addChild(Transform* p_child);
		bool removeChild(const Transform* p_child);


	};
}