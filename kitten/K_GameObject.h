#include <typeindex>
#include <unordered_map>

#include "Transform.h"

namespace kitten
{
	class K_Component {};

	class K_GameObject
	{
		friend class K_GameObjectManager;
	private:
		std::unordered_map<std::type_index, K_Component*> m_components;
		int m_objectIndex;

		Transform* m_transform;

		K_GameObject();
		~K_GameObject();
	public:
		//Constructor and destructor in GameObjectManager
		bool addComponent(K_Component* p_toAdd);

		template <typename T>
		T getComponent();

		Transform& getTransform() { return *m_transform; };
	};
}