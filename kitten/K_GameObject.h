#include <typeindex>
#include <unordered_map>

namespace kitten
{
	class K_Component {};

	class K_GameObject
	{
		friend class K_GameObjectManager;
	private:
		std::unordered_map<std::type_index, K_Component*> m_components;
		int m_objectIndex;

	public:
		//Constructor and destructor in GameObjectManager
		bool addComponent(K_Component* p_toAdd);

		template <typename T>
		T getComponent();

	};
}