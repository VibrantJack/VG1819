#include <list>

class K_Component;

namespace kitten
{
	class K_ComponentManager
	{
	private:
		std::list<K_Component*> m_toUpdate;

	public:
		
		bool createComponent();
		bool destroyComponent(K_Component* p_toDestroy);

	};
}