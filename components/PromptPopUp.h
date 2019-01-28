#pragma once
#include "kitten/K_Component.h"
#include "kitten/K_GameObject.h"

class PromptPopUp : public kitten::K_Component {
public:
	class Behavior {
	public:
		std::string m_text;
		virtual void onSuccess()=0; // A must to set
		virtual void onDecline(){
			PromptPopUp::getActiveInstance()->setEnabledPrompt(false);
		}
	};

protected:
	Behavior *m_connectedBehavior;
	kitten::K_GameObject *m_backgroundFrame, *m_successFrame, *m_declineFrame, *m_textBox, *m_mainObject;

public:
	void setBehavior(Behavior* p_connectedBehavior);
	void triggerSuccess() { m_connectedBehavior->onSuccess(); }
	void triggerDecline() { m_connectedBehavior->onDecline(); }
	void setEnabledPrompt(bool p_flag) { m_mainObject->setEnabled(p_flag); }
	void start() override;

	static PromptPopUp* getActiveInstance();

	PromptPopUp();
	~PromptPopUp();
};