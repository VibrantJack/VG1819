#pragma once
#include "kitten\mouse picking\Clickable.h"
#include "puppy\Text\TextBox.h"
#include "components\SelectAbility.h"

class UseAbilityWhenClicked : public kitten::Clickable
{
public:
	UseAbilityWhenClicked();
	virtual ~UseAbilityWhenClicked();

	void start() override;
	virtual bool hasUpdate() const override { return true; };
	virtual void update() override;

	virtual void onClick() override;

private:
	puppy::TextBox* m_textBox;
	bool m_bSelectingAbility;

	SelectAbility* m_pSelectAbilityComp;
};