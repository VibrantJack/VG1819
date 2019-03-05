#pragma once
#include <vector>
#include "puppy\P_Common.h"
/*
	Callum MacKenzie
	Transform component
*/
namespace kitten
{
	// Interfaces for transform changing events

	class TransformScaleListener
	{
	public:
		virtual void onScaleChanged(const glm::vec3& p_newScale) = 0;
	};

	class TransformPositionListener
	{
	public:
		virtual void onPosChanged(const glm::vec3& p_newPos) = 0;
	};

	class TransformRotationListener
	{
	public:
		virtual void onRotationChanged(const glm::quat& p_newRot) = 0;
	};

	class K_GameObject;
	class TransformParentListener;

	class Transform
	{
	private:
		enum ParentDirtyType {position, rotation, scale, unknown};

		K_GameObject& m_attachedObject;

		//Actual transform related
		float m_rotateDeg;
		glm::vec3 m_scale;
		glm::vec3 m_translation;
		glm::vec3 m_derivedScale;
		glm::vec3 m_derivedTranslation;

		glm::vec3 m_forward;
		glm::vec3 m_upVector;

		glm::mat4 m_matTranslation;
		glm::mat4 m_derivedMatTranslation;
		glm::mat4 m_matScale;
		glm::quat m_quatRotation;
		glm::quat m_derivedQuatRotation;
		glm::mat4 m_matRotation;
		glm::mat4 m_rotScale;
		glm::mat4 m_derivedRotScale;

		glm::mat4 m_matWorldNoScale;
		glm::mat4 m_matWorld;
		glm::mat3 m_matWorldIT;

		bool m_isDirty;

		//Parent / children related
		bool m_ignoresParent;
		Transform* m_parent;
		std::vector<Transform*> m_children;

		//Listener related
		// I can't imagine a transform having more than two listeners for any given
		// property, so I have elected to just keep listeners as a vector
		// -Callum
		std::vector<TransformScaleListener*> m_scaleListeners;
		std::vector<TransformPositionListener*> m_positionListeners;
		std::vector<TransformRotationListener*> m_rotationListeners;
		std::vector<TransformParentListener*> m_parentListeners;

		void notifyScaleListeners();
		void notifyPositionListeners();
		void notifyRotationListeners();
		void notifyParentListeners();

		void addChild(Transform* p_child);

		void setChildrenDirty(ParentDirtyType p_type);
		void onParentDirty(ParentDirtyType p_type);

		inline void rebuildWorldMatrix()
		{
			m_matWorldNoScale = m_matTranslation * glm::mat4_cast(m_quatRotation);
			m_matWorld = m_matWorldNoScale * m_matScale;

			if (!m_ignoresParent && m_parent != nullptr)
			{
				m_matWorldNoScale = m_parent->getWorldTransformNoScale() * m_matWorldNoScale;
				m_matWorld = m_matWorldNoScale * glm::scale((m_scale * m_parent->getScale()));

				m_derivedRotScale = glm::mat4_cast(m_derivedQuatRotation) * glm::scale(m_scale * m_parent->getScale());
				m_derivedMatTranslation = glm::translate(m_derivedTranslation);
			}

			m_matWorldIT = glm::inverse((glm::mat3)m_matWorld);
			m_matWorldIT = glm::transpose(m_matWorldIT);
			m_rotScale = glm::mat4_cast(m_quatRotation) * m_matScale;

			m_isDirty = false;
		}

	public:
		Transform(K_GameObject& p_owner);
		~Transform();

		K_GameObject& getAttachedGameObject();

		void move2D(const float xUnits, const float yUnits);
		void move(const float xUnits, const float yUnits, const float zUnits);
		void place2D(const float x, const float y);
		void place(const float x, const float y, const float z);
		void placeInWorld(const float x, const float y, const float z);

		void scale2D(const float xScale, const float yScale);
		void scaleAbsolute(const float xScale, const float yScale, const float zScale);
		void scaleRelative(const float xScale, const float yScale, const float zScale);
		void scaleInWorld(const float xScale, const float yScale, const float zScale);

		void rotate2D(const float deg);
		void rotateRelative(const glm::vec3& rot);
		void rotateAbsolute(const glm::vec3& rot);
		void rotateAbsQuat(const glm::quat& rot);

		const glm::vec3& getTranslation() const;
		const glm::vec3& getRelativeTranslation() const;
		const glm::quat& getRotation() const;
		const glm::vec3& getScale() const;
		glm::vec2 getScale2D() const;
		const glm::vec3& getLocalScale() const;

		const glm::mat4& getTranslationMat4();
		const glm::mat4& getRotScaleMat4();

		const glm::mat4& getWorldTransform();
		const glm::mat4& getWorldTransformNoScale();
		const glm::mat3& getWorldIT();
		const glm::vec3& getForward() const;
		const glm::vec3& getUpVector() const;


		//Parent / children related

		bool getIgnoreParent() const;
		void setIgnoreParent(bool p_ignores);

		bool hasChildren() const;
		const std::vector<Transform*>& getChildren() const;

		void setParent(Transform* p_parent);
		Transform* getParent();
		bool removeChild(const Transform* p_child);

		//Listeners
		void addPositionListener(TransformPositionListener* p_toAdd);
		void addScaleListener(TransformScaleListener* p_toAdd);
		void addRotationListener(TransformRotationListener* p_toAdd);
		void addParentListener(TransformParentListener* p_toAdd);

		void removePositionListener(TransformPositionListener* p_toRemove);
		void removeScaleListener(TransformScaleListener* p_toRemove);
		void removeRotationListener(TransformRotationListener* p_toRemoe);
		void removeParentListener(TransformParentListener* p_toRemove);
	};

	class TransformParentListener
	{
	public:
		virtual void onParentChanged(Transform* p_newParent) = 0;
	};
}