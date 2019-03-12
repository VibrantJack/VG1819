#include "Transform.h"
#include "K_GameObjectManager.h"

namespace kitten
{

	Transform::Transform(K_GameObject& p_owner) : m_forward(0,0,1), m_matTranslation(glm::translate(0,0,0)), m_matScale(glm::scale(1,1,1)), m_translation(0,0,0), m_scale(1,1,1),
		m_derivedTranslation(0,0,0), m_derivedScale(1,1,1), m_rotateDeg(0), m_parent(nullptr), m_ignoresParent(true), m_attachedObject(p_owner)
	{

	}

	Transform::~Transform()
	{
		if (!m_children.empty())
		{
			auto list = m_children;
			auto end = list.end();
			for (auto it = list.begin(); it != end; ++it)
			{
				(*it)->setParent(nullptr);
			}
		}

		if (m_parent != nullptr)
		{
			m_parent->removeChild(this);
		}
	}

	K_GameObject& Transform::getAttachedGameObject()
	{
		return m_attachedObject;
	}

	const glm::mat4& Transform::getWorldTransform()
	{
		if (m_isDirty)
		{
			rebuildWorldMatrix();
		}

		return m_matWorld;
	}

	const glm::mat4& Transform::getWorldTransformNoScale()
	{
		if (m_isDirty)
		{
			rebuildWorldMatrix();
		}

		return m_matWorldNoScale;
	}

	const glm::mat3& Transform::getWorldIT()
	{
		if (m_isDirty)
		{
			rebuildWorldMatrix();
		}

		return m_matWorldIT;
	}

	void Transform::move2D(const float xUnits, const float yUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);
		}

		setChildrenDirty(position);
		notifyPositionListeners();
	}

	void Transform::move(const float xUnits, const float yUnits, const float zUnits)
	{
		m_translation[0] += xUnits;
		m_translation[1] += yUnits;
		m_translation[2] += zUnits;
		m_matTranslation = glm::translate(m_translation);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);
		}

		setChildrenDirty(position);
		notifyPositionListeners();
	}

	void Transform::place2D(const float x, const float y)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_matTranslation = glm::translate(x, y, m_translation.z);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);
		}

		setChildrenDirty(position);
		notifyPositionListeners();
	}

	void Transform::place(const float x, const float y, const float z)
	{
		m_translation[0] = x;
		m_translation[1] = y;
		m_translation[2] = z;
		m_matTranslation = glm::translate(x, y, z);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);
		}

		setChildrenDirty(position);
		notifyPositionListeners();
	}

	void Transform::placeInWorld(const float x, const float y, const float z)
	{
		if (m_ignoresParent || m_parent == nullptr)
		{
			place(x,y,z);
		}
		else
		{
			auto parentPos = m_parent->getTranslation();
			place(x - parentPos.x, y - parentPos.y, z - parentPos.z);
			//set this position so parentPos + thisPos = p_pos
		}
	}

	void Transform::scale2D(const float xScale, const float yScale)
	{
		m_scale = glm::vec3(xScale, yScale, 1.0f);
		m_matScale = glm::scale(xScale, yScale, 1.0f);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedScale = m_scale * m_parent->getScale();
		}

		setChildrenDirty(scale);
		notifyScaleListeners();
	}

	void Transform::scaleAbsolute(const float xScale, const float yScale, const float zScale)
	{
		m_scale = glm::vec3(xScale, yScale, zScale);
		m_matScale = glm::scale(m_scale);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedScale = m_scale * m_parent->getScale();
		}

		setChildrenDirty(scale);
		notifyScaleListeners();
	}

	void Transform::scaleRelative(const float xScale, const float yScale, const float zScale)
	{
		m_scale += glm::vec3(xScale, yScale, zScale);
		m_matScale = glm::scale(m_scale);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedScale = m_scale * m_parent->getScale();
		}

		setChildrenDirty(scale);
		notifyScaleListeners();
	}

	void Transform::scaleInWorld(const float xScale, const float yScale, const float zScale)
	{
		if (!m_ignoresParent && m_parent != nullptr)
		{
			const glm::vec3& parentScale = m_parent->getScale();
			
			float neededX = xScale / parentScale.x;
			float neededY = yScale / parentScale.y;
			float neededZ = zScale / parentScale.z;

			scaleAbsolute(neededX, neededY, neededZ);
		}
		else
		{
			scaleAbsolute(xScale, yScale, zScale);
		}
	}

	void Transform::rotate2D(const float deg)
	{
		rotateRelative(glm::vec3(0, 0, deg));
	}

	void Transform::rotateRelative(const glm::vec3& rot)
	{
		m_quatRotation = glm::quat(rot * (float)DEG_TO_RAD_FACTOR) * m_quatRotation;
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedQuatRotation = m_quatRotation * m_parent->getRotation();
			m_forward = glm::vec3(0, 0, 1) * m_derivedQuatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_derivedQuatRotation;
		}
		else
		{
			m_forward = glm::vec3(0, 0, 1) * m_quatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_quatRotation;
		}

		setChildrenDirty(rotation);
		notifyRotationListeners();
	}

	void Transform::rotateAbsolute(const glm::vec3& rot)
	{
		m_quatRotation = glm::quat(rot * (float)DEG_TO_RAD_FACTOR);
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedQuatRotation = m_quatRotation * m_parent->getRotation();
			m_forward = glm::vec3(0, 0, 1) * m_derivedQuatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_derivedQuatRotation;
		}
		else
		{
			m_forward = glm::vec3(0, 0, 1) * m_quatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_quatRotation;
		}

		setChildrenDirty(rotation);
		notifyRotationListeners();
	}

	void Transform::rotateAbsQuat(const glm::quat& rot)
	{
		m_quatRotation = rot;
		m_isDirty = true;

		if (!m_ignoresParent && m_parent != nullptr)
		{
			m_derivedQuatRotation = rot * m_parent->getRotation();
			m_forward = glm::vec3(0, 0, 1) * m_derivedQuatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_derivedQuatRotation;
		}
		else
		{
			m_forward = glm::vec3(0, 0, 1) * m_quatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_quatRotation;
		}

		setChildrenDirty(rotation);
		notifyRotationListeners();
	}

	const glm::vec3& Transform::getTranslation() const
	{
		if (m_ignoresParent)
		{
			return m_translation;
		}
		else
		{
			return m_derivedTranslation;
		}
	}

	const glm::vec3 & Transform::getRelativeTranslation() const
	{
		return m_translation;
	}

	const glm::quat& Transform::getRotation() const
	{
		if (m_ignoresParent)
		{
			return m_quatRotation;
		}
		else
		{
			return m_derivedQuatRotation;
		}
	}

	const glm::vec3& Transform::getForward() const
	{
		return m_forward;
	}

	const glm::vec3& Transform::getUpVector() const
	{
		return m_upVector;
	}

	const glm::vec3& Transform::getScale() const
	{
		if (m_ignoresParent)
		{
			return m_scale;
		}
		else
		{
			return m_derivedScale;
		}
	}

	const glm::vec3& Transform::getLocalScale() const
	{
		return m_scale;
	}

	glm::vec2 Transform::getScale2D() const
	{
		if (m_ignoresParent)
		{
			return (glm::vec2)m_scale;
		}
		else
		{
			return (glm::vec2)m_derivedScale;
		}
	}

	const glm::mat4& Transform::getTranslationMat4()
	{
		if (m_isDirty)
		{
			rebuildWorldMatrix();
		}

		if (!m_ignoresParent)
		{
			return m_derivedMatTranslation;
		}
		else
		{
			return m_matTranslation;
		}
	}

	const glm::mat4& Transform::getRotScaleMat4()
	{
		if (m_isDirty)
		{
			rebuildWorldMatrix();
		}

		if (!m_ignoresParent)
		{
			return m_derivedRotScale;
		}
		else
		{
			return m_rotScale;
		}
	}

	bool Transform::getIgnoreParent() const
	{
		return m_ignoresParent;
	}

	void Transform::setIgnoreParent(bool p_ignores)
	{
		if (m_ignoresParent != p_ignores)
		{
			m_ignoresParent = p_ignores;

			if (!p_ignores)
			{
				if (m_parent != nullptr)
				{
					onParentDirty(unknown);
				}

				m_isDirty = true;
				setChildrenDirty(unknown);
				//Not sure how transform attributes will change, notify
				notifyPositionListeners();
				notifyRotationListeners();
				notifyScaleListeners();
			}
		}
	}

	void Transform::setParent(Transform* p_parent)
	{
		if (p_parent == m_parent)
		{
			return;
		}

		if (m_parent != nullptr)
		{
			m_parent->removeChild(this);

			m_parent = p_parent;

			if (p_parent != nullptr)
			{
				p_parent->addChild(this);
			}
			else
			{
				K_GameObjectManager::sm_instance->addGameObjectToList(&m_attachedObject);
			}
		}
		else
		{
			m_parent = p_parent;

			if (p_parent != nullptr)
			{
				p_parent->addChild(this);
			}
			
			K_GameObjectManager::sm_instance->removeGameObjectFromList(&m_attachedObject);
		}

		notifyParentListeners(); // intentionally not in the if statement below

		if (!m_ignoresParent)
		{
			m_isDirty = true;
			setChildrenDirty(unknown);
			//Not sure how transform attributes will change, notify
			notifyPositionListeners();
			notifyRotationListeners();
			notifyScaleListeners();
		}
	}

	Transform* Transform::getParent()
	{
		return m_parent;
	}

	//Private method called when the child's parent is assigned to this
	void Transform::addChild(Transform* p_child)
	{
		m_children.push_back(p_child);
	}

	bool Transform::removeChild(const Transform* p_child)
	{
		auto end = m_children.end();
		for (auto it = m_children.begin(); it != end; ++it)
		{
			if (p_child == *it)
			{
				m_children.erase(it);
				return true;
			}
		}

		return false;
	}

	bool Transform::hasChildren() const
	{
		return !m_children.empty();
	}

	const std::vector<Transform*>& Transform::getChildren() const
	{
		return m_children;
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

	void Transform::addParentListener(TransformParentListener* p_toAdd)
	{
		m_parentListeners.push_back(p_toAdd);
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

	void Transform::removeParentListener(TransformParentListener* p_toRemove)
	{
		auto end = m_parentListeners.cend();
		for (auto it = m_parentListeners.begin(); it != end; ++it)
		{
			if (*it == p_toRemove)
			{
				m_parentListeners.erase(it);
				return;
			}
		}
	}

	void Transform::notifyScaleListeners()
	{
		const glm::vec3& scale = getScale();
		auto end = m_scaleListeners.cend();
		for (auto it = m_scaleListeners.begin(); it != end; ++it)
		{
			(*it)->onScaleChanged(scale);
		}
	}

	void Transform::notifyPositionListeners()
	{
		const glm::vec3& pos = getTranslation();
		auto end = m_positionListeners.cend();
		for (auto it = m_positionListeners.begin(); it != end; ++it)
		{
			(*it)->onPosChanged(pos);
		}
	}

	void Transform::notifyRotationListeners()
	{
		const glm::quat& rot = getRotation();
		auto end = m_rotationListeners.cend();
		for (auto it = m_rotationListeners.begin(); it != end; ++it)
		{
			(*it)->onRotationChanged(rot);
		}
	}

	void Transform::notifyParentListeners()
	{
		auto end = m_parentListeners.cend();
		for (auto it = m_parentListeners.begin(); it != end; ++it)
		{
			(*it)->onParentChanged(m_parent);
		}
	}

	void Transform::setChildrenDirty(ParentDirtyType p_type)
	{
		auto end = m_children.cend();
		for (auto it = m_children.cbegin(); it != end; ++it)
		{
			if (!(*it)->m_ignoresParent)
			{
				(*it)->onParentDirty(p_type);
			}	
		}
	}

	void Transform::onParentDirty(ParentDirtyType p_type)
	{
		m_isDirty = true;

		setChildrenDirty(p_type);

		switch (p_type)
		{
		case position:
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);

			notifyPositionListeners();
			break;
		case rotation:
			m_derivedQuatRotation = m_quatRotation * m_parent->getRotation();
			m_forward = glm::vec3(0, 0, 1) * m_derivedQuatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_derivedQuatRotation;

			notifyRotationListeners();
			break;
		case scale:
			m_derivedScale = m_scale * m_parent->getScale();

			notifyScaleListeners();
			break;
		case unknown:
			m_derivedTranslation = m_parent->getTranslation() + (m_parent->getRotation() * m_translation);
			m_derivedQuatRotation = m_quatRotation * m_parent->getRotation();
			m_forward = glm::vec3(0, 0, 1) * m_derivedQuatRotation;
			m_upVector = glm::vec3(0, 1, 0) * m_derivedQuatRotation;
			m_derivedScale = m_scale * m_parent->getScale();

			notifyPositionListeners();
			notifyRotationListeners();
			notifyScaleListeners();
			break;
		default:
			assert(false);
		}
	}
}