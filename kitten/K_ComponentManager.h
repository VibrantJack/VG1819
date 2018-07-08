#include <list>

class K_Component;

namespace kitten
{
	class K_ComponentManager
	{
	private:
		std::list<K_Component*> m_toUpdate;
		
	public:
		static K_ComponentManager* instance;
		static void createInstance() { instance = new K_ComponentManager(); };
		static void destroyInstance() { delete(instance); instance = nullptr; };


		bool createComponent();
		bool destroyComponent(K_Component* p_toDestroy);

	};
}