#include "K_GameObject.h"
#include "K_ComponentManager.h"

namespace kitten
{
	class K_Component
	{
		friend class K_ComponentManager;

	private:
		K_Component();
		virtual ~K_Component();
		
		K_GameObject* m_attachedObject;
	public:
		

		virtual const bool hasUpdate() const { return false; }
		virtual void update();

		
	};
}