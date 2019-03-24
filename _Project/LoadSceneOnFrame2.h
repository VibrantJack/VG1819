#pragma once

#include "kitten\K_Component.h"
#include "kitten\K_Instance.h"

class LoadSceneOnFrame2 : public kitten::K_Component
{
private:
	const std::string m_sceneName;
	bool m_hasWaited = false;

	virtual bool hasUpdate() const override { return true; }
	virtual void update() override;

public:
	LoadSceneOnFrame2(const std::string& p_sceneName);
	~LoadSceneOnFrame2();
};