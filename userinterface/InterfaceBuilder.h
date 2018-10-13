#pragma once

#include <vector>
#include "UIFrame.h"
#include "kitten\K_Component.h"


namespace userinterface
{

	class InterfaceBuilder : public kitten::K_Component
	{
	public:
		InterfaceBuilder();
		~InterfaceBuilder();

		bool hasUpdate() const  override;
		void update() override;
		void start() override;
		
	private:
	};
}