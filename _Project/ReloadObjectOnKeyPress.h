#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_GameObject.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\InputManager.h"


#include <string>

class ReloadObjectOnKeyPress : public kitten::K_Component
{
private:
	const std::string m_pathToJson;
	const char m_key;
	const bool m_replaceTransform;

	input::InputManager* m_inputMan;

	virtual void start() override;

	virtual bool hasUpdate() const override
	{
		return true;
	}
	virtual void update() override;

public:
	ReloadObjectOnKeyPress(char p_key, const std::string& p_pathToJson, bool p_replaceTransform = true);
	~ReloadObjectOnKeyPress();
};