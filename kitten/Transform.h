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

	class Transform
	{
	private:
		enum ParentDirtyType {position, rotation, scale, unknown};

		K_GameObject& m_attachedObject;

		//Actual transform related
		float m_rotateDeg;
		glm::vec3 m_scale;
		glm::vec3 m_translation;
		glm::vec3 m_forward;

		glm::mat4 m_matTranslation;
		glm::mat4 m_matScale;
		glm::quat m_quatRotation;
		glm::mat4 m_matRotation;
		glm::mat4 m_matWorldNoScale;
		glm::mat4 m_matWorld;

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

		void notifyScaleListeners();
		void notifyPositionListeners();
		void notifyRotationListeners();

		void addChild(Transform* p_child);

		void setChildrenDirty(ParentDirtyType p_type);
		void onParentDirty(ParentDirtyType p_type);

	public:
		Transform(K_GameObject& p_owner);
		~Transform();

		K_GameObject& getAttachedGameObject();

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
		const glm::mat4& getWorldTransformNoScale();
		const glm::vec3& getForward() const;

		//Parent / children related

		bool getIgnoreParent() const;
		void setIgnoreParent(bool p_ignores);

		void setParent(Transform* p_parent);
		bool removeChild(const Transform* p_child);

		//Listeners
		void addPositionListener(TransformPositionListener* p_toAdd);
		void addScaleListener(TransformScaleListener* p_toAdd);
		void addRotationListener(TransformRotationListener* p_toAdd);

		void removePositionListener(TransformPositionListener* p_toRemove);
		void removeScaleListener(TransformScaleListener* p_toRemove);
		void removeRotationListener(TransformRotationListener* p_toRemoe);
	};

	
}