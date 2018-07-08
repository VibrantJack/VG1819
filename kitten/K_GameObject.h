
namespace kitten
{
	class K_GameObject
	{
	private:

	public:
		//Constructor and destructor in GameObjectManager

		bool addComponent(K_Component p_toAdd);
		K_Component getComponent();

	};
}